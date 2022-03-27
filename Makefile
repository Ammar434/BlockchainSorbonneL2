CFLAGS = -g -Wall -Wextra -pedantic
CC = gcc

PROGRAMS = main
.PHONY:	all clean

all: $(PROGRAMS)

main: main.o  partie1.o 
	$(CC) -o $@ $(CFLAGS) $^

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

jeuDeTest: jeuDeTest.o  partie1.o partie2.o -lm
	$(CC) -o $@ $(CFLAGS) $^

jeuDeTest.o: jeuDeTest.c
	$(CC) -c $(CFLAGS) jeuDeTest.c 
	
partie1.o: partie1.c
	$(CC) -c $(CFLAGS) partie1.c

partie2.o: partie2.c
	$(CC) -c  $(CFLAGS) partie2.c 
clean:
	rm -f *.o *~ $(PROGRAMS)
