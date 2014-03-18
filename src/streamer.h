/**
 * @file streamer.h
 * @brief Header file for things required by both client and server
 *
 * @author Brooks Kindle
 * @date March 2014
 */

#ifndef STREAMER_H
#define STREAMER_H

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

#endif
