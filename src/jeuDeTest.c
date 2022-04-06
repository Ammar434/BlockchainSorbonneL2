#include "jeuDeTest.h"
#include "jeuDeTest.h"

void jeu_test_exercice_1()
{
    printf("Q.1.1\n");
    if (is_prime_naive(2))
    {
        printf("2 est premier\n");
    }
    else
    {
        printf("2 n'est pas premier\n");
    }

    if (is_prime_naive(53))
    {
        printf("53 est premier\n");
    }
    else
    {
        printf("53 n'est pas premier\n");
    }

    if (is_prime_naive(4))
    {
        printf("4 est premier\n");
    }
    else
    {
        printf("4 n'est pas premier\n");
    }
    printf("\n");

    printf("Q.1.3\n");
    printf("2^2 mod 2 = %ld\n", modpow_naive(2, 2, 2));
    printf("5^5 mod 4 = %ld\n", modpow_naive(5, 5, 4));
    printf("\n");

    printf("Q.1.4\n");
    printf("2^2 mod 2 = %ld\n", modpow(2, 2, 2));
    printf("5^5 mod 4 = %ld\n", modpow(5, 5, 4));
    printf("\n");

    printf("Q.1.8\n");
    printf("low : 10, up : 100, k : 5 -> random_prime_number(10,100,5) = %ld\n", random_prime_number(10, 100, 5));
}

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
    // Testing Init Keys
    Key *pKey = malloc(sizeof(Key));
    Key *sKey = malloc(sizeof(Key));
    init_pair_keys(pKey, sKey, 3, 7);
    printf("pKey: %lx, %lx \n", pKey->a, pKey->b);
    printf("sKey: %lx, %lx \n", sKey->a, sKey->b);

    // Testing Key Serialization
    char *chaine = key_to_str(pKey);
    printf("keytostr: %s\n", chaine);
    Key *k = str_to_key(chaine);
    printf("strtokey: %lx, %lx\n", k->a, k->b);
    free(chaine);

    // Testing signature
    // Candidate keys:
    Key *pKeyC = malloc(sizeof(Key));
    Key *sKeyC = malloc(sizeof(Key));
    init_pair_keys(pKeyC, sKeyC, 3, 7);

    // Declaration:
    char *mess = key_to_str(pKeyC);
    char *mess2 = key_to_str(pKey);
    printf("%s vote pour %s \n", mess2, mess);
    free(mess2);

    Signature *sgn = sign(mess, sKey);
    printf("signature ");
    print_long_vector(sgn->tab, sgn->size);
    chaine = signature_to_str(sgn);
    free(sgn->tab);
    free(sgn);

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
    free(chaine);

    chaine = protected_to_str(pr);
    printf("protected to str: %s\n", chaine);

    free(pr->message);
    free(pr);
    pr = str_to_protected(chaine);

    mess2 = key_to_str(pr->pKey);
    char *mess3 = signature_to_str(pr->signature);
    printf("str to protected: %s %s %s \n", mess2, pr->message, mess3);

    free(pKey);
    free(sKey);
    free(pKeyC);
    free(sKeyC);
    free(k);
    free(chaine);
    free(mess);
    free(mess2);
    free(mess3);
    free(sgn->tab);
    free(sgn);
    free(pr->pKey);
    free(pr->signature->tab);
    free(pr->signature);
    free(pr->message);
    free(pr);
}

// void jeu_test_exercice_5()
// {
//     // Creation de la clé
//     Key *k = (Key *)(malloc(sizeof(Key)));
//     k->a = 1;
//     k->b = 2;
//     // Ajout à une CellKey
//     CellKey *c = create_cell_key(NULL);
//     add_key_to_head(&c, k);

//     // Affichage de la liste
//     print_list_keys(c);

//     // Suppresion de la liste de cle
//     delete_list_keys(c);

//     // Lecture d'un fichier
//     CellKey *c2 = read_public_keys("election_donnee/candidates.txt");

//     // Lecture et suppression de la liste
//     print_list_keys(c2);
//     delete_list_keys(c2);

//     // Creation d'une clé
//     Key *k3 = (Key *)(malloc(sizeof(Key)));
//     k3->a = 1;
//     k3->b = 2;
//     Key *k4 = (Key *)(malloc(sizeof(Key)));
//     k4->a = 1;
//     k4->b = 2;

//     char *tmp = key_to_str(k3);

//     // variable Signature
//     Signature *signature = sign(tmp, k4);

//     // variable Protected
//     Protected *p = init_protected(k3, tmp, signature);

//     // Ajout à une liste de Protected
//     CellProtected *p2 = create_cell_protected(NULL);
//     add_cell_protected_to_head(&p2, p);

//     // Affichage de la liste Protected
//     print_list_protected(p2);

//     free(tmp);
//     // Suppresion de la liste Protected
//     delete_list_protected(p2);

//     // free
//     free(k4);

//     // Lecture d'un fichier
//     CellProtected *p3 = read_protected_from_file("election_donnee/declaration.txt");

