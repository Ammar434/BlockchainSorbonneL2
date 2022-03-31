#ifndef EXERCICE_4_H
#define EXERCICE_4_H
#include "../exercice3/exercice3.h"

int verify(Protected *pr);
void generer_all_data(char *filename, int nv);
void generer_declaration_vote(char *filename, char *filename2, char *filename3, int nbCandidates);
void generer_selection_candidat(char *filename, char *filename2, int nv, int nc);
void generate_random_data(int nv, int nc);

#endif // PARTIE2_H