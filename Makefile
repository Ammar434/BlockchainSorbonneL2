CFLAGS = -g -Wall -Wextra -pedantic -ggdb3 
CC = gcc

PROGRAMS = main

OUTDIR = ./bin
SRCDIR = ./src
DATADIR = ./election_donnee

REQUIREMENT = exercice1.o  exercice2.o  exercice3.o  exercice4.o  exercice5.o  exercice6.o

.PHONY:	all clean

all: $(PROGRAMS)

main: main.o $(REQUIREMENT) jeuDeTest.o -lm
	$(CC) -o $@ $(CFLAGS) $^

main.o: main.c
	$(CC) -c $(CFLAGS) main.c 

jeuDeTest.o: $(SRCDIR)/jeuDeTest.c 
	$(CC) -c $(CFLAGS) $(SRCDIR)/jeuDeTest.c 

exercice1.o: $(SRCDIR)/partie1/exercice1/exercice1.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie1/exercice1/exercice1.c  

exercice2.o: $(SRCDIR)/partie1/exercice2/exercice2.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie1/exercice2/exercice2.c 
	
exercice3.o: $(SRCDIR)/partie2/exercice3/exercice3.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie2/exercice3/exercice3.c 

exercice4.o: $(SRCDIR)/partie2/exercice4/exercice4.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie2/exercice4/exercice4.c 

exercice5.o: $(SRCDIR)/partie3/exercice5/exercice5.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie3/exercice5/exercice5.c 

exercice6.o: $(SRCDIR)/partie3/exercice6/exercice6.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie3/exercice6/exercice6.c 

clean:
	rm -f $(OUTDIR)/*.o
	rm -f *.o *~ $(PROGRAMS)
	rm -f $(DATADIR)/*.txt