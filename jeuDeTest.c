#include "jeuDeTest.h"

void jeu_test_exercice_2()
{
    // Exercice 2
    printf("Jeux de tests exercice 2\n");
    srand(time(NULL));

    // Generation de cle :
    long p = random_prime_number(3, 7, 5000);
    long q = random_prime_number(3, 7, 5000);
    while (p == q)
    {
        q = random_prime_number(3, 7, 5000);
    }
    long n, s, u;
    generate_key_values(p, q, &n, &s, &u);

    // Pour avoir des cles positives :
    if (u < 0)
    {
        long t = (p - 1) * (q - 1);
        u = u + t; // on aura toujours s*u mod t = 1
    }

    // Afichage des cles en hexadecimal
    printf("cle publique = (%lx , %lx)\n", s, n);
    printf("cle privee = (%lx , %lx)\n", u, n);

    // Chiffrement:
    char mess[10] = "Hello";
    int len = strlen(mess);
    long *crypted = encrypt(mess, s, n);

    printf("Initial message : %s\n", mess);
    printf("Encoded representation : \n");
    print_long_vector(crypted, len);

    // Dechiffrement
    char *decoded = decrypt(crypted, len, u, n);
    printf("Decoded : %s \n", decoded);

    free(crypted);
    free(decoded);

    printf("\n");
}

void jeu_test_exercice_3()
{
    Key *pKey = malloc(sizeof(Key));
    Key *sKey = malloc(sizeof(Key));
    init_pair_keys(pKey, sKey, 3, 7);
    printf("pKey: %lx, %lx \n", pKey->a, pKey->b);
    printf("sKey: %lx, %lx \n", sKey->a, sKey->b);
    char *chaine = key_to_str(pKey);
    printf("keytostr: %s\n", chaine);
    Key *k = str_to_key(chaine);
    printf("strtokey: %lx, %lx\n", k->a, k->b);
    // Testing signature
    // Candidate keys:
    Key *pKeyC = malloc(sizeof(Key));
    Key *sKeyC = malloc(sizeof(Key));
    init_pair_keys(pKeyC, sKeyC, 3, 7);
    // Declaration:
    char *mess = key_to_str(pKeyC);
    printf("%s vote pour %s \n", key_to_str(pKey), mess);
    Signature *sgn = sign(mess, sKey);
    printf("signature ");
    print_long_vector(sgn->tab, sgn->size);
    chaine = signature_to_str(sgn);
    printf("signature to str: %s \n", chaine);
    sgn = str_to_signature(chaine);
    printf("str to signature ");
    print_long_vector(sgn->tab, sgn->size);
    // Testing protected:
    Protected *pr = init_protected(pKey, mess, sgn);

    // Verification:
    if (verify(pr))
    {
        printf("Signature valide\n");
    }
    else
    {
        printf("Signature invalide\n");
    }
    chaine = protected_to_str(pr);
    printf("protected to str: %s\n", chaine);
    pr = str_to_protected(chaine);
    printf("str to protected: %s %s %s \n", key_to_str(pr->pKey), pr->message, signature_to_str(pr->signature));
}

void get_line_from_file(char *filename, char *filename2, int lineValue)
{
    int i = 0;
    char buffer[BUFFER_SIZE];
    char kPublic[BUFFER_SIZE];
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen(filename2, "aw");

    if (f == NULL || f2 == NULL)
    {
        printf("erreur lors de la lecture\n");
    }
    while (fgets(buffer, sizeof(buffer), f))
    {
        i++;
        if (i == lineValue)
        {
            sscanf(buffer, " %s", kPublic);
            fprintf(f2, "%s\n", kPublic);
            // printf("%s\n", kPublic);
            break;
        }
    }

    fclose(f);
    fclose(f2);
}
// a revoir
void generer_declaration_vote(char *filename, char *filename2, char *filename3, int nbCandidates)
{
    Key **tabCandidates = malloc(sizeof(Key *) * nbCandidates);
    for (int i = 0; i < nbCandidates; i++)
    {
        tabCandidates[i] = malloc(sizeof(Key));
    }

    char buff[BUFFER_SIZE];
    char pKey[BUFFER_SIZE];
    char sKey[BUFFER_SIZE];

    int elemAtTabCandidates = 0;

    FILE *f = fopen(filename, "r");   // prendre toute la population
    FILE *f2 = fopen(filename2, "r"); // prendre tous les candidats
    FILE *f3 = fopen(filename3, "w"); // declaration de vote de chacun

    if (f == NULL || f2 == NULL || f3 == NULL)
    {
        printf("erreur lors de la lecture\n");
        return;
    }

    char *mess;
    Signature *sgn;
    Protected *pr;
    char *chaine;

    // Generer tab candidat
    while (fgets(buff, BUFFER_SIZE, f2) != 0)
    {
        if (sscanf(buff, "%s", pKey) != 1)
        {
            printf("erreur lecture\n");
        }
        Key *candidatKey = malloc(sizeof(Key));
        candidatKey = str_to_key(pKey);
        tabCandidates[elemAtTabCandidates] = candidatKey;
        elemAtTabCandidates++;
    }

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

        int votePour = rand() % nbCandidates;

        mess = key_to_str(tabCandidates[votePour]);

        // printf("%s vote pour %s \n", key_to_str(publicKey), mess);

        printf("Message %s\n", mess);
        printf("privee %s\n", sKey);
        // sgn = sign(mess, secureKey);

        // pr = init_protected(publicKey, mess, sgn);

        // chaine = protected_to_str(pr);

        // fprintf(f3, "%s\n", chaine);
        free(publicKey);
        free(secureKey);
    }

    fclose(f);
    fclose(f2);
    fclose(f3);
}

void generate_random_data(int nv, int nc)
{

    // Creation fichier toutes les clés
    FILE *f = fopen("keys.txt", "w");
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
        fprintf(f, "%s %s\n", key_to_str(pKey), key_to_str(sKey));
        free(pKey);
        free(sKey);
    }
    fclose(f);

    // Selection des candidats
    for (int i = 0; i < nc; i++)
    {
        int random = rand() % nv;
        printf("Candidat a la ligne %d se presente au election\n", random);
        get_line_from_file("keys.txt", "candidates.txt", random);
    }
    generer_declaration_vote("keys.txt", "candidates.txt", "declaration.txt", nc);
}