#include "primalite.h"
#include <time.h>
int main()
{
    clock_t temps_initial;
    clock_t temps_final;
    float temps_cpu;

    for (int i = 0; i < 100000; i++)
    {
        temps_initial = clock();
        modpow_naive(i, i, 5);
        temps_final = clock();
        temps_cpu = (temps_final - temps_initial) / CLOCKS_PER_SEC;
        printf("%f  s\n", temps_cpu);
    }
    for (int i = 0; i < 100000; i++)
    {
        temps_initial = clock();
        modpow(i, 10, 5);
        temps_final = clock();
        temps_cpu = (temps_final - temps_initial) / CLOCKS_PER_SEC;
        printf("%f  s\n", temps_cpu);
    }
    return 0;
}
