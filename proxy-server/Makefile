CC=gcc
CFLAGS=-I.
EXE=run-server

PSRC = server.c connection.c handler.c logger.c
POBJ = server.o connection.o handler.o logger.o

sched: $(POBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(POBJ)

clean:
	/bin/rm $(POBJ)

server.o: connection.h logger.h
connection.o: handler.h logger.h
handler.o: logger.h