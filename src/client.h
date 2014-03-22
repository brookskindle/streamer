/*
 * Brooks Kindle
 * brooks.kindle@wsu.edu
 *
 * client.h	-	header file for client side program
 */

#ifndef CLIENT_H
#define CLIENT_H

#include "streamer.h"

extern const char MUSIC_FILE[]; ///< name of the music file to play

//function prototypes
/**
 * @brief Attempts to play the given filename
 *
 * @param filename name of the music file to play
 * @return 0 on failure, or a positive integer on success
 */
int play(const char *const filename);

#endif
