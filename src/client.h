/**
 * @file client.h
 * @brief header file for client side
 *
 * @author Brooks Kindle
 * @date March 2014
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
