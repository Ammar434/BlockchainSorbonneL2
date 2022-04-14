#include "exercice1.h"

// Exercice 1

// Question 1.1
int is_prime_naive(long p)
{
    for (int i = 2; i <= (p / 2); i++)
    {
        if (p % i == 0)
        {
            return 0;
        }
    }
    return 1;
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

    // Cas 1
    if (m == 0)
    {
        return 1;
    }

    // Cas 2
    if (m == 1)
    {
        return a % n;
    }

    // Cas 3
    for (int i = 0; i < m; i++)
    {
        val = ((val * a) % n);
    }
    return val;
}

// Question 1.4
long modpow(long a, long m, long n)
{
    long x;
    // 4 cas possibles
    // Cas 1 (cas de base)
    if (m == 0)
    {
        return 1;
    }

    // Cas 2
    if (m == 1)
    {
        return a % n;
    }

    // Cas 3 et 4
    // m impair
    if (m & 1)
    {
        x = modpow(a, m / 2, n);
        return (a * x * x) % n;
    }
    // m pair
    else
    {
        x = modpow(a, m / 2, n);
        return (x * x) % n;
    }
}

// Question 1.5
void generer_data_modpow_naive()
{
    FILE *file = fopen("courbe_donnee/generer_data_modpow_naive.txt", "w");
    long a = rand_long(3, 7);
    long n = rand_long(3, 7);
    clock_t temps_initial;
    clock_t temps_final;
    float temps_cpu;

    for (int m = 1; m < 50000; m++)
    {
        temps_initial = clock();
        modpow_naive(a, m, n);
        temps_final = clock();
        temps_cpu = (temps_final - temps_initial) * pow(10, -6);
        fprintf(file, "%d %f\n", m, temps_cpu);
        printf("Iteration %d de modpow_naive duree => %f\n", m, temps_cpu);
    }
    fclose(file);
}

void generer_data_modpow()
{
    clock_t temps_initial;
    clock_t temps_final;
    float temps_cpu;
    FILE *file = fopen("courbe_donnee/generer_data_modpow.txt", "w");
    long a, n;
    a = rand_long(3, 7);
    n = rand_long(3, 7);
    for (int m = 1; m < 50000; m++)
    {
        temps_initial = clock();
        modpow(a, m, n);
        temps_final = clock();
        temps_cpu = (temps_final - temps_initial) * pow(10, -6);
        fprintf(file, "%d %f\n", m, temps_cpu);
        printf("Iteration %d de modpow duree => %f\n", m, temps_cpu);
    }
    fclose(file);
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

// Question 1.8
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
    long low = (long)(power(2, low_size - 1));
    long up = (long)(power(2, up_size) - 1);
    // On genere un entier long aléatoire entre low et up
    long res = 0;

    // Tant qu'un témoin de Miller est vrai, càd que le nombre n'est pas premier
    while (is_prime_miller(res, k) == 0)
    {
        res = rand_long(low, up);
    }

    // Vérification que ce n'est pas premier
    if (is_prime_naive(res) == 0)
    {
        printf("Nombre non premier\n");
    }
    return res;
}