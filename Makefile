CC=gcc
CFLAGS=-I.

make: server.c
	$(CC) -o server server.c -I.