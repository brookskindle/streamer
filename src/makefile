#####################################
#####	Author: Brooks Kindle	#####
#####	Streamer makefile		#####
#####################################

CC=gcc
CFLAGS=-m32
SER_EXE=server
CLI_EXE=client

all: server client
debug: CFLAGS += -ggdb
debug: all
server: server-main.c server.h
	$(CC) server-main.c -o $(SER_EXE) $(CFLAGS)
client: client-main.c client.h
	$(CC) client-main.c -o $(CLI_EXE) $(CFLAGS)
clean:
	rm -rf *.o $(SER_EXE) $(CLI_EXE)
