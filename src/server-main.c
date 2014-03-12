/*
   Brooks Kindle
   brooks.kindle@wsu.edu

   server-main.c    -   entry point for server-side program
 */

#include "server.h"

int main(void) {
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr;
	char sendBuff[1025];
	time_t ticks;
	
	//create an unnamed socket inside the kernel (to listen from) and return fd
	// the first argument, AF_INET, specified the internet family of IPv4 addrs)
	//second arg, SOCK_STREAM, specified the transport layer protocol that we
	//want, for example, TCP
	//third arg, 0, let kernel decide the default protocol to use for connection
	//for connection oriented reliable connections, default protocol is TCP
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	//initialize memory
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff));

	serv_addr.sin_family = AF_INET; //set server family/domain

	//interface to listen on, in case of multiple interfaces to networks
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	serv_addr.sin_port = htons(5000); //port number to listen on

	//assigns details of serv_addr to the given socket (listenfd)
	bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	//set listenfd as a listening socket, accepting 10 max client connections
	listen(listenfd, 10);

	
	//print server details to screen
	printf("Listening from IP=%s PORT=%d\n", inet_ntoa(serv_addr.sin_addr),
			ntohs(serv_addr.sin_port));

	while(1) { //loop continually to connect to client
		connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);

		ticks = time(NULL); //get the current time
		snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
		write(connfd, sendBuff, strlen(sendBuff)); //send client the time
		printf("Wrote %ld bytes\n", strlen(sendBuff) + 1);

		close(connfd);
		sleep(1); //sleep for a tiny bit to we don't use all CPU power, hehehe
	}//end while
}//end main
