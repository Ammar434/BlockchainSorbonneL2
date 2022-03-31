
#include "exercice2.h"
// Exercice 2

// version récursive de l’algorithme d’Euclide etendu
long extended_gcd(long s, long t, long *u, long *v)
{
    if (s == 0)
    {
        *u = 0;
        *v = 1;
        return t;
    }
    long uPrim, vPrim;
    long gcd = extended_gcd(t % s, s, &uPrim, &vPrim);
    *u = vPrim - (t / s) * uPrim;
    *v = uPrim;
    return gcd;
}

// Question 2.1
void generate_key_values(long p, long q, long *n, long *s, long *u)
{
    long t = (p - 1) * (q - 1);
    *n = p * q;
    *s = rand_long(2, t - 1);
    long v;
    long pgcd = extended_gcd(*s, t, u, &v);
    while (pgcd != 1)
    {
        *s = rand_long(2, t - 1);
        pgcd = extended_gcd(*s, t, u, &v);
    }
    long test = (*s) * (*u) + t * v;
    if (test != 1)
    {
        fprintf(stderr, "Erreur generate_key_values : %ld\n", test);
    }
}

// Question 2.2
long *encrypt(char *chaine, long s, long n)
{
    int i = 0;
    long *tab = (long *)malloc(sizeof(long) * strlen(chaine));
    assert(tab);
    while (chaine[i] != '\0')
    {
        tab[i] = modpow((int)chaine[i], s, n);
        i++;
    }
    return tab;
}

// Question 2.3
char *decrypt(long *crypted, int size, long u, long n)
{
    char *tab = (char *)malloc(sizeof(char) * size + 1);
    assert(tab);
    for (int i = 0; i < size; i++)
    {
        tab[i] = (char)modpow(crypted[i], u, n);
    }
    tab[size] = '\0';
    return tab;
}

void print_long_vector(long *result, int size)
{
    printf("Vector: [");
    for (int i = 0; i < size; i++)
    {
        if (i < size - 1)
            printf("%lx\t", result[i]);
        else
            printf("%lx", result[i]);
    }
    printf("]\n");
}
