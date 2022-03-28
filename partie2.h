#ifndef PARTIE2_H
#define PARTIE2_H
#include "partie1.h"

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
long extended_gcd(long s, long t, long *u, long *v);
void generate_key_values(long p, long q, long *n, long *s, long *u);
long *encrypt(char *chaine, long s, long n);
char *decrypt(long *crypted, int size, long u, long n);
void print_long_vector(long *result, int size);
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
#endif // PARTIE2_H