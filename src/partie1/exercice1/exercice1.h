#ifndef EXERCICE_1_H
#define EXERCICE_1_H
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int is_prime_naive(long p);
void test_q_1_2();
long modpow_naive(long a, long m, long n);
long modpow(long a, long m, long n);
void generer_data_modpow_naive();
void generer_data_modpow();
int witness(long a, long b, long d, long p);
long rand_long(long low, long up);
int is_prime_miller(long p, int k);
long power(long a, long b);
long random_prime_number(int low_size, int up_size, int k);

#endif
