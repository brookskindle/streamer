/**
 * @file streamer.c
 * @brief Source file for things required by both client and server
 *
 * @author Brooks Kindle
 * @date March 2014
 */

#include <string.h>
#include <stdio.h>
#include "streamer.h"

//global variables
const unsigned int PORT_NO = 5000;
const char *const COMMANDS[] = {"ls", "get"};
const char END_OF_INPUT[] = "END OF INPUT";


int isCommand(const char *const str) {
	int i, isCmd = 0;
	for(i = 0; i < sizeof(COMMANDS) / sizeof(const char *const); i++) {
		if(!strcmp(COMMANDS[i], str)) { //match found
			isCmd = 1;
			break;
		}
	}//end for
	return isCmd;
}//end isCommand
