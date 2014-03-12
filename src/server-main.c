/**
 * @file server-main.c
 * @brief Entry point for the server program
 *
 * @author Brooks Kindle
 * @date March 2014
 */

#include "server.h"

int main(void) {
	int listenfd = 0, connfd = 0;
	char sendBuff[1025] = {0};

	if((listenfd = serverInit()) == -1) { //error setting up server
		fprintf(stderr, "Error: unable to initialize server\n");
		return 1;
	}

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
