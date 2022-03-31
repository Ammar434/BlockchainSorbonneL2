#include "src/jeuDeTest.h"
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
    //         jeu_test_exercice_2();
    //         printf("\n");
    //         printf("-------------------------------------------------------------------------------------------\n");
    //         printf("\n");
    //         break;

    //     case 2:
    //         jeu_test_exercice_3();
    //         printf("\n");
    //         printf("-------------------------------------------------------------------------------------------\n");
    //         printf("\n");
    //         break;

    //     case 3:
    //         printf("Veuillez ecrire le nv et le nc de la fonction generate_random_data\n");
    //         fgets(buff, BUFFER_SIZE, stdin);
    //         cpt = sscanf(buff, "%d %d\n", &nv, &nc);
    //         if (cpt == 2)
    //         {
    //             generate_random_data(nv, nc);
    //             printf("\n");
    //             printf("-------------------------------------------------------------------------------------------\n");
    //             printf("\n");
    //         }
    //         else
    //         {
    //             printf("Erreur format\n");
    //             printf("\n");
    //             printf("-------------------------------------------------------------------------------------------\n");
    //             printf("\n");
    //         }
    //         break;
    //     }
    // } while (rep != 0);
    // printf("Merci , et au revoir.\n");

    // jeu_test_exercice_3();
    generate_random_data(1000, 5);

    // CellProtected *cp = read_protected_from_file("election_donnee/declaration.txt");
    // print_list_protected(cp);
    // cp = supprimer_fausse_signature(cp);
    CellKey *lc = read_public_keys("election_donnee/candidates.txt");
    CellKey *lp = read_public_keys("election_donnee/keys.txt");
    CellProtected *cp = read_protected_from_file("election_donnee/declaration.txt");

    // print_list_protected(cp);
    // HashTable *hash = create_hashtable(lp, 100);
    // afficher_hashtable(hash);
    // Key *k = malloc(sizeof(Key));
    // init_key(k, 4181, 13511);
    // find_position(hash, k);
    Key *vainqueur = compute_winner(cp, lc, lp, 10, 1500);
    delete_list_protected(cp);
    delete_list_keys(lc);
    delete_list_keys(lp);
    free(vainqueur);

    return 0;
}
