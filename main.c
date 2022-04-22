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
    int rep;
    char buff[BUFFER_SIZE];
    do
    {
        printf("--------------------------------Que voulez-vous faire ?------------------------------------\n");
        menu();
        fgets(buff, BUFFER_SIZE, stdin);
        sscanf(buff, "%d\n", &rep);
        printf("\n");
        switch (rep)
        {
        case 1:
            jeu_test_exercice_1();
            printf("\n");
            printf("-------------------------------------------------------------------------------------------\n");
            printf("\n");
            break;

        case 2:
            jeu_test_exercice_2();
            printf("\n");
            printf("-------------------------------------------------------------------------------------------\n");
            printf("\n");
            break;

        case 3:
            jeu_test_exercice_3();
            printf("\n");
            printf("-------------------------------------------------------------------------------------------\n");
            printf("\n");
            break;

        case 4:
            generate_random_data(NB_VOTANT, NB_CANDIDAT);
            printf("\n");
            printf("-------------------------------------------------------------------------------------------\n");
            printf("\n");
            break;
        case 5:
            jeu_test_exercice_5();
            printf("\n");
            printf("-------------------------------------------------------------------------------------------\n");
            printf("\n");
            break;

        case 6:
            jeu_test_exercice_6();
            printf("\n");
            printf("-------------------------------------------------------------------------------------------\n");
            printf("\n");
            break;

        case 7:
            jeu_test_exercice_6bis();
            printf("\n");
            printf("-------------------------------------------------------------------------------------------\n");
            printf("\n");
            break;

        case 8:
            jeu_test_exercice_7();
            printf("\n");
            printf("-------------------------------------------------------------------------------------------\n");
            printf("\n");
            break;

        case 9:
            jeu_test_exercice_8();
            printf("\n");
            printf("-------------------------------------------------------------------------------------------\n");
            printf("\n");
            break;

        case 10:
            jeu_test_exercice_9();
            printf("\n");
            printf("-------------------------------------------------------------------------------------------\n");
            printf("\n");
            break;
        }
    } while (rep != 0);
    printf("Merci , et au revoir.\n");

    // Libre à vous de décommenter les lignes suivantes afin de tester les jeux de test

    // jeu_test_exercice_1();
    // jeu_test_exercice_2();
    // jeu_test_exercice_3();
    // generate_random_data(NB_VOTANT, NB_CANDIDAT);
    // jeu_test_exercice_5();
    // jeu_test_exercice_6();
    // jeu_test_exercice_6bis();
    // jeu_test_exercice_7();
    // jeu_test_exercice_8();
    // jeu_test_exercice_9();

    // AVANT DE TESTER LA FONCTION SUIVANTE, FAITES UN MAKE CLEAN !!!
    // simulationComplete();

    // jeu_test_create_random_block();
    // simulation_compute_proof_of_work();

    return 0;
}
