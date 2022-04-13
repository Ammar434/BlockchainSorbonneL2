#include "src/jeuDeTest.h"
void menu()
{
    printf("0 - Sortie du programme\n");
    printf("1 - jeu_test_exercice_1\n");
    printf("2 - jeu_test_exercice_2\n");
    printf("3 - jeu_test_exercice_3\n");
    printf("4 - jeu_test_exercice_4\n");
    printf("5 - jeu_test_exercice_5\n");
    printf("6 - jeu_test_exercice_6\n");
    printf("7 - jeu_test_exercice_6bis\n");
    printf("8 - jeu_test_exercice_7\n");
    printf("9 - jeu_test_exercice_8\n");
    printf("10 - jeu_test_exercice_9\n");
}

int main()
{
    srand(time(NULL));
    // int rep;
    // char buff[BUFFER_SIZE];
    // int nv, nc, cpt;
    // do
    // {
    //     printf("--------------------------------Que voulez-vous faire ?------------------------------------\n");
    //     menu();
    //     fgets(buff, BUFFER_SIZE, stdin);
    //     sscanf(buff, "%d\n", &rep);
    //     printf("\n");
    //     switch (rep)
    //     {
    //     case 1:
    //         jeu_test_exercice_1();
    //         printf("\n");
    //         printf("-------------------------------------------------------------------------------------------\n");
    //         printf("\n");
    //         break;

    //     case 2:
    //         jeu_test_exercice_2();
    //         printf("\n");
    //         printf("-------------------------------------------------------------------------------------------\n");
    //         printf("\n");
    //         break;

    //     case 3:
    //         jeu_test_exercice_3();
    //         printf("\n");
    //         printf("-------------------------------------------------------------------------------------------\n");
    //         printf("\n");
    //         break;

    //     case 4:
    //         generate_random_data(NB_VOTANT, NB_CANDIDAT);
    //         printf("\n");
    //         printf("-------------------------------------------------------------------------------------------\n");
    //         printf("\n");
    //         break;

    //     case 5:
    //         jeu_test_exercice_5();
    //         printf("\n");
    //         printf("-------------------------------------------------------------------------------------------\n");
    //         printf("\n");
    //         break;

    //     case 6:
    //         jeu_test_exercice_6();
    //         printf("\n");
    //         printf("-------------------------------------------------------------------------------------------\n");
    //         printf("\n");
    //         break;

    //     case 7:
    //         jeu_test_exercice_6bis();
    //         printf("\n");
    //         printf("-------------------------------------------------------------------------------------------\n");
    //         printf("\n");
    //         break;

    //     case 8:
    //         jeu_test_exercice_7();
    //         printf("\n");
    //         printf("-------------------------------------------------------------------------------------------\n");
    //         printf("\n");
    //         break;

    //     case 9:
    //         jeu_test_exercice_8();
    //         printf("\n");
    //         printf("-------------------------------------------------------------------------------------------\n");
    //         printf("\n");
    //         break;

    //     case 10:
    //         jeu_test_exercice_9();
    //         printf("\n");
    //         printf("-------------------------------------------------------------------------------------------\n");
    //         printf("\n");
    //         break;
    //     }
    // } while (rep != 0);
    // printf("Merci , et au revoir.\n");
    // jeu_test_exercice_1();
    // jeu_test_exercice_2();
    // jeu_test_exercice_3();
    // jeu_test_exercice_5();
    // jeu_test_exercice_6();
    // jeu_test_exercice_6bis();
    // jeu_test_exercice_7();
    // simulation_compute_proof_of_work();
    jeu_test_exercice_8();

    // int i = strncmp("0011011110111110111010100000111011010101001011110111100011001010010111101110100110100010100100001100000010001110111001111000000101111111011100010111110101111110010001011011110001100101011100010011011000001110011101100101011000111001111101100000011000111111", "00", 1);
    // printf("%d\n", i);
    // generate_random_data(100, 2);

    // jeu_test_exercice_5();

    return 0;
}
