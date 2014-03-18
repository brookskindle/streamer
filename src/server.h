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
#include "streamer.h"

//global variable declarations
const extern char CONFIG_FILE[]; ///< default server configuration file

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

/**
 * @brief Locates the server configuration file and returns a FILE pointer to it
 * @return FILE pointer to the configuration file.
 */
FILE *getConfigFile(void);

/**
 * @brief Attempts to execute client input.
 *
 * If the input is a valid command, it will be executed. Else, an error
 * message will be printed and nothing will happen.
 * 
 * @param inp string input of the client
 * @param fd file descriptor to print results to
 * @param cfg server configuration file
 */
void executeInput(char *inp, int fd, FILE *cfg);

/**
 * @brief Lists the contents of each directory in the server configuration file.
 *
 * Error messages will be printed to stderr for every path in the configuration
 * file that cannot be opened and read from as a directory.
 *
 * @param fd file descriptor to print results to
 * @param cfg configuration file (tells us what directories to list)
 * @return the number of paths that could not be read from (so 0 is success)
 */
int ls(int fd, FILE *cfg);

#endif
