/**
 * @file server-main.c
 * @brief Entry point for the server program
 *
 * @author Brooks Kindle
 * @date March 2014
 */

#include "server.h"

int main(void) {
	int listenfd = 0, connfd = 0, n = 0, len = 0;
	char sendBuff[1025] = {0};
	struct sockaddr_in client_addr;

	if((listenfd = serverInit()) == -1) { //error setting up server
		fprintf(stderr, "Error: unable to initialize server\n");
		return 1;
	}

	while(1) { //loop continually to connect to client
		len = sizeof(client_addr);
		connfd = accept(listenfd, (struct sockaddr *)&client_addr, (socklen_t *)&len);
		printf("Client connected from IP=%s on PORT=%d\n",
				inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

		while(1) { //processing loop
			n = read(connfd, sendBuff, sizeof(sendBuff));

			if(!n) { //client died
				printf("Client died, waiting for new connection\n");
				close(connfd);
				break;
			}
			else if(n == -1) { //client hasn't sent anything yet
				continue;
			}

			printf("Client sent: %s\n", sendBuff);
		}//end while
		sleep(1); //sleep for a tiny bit to we don't use all CPU power, hehehe
	}//end while
}//end main
