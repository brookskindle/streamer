/**
 * @file server.c
 * @brief Source file for server side code
 *
 * @author Brooks Kindle
 * @date March 2014
 */

#include <sys/types.h>
#include <libgen.h>
#include <limits.h>
#include "server.h"

const char CONFIG_FILE[] = "streamer.config";
char buf[1024] = {0};

int serverInit(void) {
	int listenfd = 0;
	struct sockaddr_in serv_addr;

	printf("**********Initializing server**********\n");

	//create an unnamed socket inside the kernel (to listen from) and return fd.
	//the first argument, AF_INET, specifies the internet family of IPv4 addrs.
	//second arg, SOCK_STREAM, specifies the transport layer protocol that we
	//want, for example, TCP
	//third arg, 0, let kernel decide the default protocol to use for connection
	//for connection oriented reliable connections, default protocol is TCP
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	//initialize memory
	memset(&serv_addr, 0, sizeof(serv_addr)); 

	
	//configure details of the server
	serv_addr.sin_family = AF_INET; //set server family/domain (IPv4)
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //interface to listen on
	serv_addr.sin_port = htons(PORT_NO); //set port number to listen on

	//assigns the details of serv_addr to listenfd (our socket)
	bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	//finally, begin listening from socket!
	listen(listenfd, 10); //queue up to 10 clients
	printf("Listening from IP: %s on PORT: %d\n", inet_ntoa(serv_addr.sin_addr),
		ntohs(serv_addr.sin_port));
	printf("**********Init done**********\n");

	//return socket fd
	return listenfd;
}//end serverInit


int getNextClient(int serverfd) {
	int clientfd = accept(serverfd, NULL, NULL); //wait until client connects
	return clientfd;
}//end getNextClient


FILE *getConfigFile(void) {
	return fopen(CONFIG_FILE, "r"); //open config file for reading
}//end getConfigFile


void executeInput(char *inp, int fd, FILE *cfg) {
	char *fname = 0;
	rewind(cfg); //restart config file from beginning
	if(!strcmp(inp, "ls")) { //ls
		ls(fd, cfg);
	}
	else if(strstr(inp, "get") == inp) { //get
		fname = strtok(inp, " ");
		fname = fname + strlen(fname) + 1;
		if(fileExists(fname, cfg)) {
			put(fd, fname);
		}
		else { //invalid file specified
			fprintf(stderr, "Error: Unknown file %s\n", fname);
			write(fd, "-1", 3);
		}
	}
	else { //unknown command
		fprintf(stderr, "Unknown command %s..skipping\n", inp);
	}
}//end executeInput


int ls(int fd, FILE *cfg) {
	int nbad = 0, //number of bad path entries in config file
		n = 0,
		len = 0;
	char *path = 0;
	DIR *dir = 0;
	struct dirent *file = 0;

	getline(&path, (size_t *)&len, cfg);
	do { //process each line in config file
		n = strlen(path);
		path[n-- - 1] = 0; //remove newline
		if(path[n - 1] == '/' && n > 1) {
			path[n - 1] = 0;
		}
		dir = opendir(path);
		if(dir) {
			lsdir(fd, dir, path);
			closedir(dir);
		}//end if
		else { //unable to open directory
			fprintf(stderr, "Config file - unable to open directory %s\n",
					path);
			nbad++;
		}

		getline(&path, (size_t *)&len, cfg);
	}while(!feof(cfg));

	//send end of transmission to socket
	n = sprintf(buf, "%s", END_OF_INPUT);
	write(fd, buf, n);
	printf("%s\n", buf);

	return nbad;
}//end ls


void lsdir(int fd, DIR *dir, char *path) {
	struct dirent *file = 0;
	int n = 0;
	char *newpath = 0;
	DIR *newdir = 0;
	while((file = readdir(dir))) { //get directory entry
		if(file->d_type != DT_REG) { //file not regular
			continue;
		}
		bzero(buf, sizeof(buf));
		n = sprintf(buf, "%s/%s\n", path, file->d_name);
		write(fd, buf, n); //write filename to file descriptor
		printf("%s", buf);
	}
}//end lsdir


int fileExists(const char *const fname, FILE *cfg) {
	int exists = 0,
		len = 0;
	char path[PATH_MAX] = {0},
		 cfgpath[PATH_MAX] = {0};
	struct stat file;
	if(realpath(fname, path)) { //valid path specified
		if(!stat(path, &file)) { //file exists
			rewind(cfg);
			getline((char **)&cfgpath, (size_t *)&len, cfg);
			while(!feof(cfg)) {
				if(strstr(path, cfgpath) == path) {
					exists = 1; //file is being monitored
					break;
				}
				getline((char **)&cfgpath, (size_t *)&len, cfg);
			}//end while
		}
	}
	return exists;
}//end fileExists
