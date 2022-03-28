#include "partie1.h"
// Exercice 1
// Question 1.1
int is_prime_naive(long p)
{
    if ((p == 0) || (p == 1))
    {
        return 1;
    }
    else
    {
        for (int i = 2; i <= (p / 2); i++)
        {
            if (p % i == 0)
                return 0;
        }
        return 1;
    }
}

// Question 1.2
void test_q_1_2()
{
    clock_t ti, tf;
    double temps;
    int p = 3;
    while (is_prime_naive(p) == 0 || temps < 0.002)
    {
        ti = clock();
        is_prime_naive(p);
        tf = clock();
        temps = (double)(tf - ti) / CLOCKS_PER_SEC;
        p = p + 2;
    }
    printf("%d\n", p);
    printf("%d\n", is_prime_naive(p));
    return;
}

// Question 1.3
long modpow_naive(long a, long m, long n)
{
    long val = 1;
    if (m == 0)
    {
        return a % n;
    }
    for (int i = 0; i < m; i++)
    {
        val = ((val * a) % n);
    }
    return val;
}

// Question 1.4
long modpow(long a, long m, long n)
{
    if (m == 1)
    {
        return a % n;
    }
    long x = modpow(a, m / 2, n);

    if (m & 1)
    {
        return (a * x * x) % n;
    }
    else
    {
        return (x * x) % n;
    }
}

// Question 1.5
void test_q_1_5()
{
    FILE *f = fopen("q1_5.txt", "w");
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    clock_t ti, tf;
    double temps_naive, temps;
    for (int i = 1; i <= 10000; i++)
    {
        ti = clock();
        modpow_naive(5, i, 3);
        tf = clock();
        temps_naive = ((double)(tf - ti)) / CLOCKS_PER_SEC;

        ti = clock();
        modpow(5, i, 3);
        tf = clock();

        temps = ((double)(tf - ti)) / CLOCKS_PER_SEC;
        fprintf(f, "%d %f %f\n", i, temps_naive, temps);
    }
    fclose(f);
}

// Question 1.6
int witness(long a, long b, long d, long p)
{
    long x = modpow(a, d, p);
    if (x == 1)
    {
        return 0;
    }
    for (long i = 0; i < b; i++)
    {
        if (x == p - 1)
        {
            return 0;
        }
        x = modpow(x, 2, p);
    }
    return 1;
}

long rand_long(long low, long up)
{
    return rand() % (up - low + 1) + low;
}

int is_prime_miller(long p, int k)
{
    if (p == 2)
    {
        return 1;
    }
    if (!(p & 1) || p <= 1)
    { // on verifie que p est impair et different de 1
        return 0;
    }
    // on determine b et d :
    long b = 0;
    long d = p - 1;
    while (!(d & 1))
    { // tant que d n’est pas impair
        d = d / 2;
        b = b + 1;
    }
    // On genere k reseurs pour a, et on teste si c’est un temoin :
    long a;
    int i;
    for (i = 0; i < k; i++)
    {
        a = rand_long(2, p - 1);
        if (witness(a, b, d, p))
        {
            return 0;
        }
    }
    return 1;
}

// Question 1.8 à rechecker
long power(long a, long b)
{
    long cpt = 1;
    for (int i = 0; i <= b; i++)
    {
        cpt = cpt * a;
    }
    return cpt;
}

long random_prime_number(int low_size, int up_size, int k)
{
    long res = rand_long(power(2, (low_size - 1)), (power(2, up_size) - 1));
    int tmp = is_prime_miller(res, k);

    while (tmp == 0)
    {
        res = rand_long(power(2, (low_size - 1)), (power(2, up_size) - 1));
        tmp = is_prime_miller(res, k);
    }
    return res;
}

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
    *n = p * q;
    long t = (p - 1) * (q - 1);
    *s = rand_long(2, t);
    long v;
    while (extended_gcd(*s, t, u, &v) != 1)
    {
        *s = rand_long(2, t);
    }
    // printf("Clé publique : %lx %lx \n", *s, *n);
    // printf("Clé secrete : %lx %lx \n", *u, *n);
}

// Question 2.2
long *encrypt(char *chaine, long s, long n)
{
    int i = 0;
    long *tab = (long *)malloc(sizeof(long) * strlen(chaine));
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
