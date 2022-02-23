#include "primalite.h"

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
https: // prod.liveshare.vsengsaas.visualstudio.com/join?FB7976C219D7D14E48770925E7CC37C23639