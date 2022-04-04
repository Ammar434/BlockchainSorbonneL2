#include "exercice4.h"

// Exercice 4
// Question 4.1

void generer_all_data(char *filename, int nv)
{
    // Genere carte electorale de toute la population
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("erreur lors de l'ouverture");
        return;
    }
    for (int i = 0; i < nv; i++)
    {
        Key *pKey = malloc(sizeof(Key));
        Key *sKey = malloc(sizeof(Key));
        init_pair_keys(pKey, sKey, 3, 7);
        char *tmp1 = key_to_str(pKey);
        char *tmp2 = key_to_str(sKey);
        fprintf(f, "%s %s\n", tmp1, tmp2);
        free(tmp1);
        free(tmp2);
        free(pKey);
        free(sKey);
    }
    fclose(f);
}

void generer_selection_candidat(char *filename, char *filename2, int nv, int nc)
{
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen(filename2, "w");
    int i = 0;
    char buffer[BUFFER_SIZE];
    char kPublic[BUFFER_SIZE];
    char kPrivee[BUFFER_SIZE];
    if (f == NULL || f2 == NULL)
    {
        printf("erreur lors de la lecture\n");
        return;
    }
    // Selection des candidats
    for (int j = 0; j < nc; j++)
    {
        int random = rand() % nv;
        printf("Candidat a la ligne %d se presente au election\n", random);
        while (fgets(buffer, sizeof(buffer), f) != 0)
        {
            i++;
            if (i == random)
            {
                sscanf(buffer, "%s %s", kPublic, kPrivee);
                printf("%s\n", buffer);
                fprintf(f2, "%s\n", kPublic);
                // printf("%s\n", kPublic);
                break;
            }
        }
        rewind(f);
        i = 0;
    }
    fclose(f);
    fclose(f2);
}

void generer_declaration_vote(char *filename, char *filename2, char *filename3, int nbCandidates)
{
    char buff[BUFFER_SIZE];
    char pKey[BUFFER_SIZE];
    char sKey[BUFFER_SIZE];
    char bufferCandidat[BUFFER_SIZE];
    char candidatPublic[BUFFER_SIZE];

    FILE *f = fopen(filename, "r");   // prendre toute la population
    FILE *f2 = fopen(filename2, "r"); // prendre tous les candidats
    FILE *f3 = fopen(filename3, "w"); // declaration de vote de chacun

    if (f == NULL || f2 == NULL || f3 == NULL)
    {
        printf("erreur lors de la lecture\n");
        return;
    }

    char *tmp;
    Signature *sgn;
    Protected *pr;
    int i = 0;

    while (fgets(buff, BUFFER_SIZE, f) != 0)
    {
        Key *publicKey = NULL;
        Key *secureKey = NULL;
        if (sscanf(buff, "%s %s", pKey, sKey) != 2)
        {
            printf("erreur lecture\n");
            return;
        }
        publicKey = str_to_key(pKey);
        secureKey = str_to_key(sKey);
        int votePour = rand() % (nbCandidates + 1);
        while (fgets(bufferCandidat, sizeof(bufferCandidat), f2) != 0)
        {
            i++;
            if (i == votePour)
            {
                sscanf(bufferCandidat, "%s\n", candidatPublic);
                break;
            }
        }

        tmp = key_to_str(publicKey);
        printf("%s vote pour %s \n", tmp, candidatPublic);
        free(tmp);
        sgn = sign(candidatPublic, secureKey);
        pr = init_protected(publicKey, candidatPublic, sgn);
        tmp = protected_to_str(pr);
        fprintf(f3, "%s\n", tmp);

        i = 0;
        rewind(f2);
        free(tmp);
        free(publicKey);
        free(secureKey);
        free(sgn->tab);
        free(sgn);
        free(pr->message);
        free(pr);
    }
    fclose(f);
    fclose(f2);
    fclose(f3);
}

// version d'avant
// void generer_declaration_vote(char *filename, char *filename2, char *filename3, int nbCandidates)
// {
//     Key **tabCandidates = malloc(sizeof(Key *) * nbCandidates);

//     char buff[BUFFER_SIZE];
//     char pKey[BUFFER_SIZE];
//     char sKey[BUFFER_SIZE];

//     int elemAtTabCandidates = 0;

//     FILE *f = fopen(filename, "r");   // prendre toute la population
//     FILE *f2 = fopen(filename2, "r"); // prendre tous les candidats
//     FILE *f3 = fopen(filename3, "w"); // declaration de vote de chacun

//     if (f == NULL || f2 == NULL || f3 == NULL)
//     {
//         printf("erreur lors de la lecture\n");
//         return;
//     }

//     char *mess;
//     Signature *sgn;
//     Protected *pr;

//     // Generer tab candidat
//     while (fgets(buff, BUFFER_SIZE, f2) != 0)
//     {
//         if (sscanf(buff, "%s", pKey) != 1)
//         {
//             printf("erreur lecture\n");
//         }
//         Key *candidatKey = str_to_key(pKey);
//         tabCandidates[elemAtTabCandidates] = candidatKey;
//         elemAtTabCandidates++;
//     }

//     while (fgets(buff, BUFFER_SIZE, f) != 0)
//     {
//         Key *publicKey = NULL;
//         Key *secureKey = NULL;
//         if (sscanf(buff, "%s %s", pKey, sKey) != 2)
//         {
//             printf("erreur lecture\n");
//             return;
//         }
//         publicKey = str_to_key(pKey);
//         secureKey = str_to_key(sKey);
//         int votePour = rand() % nbCandidates;
//         mess = key_to_str(tabCandidates[votePour]);
//         char *messageKeyToStr = key_to_str(publicKey);
//         printf("%s vote pour %s \n", messageKeyToStr, mess);

//         sgn = sign(mess, secureKey);

//         pr = init_protected(publicKey, mess, sgn);
//         // printf("%s\n", protected_to_str(pr));
//         char *chaineDeProtected = protected_to_str(pr);
//         fprintf(f3, "%s\n", chaineDeProtected);
//         free(publicKey);
//         free(chaineDeProtected);
//         free(secureKey);
//         free(messageKeyToStr);
//         free(sgn->tab);
//         free(sgn);
//         free(pr->message);
//         free(pr);
//         free(mess);
//     }

//     for (int i = 0; i < nbCandidates; i++)
//         free(tabCandidates[i]);
//     free(tabCandidates);
//     fclose(f);
//     fclose(f2);
//     fclose(f3);
// }

void generate_random_data(int nv, int nc)
{
    // Creation fichier toutes les clés
    char *filename = "election_donnee/keys.txt";
    char *filename2 = "election_donnee/candidates.txt";
    char *filename3 = "election_donnee/declaration.txt";
    generer_all_data(filename, nv);
    generer_selection_candidat(filename, filename2, nv, nc);
    generer_declaration_vote(filename, filename2, filename3, nc);
}
