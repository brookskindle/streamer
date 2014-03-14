/*
 * Brooks Kindle
 * brooks.kindle@wsu.edu
 *
 * client-main.c	-	entry point for client-side program
 */

#include "client.h"

int main(int argc, char *argv[]) {
	int sockfd = 0, n = 0;
	char recvBuff[1024];
	struct sockaddr_in serv_addr;

	if(argc != 2) {
		printf("Usage: %s <ip of server> \n", argv[0]);
		return 1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Error: could not create socket\n");
		return 1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000);

	if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
		printf("inet_pton error occurred\n");
		return 1;
	}

	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("Error: connection failed\n");
		return 1;
	}

	
	while(1) { //processing loop
		printf("Enter command (\"exit\" to quit): ");
		fgets(recvBuff, sizeof(recvBuff), stdin); //get user input
		if(!strcmp("quit", recvBuff)) {
			break;
		}
		n = write(sockfd, recvBuff, sizeof(recvBuff));
		if(n == -1) {
			printf("Unable to write to server.\n");
			break;
		}
	}//end while

	close(sockfd);//close socket if it hasn't already been closed
	return 0;
}//end main
