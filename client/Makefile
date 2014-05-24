CC=gcc
CFLAGS=-I.
EXE=run-client

PSRC = client.c
POBJ = client.o

sched: $(POBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(POBJ) -lsocket -lnsl

clean:
	/bin/rm $(POBJ)
