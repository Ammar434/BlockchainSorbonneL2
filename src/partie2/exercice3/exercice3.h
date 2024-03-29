#ifndef EXERCICE_3_H
#define EXERCICE_3_H
#include "../../partie1/partie1.h"
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
Signature *init_signature(long *content, int size);
Signature *sign(char *mess, Key *sKey);
char *signature_to_str(Signature *sgn);
Signature *str_to_signature(char *str);
Protected *init_protected(Key *pKey, char *mess, Signature *sgn);
char *protected_to_str(Protected *protected);
Protected *str_to_protected(char *str);

#endif // PARTIE2_H