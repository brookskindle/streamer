/**
 * @file server.c
 * @brief Source file for server side code
 *
 * @author Brooks Kindle
 * @date March 2014
 */

#include "server.h"

const unsigned int PORT_NO = 5000;

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
