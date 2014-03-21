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


void get(int socket, const char *filename) {
	char ans[MAX];
	//char buf[MAX];
	int n;

	n = read(socket, ans, MAX);
	int size = atoi(ans); //get size of file

	if( size == -1) 
	{
		fprintf(stderr, "Recieved -1 for size: An error has occured\n");
		return;

	}else
	{
		int count = 0 ;
		if( filename == NULL)
		{
			fprintf(stderr, " invalid file name");
		}else
		{
			int fid = open(filename, O_WRONLY | O_CREAT| O_TRUNC, 0644);
			int count = 0;
			while( count < size) 
			{
				char buf[MAX];
				n = read(socket,buf, MAX);
				count += n;
				write(fid, buf, n); //only write the number of bytes we received
			}//end while
			close(fid);

		}//end if else
	}//end if else
}//end get


void put(int socket, const char *filename) {
	char buf[MAX];
	int n;

	int fid =  open(filename, O_RDONLY);
	if( fid == -1)
	{
		fprintf(stderr, "Error opening file: Sending -1\n");
		sprintf(buf,"%d", fid);
		n = write(socket, buf, MAX);

	}else
	{
		//send size
		struct stat info;
		int x = stat(filename, &info);
		int size = info.st_size;
		sprintf(buf, "%d", size);
		n = write(socket, buf, MAX);

		//then send file 
		while((n=read(fid, buf, MAX)))
		{
			n = write(socket, buf, n); //only write n bytes that we read from the file
		}//end while
	}//end if else



}//end put
