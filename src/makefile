#####################################
#####	Author: Brooks Kindle	#####
#####	Streamer makefile		#####
#####################################

CC=gcc
CFLAGS=
SER_EXE=server
CLI_EXE=client
#LIBS=-lcsfml-system -lcsfml-audio

all: client server 
debug: CFLAGS += -ggdb
debug: all
server: server-main.c server.h server.c streamer
	$(CC) streamer.o server-main.c server.c -o $(SER_EXE) $(CFLAGS) $(LIBS)
client: client-main.c client.h client.c streamer
	$(CC) streamer.o client-main.c client.c -o $(CLI_EXE) $(CFLAGS) $(LIBS)
streamer: streamer.h streamer.c
	$(CC) -c streamer.c $(CFLAGS) $(LIBS)
clean:
	rm -rf *.o $(SER_EXE) $(CLI_EXE)
