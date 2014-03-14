/**
 * @file server.h
 * @brief Header file for server side program.
 *
 * This file pretty much contains all defines, function prototypes, and
 * includes that the server needs.
 *
 * @author Brooks Kindle
 * @date March 2014
 */

#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>//just for the demo

//global variable declarations
const extern unsigned int PORT_NO; ///< default port number to use

//function prototypes
/**
 * @brief Performs initialization required by the server side.
 * @return File descriptor (socket) that the server will use to listen to, or -1
 * if an error occurred.
 */
int serverInit(void);

/**
 * @brief Waits until a client connects and then returns its file descriptor.
 * @param serverfd file descriptor of the listening server.
 * @return File descriptor (socket) of a connected client.
 */
int getNextClient(int serverfd);

#endif
