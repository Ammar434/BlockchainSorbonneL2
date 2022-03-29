CFLAGS = -g -Wall -Wextra -pedantic -ggdb3 -fsanitize=address
CC = gcc

PROGRAMS = main
.PHONY:	all clean

all: $(PROGRAMS)

main: main.o  partie1.o partie2.o partie3.o jeuDeTest.o -lm
	$(CC) -o $@ $(CFLAGS) $^

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

jeuDeTest.o: jeuDeTest.c
	$(CC) -c $(CFLAGS) jeuDeTest.c 
	
partie1.o: partie1.c
	$(CC) -c $(CFLAGS) partie1.c

partie2.o: partie2.c
	$(CC) -c  $(CFLAGS) partie2.c 

partie3.o: partie3.c
	$(CC) -c  $(CFLAGS) partie3.c 


clean:
	rm -f *.o *~ $(PROGRAMS)