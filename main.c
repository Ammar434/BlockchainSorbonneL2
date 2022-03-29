#include "jeuDeTest.h"
void menu()
{
    printf("0 - Sortie du programme\n");
    printf("1 - jeu_test_exercice_2\n");
    printf("2 - jeu_test_exercice_3\n");
    printf("3 - jeu_test_exercice_4\n");
}

int main()
{
    srand(time(NULL));
    int rep;
    char buff[BUFFER_SIZE];
    int nv, nc, cpt;
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
            jeu_test_exercice_2();
            printf("\n");
            printf("-------------------------------------------------------------------------------------------\n");
            printf("\n");
            break;

        case 2:
            jeu_test_exercice_3();
            printf("\n");
            printf("-------------------------------------------------------------------------------------------\n");
            printf("\n");
            break;

        case 3:
            printf("Veuillez ecrire le nv et le nc de la fonction generate_random_data\n");
            fgets(buff, BUFFER_SIZE, stdin);
            cpt = sscanf(buff, "%d %d\n", &nv, &nc);
            if (cpt == 2)
            {
                generate_random_data(nv, nc);
                printf("\n");
                printf("-------------------------------------------------------------------------------------------\n");
                printf("\n");
            }
            else
            {
                printf("Erreur format\n");
                printf("\n");
                printf("-------------------------------------------------------------------------------------------\n");
                printf("\n");
            }
            break;
        }
    } while (rep != 0);
    printf("Merci , et au revoir.\n");

    // CellProtected *cp = read_protected_from_file("election_donnee/declaration.txt");
    // // print_list_protected(cp);
    // // delete_list_protected(cp);
    // cp = supprimer_fausse_signature(cp);
    // // verify(cp->data);
    return 0;
}
