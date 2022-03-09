#ifndef PRIMALITE_H
#define PRIMALITE_H
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int is_prime_naive(long p);
void test_q_1_2();
long modpow_naive(long a, long m, long n);
long modpow(long a, long m, long n);
void test_q_1_5();
int witness(long a, long b, long d, long p);
long rand_long(long low, long up);
int is_prime_miller(long p, int k);
long power(long a, long b);
long random_prime_number(int low_size, int up_size, int k);

long extended_gcd(long s, long t, long *u, long *v);
void generate_key_values(long p, long q, long *n, long *s, long *u);
long *encrypt(char *chaine, long s, long n);
char *decrypt(long *crypted, int size, long u, long n);
void print_long_vector(long *result, int size);

// Question 3.1
typedef struct key
{
    long a;
    long b;
} Key;

void init_key(Key *key, long val, long n);
void init_pair_keys(Key *pKey, Key *sKey, long low_size, long up_size);
char *key_to_str(Key *key);
Key *str_to_key(char *key);
#endif