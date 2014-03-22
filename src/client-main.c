/*
 * Brooks Kindle
 * brooks.kindle@wsu.edu
 *
 * client-main.c	-	entry point for client-side program
 */

#include "client.h"

int main(int argc, char *argv[]) {
	int sockfd = 0, n = 0;
	char recvBuff[1024],
		 localIp[] = "127.0.0.1",
		 *serverIp = 0;
	struct sockaddr_in serv_addr;

	if(argc > 2) {
		printf("Usage: %s [ip of server]\n", argv[0]);
		return 1;
	}
	else if(argc == 1) { //no ip specified, assume localhost
		serverIp = localIp;
	}
	else { //ip specified, use that
		serverIp = argv[1];
	}

	memset(&serv_addr, '0', sizeof(serv_addr));
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Error: could not create socket\n");
		return 1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000);

	if(inet_pton(AF_INET, serverIp, &serv_addr.sin_addr) <= 0) {
		printf("inet_pton error occurred\n");
		return 1;
	}

	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("Error: connection failed\n");
		return 1;
	}

	
	while(1) { //processing loop
		bzero(recvBuff, 1024);
		printf("*******************\n");
		printf("*** ls play get ***\n");
		printf("*******************\n");
		printf("Enter command (\"exit\" to quit): ");
		fgets(recvBuff, sizeof(recvBuff), stdin); //get user input
		recvBuff[strlen(recvBuff) - 1] = 0; //remove newline character
		if(!strcmp("exit", recvBuff)) {
			break; //user wishes to exit
		}
		else if(!strcmp("ls", recvBuff)) {
			n = write(sockfd, recvBuff, sizeof(recvBuff)); //write input to server
			if(n == -1) {
				fprintf(stderr, "Unable to write to server.\n");
				break;
			}
			bzero(recvBuff, sizeof(recvBuff));
			while((n = read(sockfd, recvBuff, sizeof(recvBuff)))) {
				if(strstr(recvBuff, END_OF_INPUT)) { //end of input found
					*(strstr(recvBuff, END_OF_INPUT)) = 0; //null terminate
					break;
				}
				printf("%s", recvBuff);
			}//end while
		}//end else if
		else if(strstr(recvBuff, "get") == recvBuff) {
			n = write(sockfd, recvBuff, sizeof(recvBuff)); //write input to server
			get(sockfd, MUSIC_FILE);
		}//end else if
		else if(!strcmp("play", recvBuff)) { //play downloaded music
			play(MUSIC_FILE);
		}
		else {
			fprintf(stderr, "Unrecognized command: %s\n", recvBuff);
			continue;
		}
	}//end while

	close(sockfd);//close socket if it hasn't already been closed
	return 0;
}//end main
