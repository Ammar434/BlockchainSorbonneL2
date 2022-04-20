CFLAGS = -g -Wall -Wextra -Werror -pedantic -ggdb3 
CC = gcc

PROGRAMS = main

OUTDIR = ./bin
SRCDIR = ./src
DATADIR = ./election_donnee
BLOCKCHAINDIR = ./Blockchain

REQUIREMENT = exercice1.o  exercice2.o  exercice3.o  exercice4.o  exercice5.o  exercice6.o exercice7.o exercice8.o exercice9.o jeuDeTest.o

.PHONY:	all clean

all: $(PROGRAMS)

main: main.o $(REQUIREMENT) -lm -lssl -lcrypto
	$(CC) -o $@ $(CFLAGS) $(addprefix $(OUTDIR)/,$<) $(addprefix $(OUTDIR)/,$(REQUIREMENT)) -lm -lssl -lcrypto
	
main.o: main.c
	$(CC) -c $(CFLAGS) main.c -o $(OUTDIR)/$@

jeuDeTest.o: $(SRCDIR)/jeuDeTest.c 
	$(CC) -c $(CFLAGS) $(SRCDIR)/jeuDeTest.c -o $(OUTDIR)/$@

exercice1.o: $(SRCDIR)/partie1/exercice1/exercice1.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie1/exercice1/exercice1.c  -o $(OUTDIR)/$@

exercice2.o: $(SRCDIR)/partie1/exercice2/exercice2.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie1/exercice2/exercice2.c -o $(OUTDIR)/$@
	
exercice3.o: $(SRCDIR)/partie2/exercice3/exercice3.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie2/exercice3/exercice3.c -o $(OUTDIR)/$@

exercice4.o: $(SRCDIR)/partie2/exercice4/exercice4.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie2/exercice4/exercice4.c -o $(OUTDIR)/$@

exercice5.o: $(SRCDIR)/partie3/exercice5/exercice5.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie3/exercice5/exercice5.c -o $(OUTDIR)/$@

exercice6.o: $(SRCDIR)/partie3/exercice6/exercice6.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie3/exercice6/exercice6.c -o $(OUTDIR)/$@

exercice7.o: $(SRCDIR)/partie4/exercice7/exercice7.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie4/exercice7/exercice7.c -o $(OUTDIR)/$@	

exercice8.o: $(SRCDIR)/partie4/exercice8/exercice8.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie4/exercice8/exercice8.c -o $(OUTDIR)/$@	

exercice9.o: $(SRCDIR)/partie4/exercice9/exercice9.c
	$(CC) -c $(CFLAGS) $(SRCDIR)/partie4/exercice9/exercice9.c -o $(OUTDIR)/$@	

clean:
	rm -f $(OUTDIR)/*.o
	rm -f *.o *~ $(PROGRAMS)
	rm -f $(DATADIR)/*.txt
	# rm -f $(DATADIR)/blocks/*.txt
	rm -f $(BLOCKCHAINDIR)/blocks/*.txt
	rm -f $(BLOCKCHAINDIR)/pendings/*.txt