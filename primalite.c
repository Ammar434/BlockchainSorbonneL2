#include "primalite.h"
//
int is_prime_naive(long p)
{
    if (p % 2 == 0)
    {
        return 1;
    }

    for (int i = 0; i < p; i++)
    {
        if (p % i == 0)
        {
            return 1;
        }
    }
    return 0;
}

long modpow_naive(long a, long m, long n)
{
    long res = 1;
    for (int i = 0; i < m; i++)
    {
        res = res * a;
    }
    res = res % n;
    return res;
}
long modpow(long a, long m, long n)
{
    long res = 1;
    for (int i = 0; i < m; i++)
    {
        res = (res * res) % n;
    }
    return res;
}
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
    // On genere k valeurs pour a, et on teste si c’est un temoin :
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