//     // Lecture et suppression de la liste
//     print_list_protected(p3);
//     delete_list_protected(p3);
// }

void jeu_test_exercice_6()
{
    CellProtected *cp = read_protected_from_file("election_donnee/declaration.txt");
    printf("Liste avant supprimer_fausse_signature\n");
    print_list_protected(cp);

    printf("Liste apres supprimer_fausse_signature\n");
    supprimer_fausse_signature(&cp);
    print_list_protected(cp);

    delete_list_protected(cp);
}

void jeu_test_exercice_6bis()
{
    int nc = 10;
    int nv = 11;

    generate_random_data(nv, nc);
    CellKey *lc = read_public_keys("election_donnee/candidates.txt");
    CellKey *lp = read_public_keys("election_donnee/keys.txt");
    CellProtected *cp = read_protected_from_file("election_donnee/declaration.txt");
    // supprimer_fausse_signature(&cp);
    print_list_protected(cp);
    // HashTable *hash = create_hashtable(lp, 20);
    // afficher_hashtable(hash);

    Key *vainqueur = compute_winner(cp, lc, lp, nc + 10, nv * 1.2);

    delete_list_keys(lc);
    delete_list_keys(lp);
    delete_list_protected(cp);
    free(vainqueur);

    // // Creation de la table de hachage
    // HashCell *h = create_hashcell(k1);

    // // Lecture d'un fichier candidates.txt
    // CellKey *ck = read_public_keys("election_donnee/candidates.txt");

    // // Creation d'une HashTable
    // HashTable *hash = create_hashtable(ck, 20);

    // // Q.6.2
    // // Creation de 2 clés
    // Key *k1 = (Key *)(malloc(sizeof(Key)));
    // k1->a = 1;
    // k1->b = 2;
    // Key *k2 = (Key *)(malloc(sizeof(Key)));
    // k2->a = 3;
    // k2->b = 4;

    // // Creation de 2 HashCell
    // printf("Q.6.2\n");
    // HashCell *hc = create_hashcell(k1);
    // HashCell *hc2 = create_hashcell(k2);
    // printf("hc de valeur %d et de cle a = %ld et b = %ld\n", hc->val, hc->key->a, hc->key->b);
    // printf("hc2 de valeur %d et de cle a = %ld et b = %ld\n", hc->val, hc2->key->a, hc2->key->b);
    // printf("\n");

    // // Q.6.3
    // // Position des clé k1 et k2 dans la table de hachage
    // printf("Q.6.3\n");
    // int pos1 = hash_function(k1, 10);
    // int pos2 = hash_function(k2, 10);
    // printf("pos1 a pour position %d. C'est hc de valeur %d et de cle a = %ld et b = %ld\n", pos1, hc->val, hc->key->a, hc->key->b);
    // printf("pos2 a pour position %d. C'est hc2 de valeur %d et de cle a = %ld et b = %ld\n", pos2, hc2->val, hc2->key->a, hc2->key->b);
    // printf("\n");

    // // Q.6.4 et 6.5
    // printf("Q.6.4 et Q.6.5\n");
    // // Creation d'une CellKey
    // CellKey *ck = create_cell_key(k2);
    // CellKey **liste = &ck;
    // add_key_to_head(liste, k1);

    // CellKey *tmp = *liste;
    // int cpt = 1;
    // while (tmp)
    // {
    //     printf("Element %d de la liste : a = %ld et b = %ld\n", cpt, tmp->key->a, tmp->key->b);
    //     tmp = tmp->next;
    //     cpt++;
    // }
    // printf("\n");

    // // Creation d'une Hashtable et cherchons la position de k1 et k2 dans la Hashtable
    // HashTable *ht = create_hashtable(*liste, 10);
    // printf("\n");

    // // Cherchons la position de k3 non present dans la Hashtable
    // printf("Cherchons la position de k3 non present dans la Hashtable\n");
    // Key *k3 = (Key *)(malloc(sizeof(Key)));
    // k3->a = 5;
    // k3->b = 6;
    // printf("Position de k3 (non present dans la HashTable) : %d\n", find_position(ht, k3));
    // printf("\n");

    // // Q.6.6
    // // Affichage de la Hashtable
    // afficher_hashtable(ht);
    // printf("\n");

    // // Comptons le nombre d'element dans la Hashtable
    // count_element_hashtable(ht);
    // printf("\n");
    // // Suppression de la HashTable
    // delete_hashtable(ht);
    // if (ht == NULL)
    // {
    //     printf("Suppression de la HashTable avec succes\n");
    // }

    // // free
    // free(k3);
    // free(hc);
    // free(hc2);
}

void jeu_test_exercice_7()
{
    const char *s = "0MAthias";
    unsigned char *d = SHA256(s, strlen(s), 0);
    int i;
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
        printf("%02x", d[i]);
    putchar('\n');

    str_to_SHA256(s);
    // Block *b = read_block_from_file("election_donnee/test.txt");
}