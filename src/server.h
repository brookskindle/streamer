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

#include <dirent.h>
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

/**
 * @brief lists all regular files in a given directory
 *
 * @param fd file descriptor to print results to
 * @param dir directory in question
 * @param path full path to given directory
 */
void lsdir(int fd, DIR *dir, char *path);

/**
 * @brief Makes sure a file exists and is being monitored by the server.
 *
 * This means that the file must exist and the dirname of the file's absolute
 * path must be a directory (or sub directory) of at least one path within
 * the server configuration file.
 *
 * @param fname name of the file
 * @param cfg server configuration file
 * @return a positive integer (probably 1) if the file exists and is being
 * monitored [success], or 0 if that is not the case [failure].
 */
int fileExists(const char *const fname, FILE *cfg);

#endif
