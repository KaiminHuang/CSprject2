CC=gcc
CFLAGS=-I.
EXE=run-server

PSRC = server.c connection.c handler.c
POBJ = server.o connection.o handler.o

sched: $(POBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(POBJ)

clean:
	/bin/rm $(POBJ)

server.o: connection.h
connection.o: handler.h