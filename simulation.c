#include "simulation.h"

// Question 1.2

void generer_data_modpow_naive()
{
    clock_t temps_initial;
    clock_t temps_final;
    float temps_cpu;
    FILE *file = fopen("courbe_donnee/generer_data_modpow_naive.txt", "w");
    long a, k, n;
    a = rand_long(3, 7);
    n = rand_long(3, 7);
    for (int m = 1; m < 50000; m++)
    {
        temps_initial = clock();
        k = modpow_naive(a, m, n);
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
    long a, k, n;
    a = rand_long(3, 7);
    n = rand_long(3, 7);
    for (int m = 1; m < 50000; m++)
    {
        temps_initial = clock();
        k = modpow(a, m, n);
        temps_final = clock();
        temps_cpu = (temps_final - temps_initial) * pow(10, -6);
        fprintf(file, "%d %f\n", m, temps_cpu);
        printf("Iteration %d de modpow duree => %f\n", m, temps_cpu);
    }
    fclose(file);
}