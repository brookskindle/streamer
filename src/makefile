#####################################
#####	Author: Brooks Kindle	#####
#####	Streamer makefile		#####
#####################################

CC=gcc
CFLAGS=-m32
SER_EXE=server
CLI_EXE=client

all: client server 
debug: CFLAGS += -ggdb
debug: all
server: server-main.c server.h server.c streamer
	$(CC) streamer.o server-main.c server.c -o $(SER_EXE) $(CFLAGS)
client: client-main.c client.h streamer
	$(CC) streamer.o client-main.c -o $(CLI_EXE) $(CFLAGS)
streamer: streamer.h streamer.c
	$(CC) -c streamer.c $(CFLAGS)
clean:
	rm -rf *.o $(SER_EXE) $(CLI_EXE)
