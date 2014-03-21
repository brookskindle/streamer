/**
 * @file streamer.h
 * @brief Header file for things required by both client and server
 *
 * @author Brooks Kindle
 * @date March 2014
 */

#ifndef STREAMER_H
#define STREAMER_H

#define MAX 256 ///< standard string size

//includes
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

//global variable declarations
const extern unsigned int PORT_NO; ///< default port number to use
const extern char *const COMMANDS[]; ///< list of valid commands
const extern char END_OF_INPUT[]; ///< string found at the end of a transmission

//function prototypes
/**
 * @brief determines if the given string is a command recognized by the server
 * @param str string to check
 * @return If the string is a valid command, returns a non-zero integer.
 * Else returns 0.
 */
int isCommand(const char *const str);

/**
 * @brief Downloads the given file.
 *
 * The very first thing to be received is the size of the file.
 * If the size is negative, then the file to be downloaded does not exist.
 *
 * @param socket File descriptor to receive the file.
 * @param filename Name of the file to save the downloaded file as.
 */
void get(int socket, const char *filename);

/**
 * @brief Opens the given file and writes its contents to the socket.
 *
 * The very first thing to be sent to the socket is the file size in bytes.
 * If the file does not exist, that size will be a negative number.
 *
 * @param socket File descriptor to send the size and file contents to.
 * @param filename Name of the file to retrieve.
 */
void put(int socket, const char *filename);

#endif
