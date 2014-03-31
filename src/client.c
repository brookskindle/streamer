/**
 * @file client.c
 * @brief Source file for client side program.
 *
 * @author Brooks Kindle
 * @date March 2014
 */

#include <SFML/Audio.h>
#include "client.h"

const char MUSIC_FILE[] = ".tmp.ogg";

int play(const char *const filename) {
	int success = 0;
	sfMusic *music = sfMusic_createFromFile(filename);

	if(music) { //success opening file
		sfMusic_play(music); //creates a new thread to play the music in
		success = 1;
	}

	return success;
}//end play
