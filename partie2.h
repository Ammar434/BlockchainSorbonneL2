#ifndef PARTIE2_H
#define PARTIE2_H
#include "partie1.h"
#define BUFFER_SIZE 1024

typedef struct _key
{
    long a;
    long b;
} Key;

typedef struct _signature
{
    long *tab;
    int size;
} Signature;

typedef struct _protected
{
    char *message;
    Key *pKey;
    Signature *signature;
} Protected;

void init_key(Key *key, long val, long n);
void init_pair_keys(Key *pKey, Key *sKey, long low_size, long up_size);
char *key_to_str(Key *key);
Key *str_to_key(char *key);
int getLenNum(long a);
Signature *init_signature(long *content, int size);
Signature *sign(char *mess, Key *sKey);
char *signature_to_str(Signature *sgn);
Signature *str_to_signature(char *str);
Protected *init_protected(Key *pKey, char *mess, Signature *sgn);
char *protected_to_str(Protected *protected);
Protected *str_to_protected(char *str);
int verify(Protected *pr);
void generer_all_data(char *filename, int nv);
void generer_declaration_vote(char *filename, char *filename2, char *filename3, int nbCandidates);
void generer_selection_candidat(char *filename, char *filename2, int nv, int nc);
void generate_random_data(int nv, int nc);

#endif // PARTIE2_H