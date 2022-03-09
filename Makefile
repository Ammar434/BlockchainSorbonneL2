CFLAGS = -g -Wall -Wextra -pedantic
CC = gcc

PROGRAMS = main
.PHONY:	all clean

all: $(PROGRAMS)

main: main.o  primalite.o 
	$(CC) -o $@ $(CFLAGS) $^

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

primalite.o: primalite.c
	$(CC) -c $(CFLAGS) primalite.c

clean:
	rm -f *.o *~ $(PROGRAMS)
