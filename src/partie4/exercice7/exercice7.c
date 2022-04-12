#include "exercice7.h"

void print_hash(unsigned char *hash)
{
    printf("Hash : ");

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        printf("%02x", hash[i]);
    printf("\n");
}

// Question 7.1
void write_block_to_file(Block *b)
{
    char *path = "election_donnee/blocks/";
    char *author = key_to_str(b->author);
    char *extension = ".txt";
    int len = (strlen(path) + strlen(author) + strlen(extension) + 1);
    char *filename = malloc(sizeof(char) * len);
    memset(filename, 0, len);
    strcat(strcat(strcat(filename, path), author), extension);
    printf("%s\n", filename);

    FILE *f = fopen(filename, "w");

    if (f == NULL)
    {
        printf("erreur lors de l'ouverture\n");
        return;
    }

    // Ecriture de l’auteur du bloc, sa valeur hachee, la valeur hachee du bloc precedent, sa preuve de travail
    // fprintf(f, "%s %d %02x %02x", author, b->nonce, b->hash, b->previous_hash);

    fprintf(f, "%s %d ", author, b->nonce);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        // fputc((b->hash)[i], f);
        fprintf(f, "%02x", (b->hash)[i]);
    fprintf(f, " ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        fprintf(f, "%02x", b->previous_hash[i]);
    fprintf(f, "\n");

    // Ecriture de toutes les declarations de votes
    CellProtected *tmp = b->votes;
    while (tmp != NULL)
    {
        char *ptr = protected_to_str(tmp->data);
        fprintf(f, "%s\n", ptr);
        free(ptr);
        tmp = tmp->next;
    }
    free(author);
    free(filename);

    fclose(f);
}

unsigned char *unsigned_strdup(char *chaine)
{
    int i = 0;
    int len = strlen(chaine);
    printf("Len chaine %d\n", len);
    unsigned char *unsigned_chaine = malloc(sizeof(unsigned char) * (len + 1));

    // memcpy(unsigned_chaine, chaine, SHA256_DIGEST_LENGTH);
    for (i = 0; i < len; i++)
    {
        unsigned_chaine[i] = (unsigned char)(chaine[i]);
        //     // printf("%s", chaine);
        //     // sprintf(unsigned_chaine, "%s", chaine);
        //     // unsigned_chaine[i] = chaine[i];
    }
    unsigned_chaine[i] = '\0';
    printf("%s\n", unsigned_chaine);

    // print_hash(unsigned_chaine);
    // printf("\n");

    return unsigned_chaine;
}
// Question 7.2
Block *read_block_from_file(char *filename)
{
    Block *newBlock = malloc(sizeof(Block));
    newBlock->hash = NULL;
    newBlock->previous_hash = NULL;
    newBlock->author = NULL;
    newBlock->votes = NULL;
    newBlock->nonce = 0;

    char buff[BUFFER_SIZE];
    char auteur[BUFFER_SIZE];
    unsigned char hash[BUFFER_SIZE];
    unsigned char previous_hash[BUFFER_SIZE];
    char protected_text[BUFFER_SIZE];
    int nonce = 0;
    size_t n = 0;

    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("erreur lors de l'ouverture");
        return NULL;
    }
    fgets(buff, BUFFER_SIZE, f);

    if (sscanf(buff, "%s %d %s %s", auteur, &nonce, hash, previous_hash) != 4)
    {
        printf("erreur lecture\n");
        return NULL;
    }

    print_hash(hash);

    newBlock->author = str_to_key(auteur);
    newBlock->hash = unsigned_strdup(hash);
    newBlock->previous_hash = unsigned_strdup(previous_hash);

    // printf("%s\n", newBlock->hash);
    // print_hash(newBlock->hash);
    // print_hash(newBlock->hash);
    // print_hash(newBlock->previous_hash);

    newBlock->nonce = nonce;

    while (fgets(buff, BUFFER_SIZE, f) != 0)
    {
        if (sscanf(buff, "%[^\n]", protected_text) != 1)
        {
            printf("erreur lecture\n");
            return NULL;
        }
        Protected *protected = temporaire(protected_text);
        add_cell_protected_to_head(&(newBlock->votes), protected);
    }

    fclose(f);
    return newBlock;
}

long int len_block(Block *block)
{
    long int len = 0;
    char *auteur = key_to_str(block->author);
    int nDigits = (block->nonce == 0) ? 1 : floor(log10(abs(block->nonce))) + 1;
    len = strlen(auteur) + SHA256_DIGEST_LENGTH + nDigits + 1 + 1 + 1;

    CellProtected *tmp = block->votes;
    while (tmp != NULL)
    {
        char *chaine = protected_to_str(tmp->data);
        len = len + strlen(chaine) + 1;
        free(chaine);
        tmp = tmp->next;
    }
    free(auteur);
    return len;
}
// Question 7.3
char *block_to_str(Block *block)
{
    int len = 0;
    char *res = NULL;
    if (block == NULL)
    {
        printf("Block null\n");
        // res = strdup("Premier block");
        return res;
    }

    len = len_block(block);

    res = malloc(sizeof(char) * (len));

    if (res == NULL)
    {
        return NULL;
    }

    memset(res, 0, len);

    char *auteur = key_to_str(block->author);

    // strcat(res, auteur);
    memcpy(res, auteur, strlen(auteur));
    memcpy(res + strlen(auteur), block->previous_hash, SHA256_DIGEST_LENGTH);

    // strcat(res, (char *)block->previous_hash);
    char nonce_to_str[BUFFER_SIZE];
    snprintf(nonce_to_str, sizeof(nonce_to_str), "%d", block->nonce);
    strcat(res, nonce_to_str);
    strcat(res, "\n");
    CellProtected *tmp = block->votes;
    while (tmp != NULL)
    {
        char *chaine = protected_to_str(tmp->data);
        strcat(res, chaine);
        strcat(res, "\n");
        free(chaine);
        tmp = tmp->next;
    }
    res[len - 1] = '\0';
    free(auteur);
    return res;
}

void delete_block(Block *block)
{
    delete_list_protected(block->votes);
    free(block->hash);
    free(block->previous_hash);
    free(block->author);
    free(block);
}

// Question 7.5
unsigned char *str_to_SHA256(char *chaine)
{
    // unsigned char *d = SHA256((unsigned char *)chaine, sizeof(chaine), 0);

    unsigned char *d = malloc(sizeof(unsigned char) * SHA256_DIGEST_LENGTH);
    d = SHA256((unsigned char *)chaine, strlen(chaine), d);
    print_hash(d);
    return d;
}

char *hex_to_bin(unsigned char *hexdec)
{
    long int i = 0;
    int len_chaine = strlen((char *)hexdec);
    char *chaine = malloc(sizeof(char) * (len_chaine * 4 + 1));
    memset(chaine, 0, len_chaine * 4 + 1);
    while (hexdec[i])
    {
        switch (hexdec[i])
        {
        case '0':
            // printf("0000");
            strcat(chaine, "0000");
            // memcpy(chaine, "0000", 4);

            break;
        case '1':
            // printf("0001");
            strcat(chaine, "0001");

            break;
        case '2':
            // printf("0010");
            strcat(chaine, "0010");

            break;
        case '3':
            // printf("0011");
            strcat(chaine, "0011");

            break;
        case '4':
            // printf("0100");
            strcat(chaine, "0100");

            break;
        case '5':
            // printf("0101");
            strcat(chaine, "0101");

            break;
        case '6':
            // printf("0110");
            strcat(chaine, "0110");

            break;
        case '7':
            // printf("0111");
            strcat(chaine, "0111");

            break;
        case '8':
            // printf("1000");
            strcat(chaine, "1000");

            break;
        case '9':
            // printf("1001");
            strcat(chaine, "1001");

            break;
        // case 'A':
        case 'a':
            // printf("1010");
            strcat(chaine, "1010");

            break;
        // case 'B':
        case 'b':
            // printf("1011");
            strcat(chaine, "1011");

            break;
        // case 'C':
        case 'c':
            // printf("1100");
            strcat(chaine, "1100");

            break;
        // case 'D':
        case 'd':
            // printf("1101");
            strcat(chaine, "1101");

            break;
        // case 'E':
        case 'e':
            // printf("1110");
            strcat(chaine, "1110");

            break;
        // case 'F':
        case 'f':
            // printf("1111");
            strcat(chaine, "1111");
            break;
            // default:
            //     printf("\nInvalid hexadecimal digit %c",
            //            hexdec[i]);
        }
        i++;
    }
    // printf("i =%d\n", i);
    // printf("len =%d\n", strlen(hexdec));
    chaine[i * 4] = '\0';
    // printf("%s\n", chaine);
    return chaine;
}

// Question 7.6
void compute_proof_of_work(Block *block, int d)
{
    int i = 0;
    int nonce = 0;
    char nonce_to_str[BUFFER_SIZE];

    // Creation de la chaine commencant par n zeros
    char *chaine_a_comparer = malloc(sizeof(char) * (d + 1));
    for (i = 0; i < d; i++)
    {
        chaine_a_comparer[i] = '0';
    }
    chaine_a_comparer[i] = '\0';
    printf("Chaine à comparer : %s\n", chaine_a_comparer);

    char *block_str = NULL;
    int len_block_str = 0;

    char *block_str_with_nonce = NULL;

    unsigned char *block_hash = NULL;
    char *hexadecimal = NULL;
    char buffer[BUFFER_SIZE];
    char *binary = NULL;
    // sleep(2);
    int h = 0;
    while (1)
    {
        snprintf(nonce_to_str, sizeof(int), "%d", nonce);
        block_str = block_to_str(block);
        len_block_str = strlen(block_str);
        block_str_with_nonce = malloc(sizeof(char) * (len_block_str + strlen(nonce_to_str) + 1));
        memset(block_str_with_nonce, 0, len_block_str + strlen(nonce_to_str) + 1);
        strcat(strcat(block_str_with_nonce, block_str), nonce_to_str);
        block_hash = str_to_SHA256(block_str_with_nonce);

        // printf("%s\n", block_str_with_nonce);
        print_hash(block_hash);
        hexadecimal = malloc(sizeof(char) * BUFFER_SIZE);
        memset(hexadecimal, 0, BUFFER_SIZE);
        printf("Reprensentation hexadecimal hash block : ");
        for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
        {
            printf("%02x", block_hash[i]);
            sprintf(buffer, "%02x", block_hash[i]);
            strcat(hexadecimal, buffer);
        }

        printf("\nReprensentation binaire hash block :\n");
        binary = hex_to_bin(hexadecimal);
        printf("%s\n", binary);

        printf("\n");
        // Si commence par n zero alors on a completer preuve de travail

        if (strncmp(chaine_a_comparer, binary, d) == 0)
        {
            printf("---------------------------------------\n");
            printf("%s\n", binary);
            printf("---------------------------------------\n");
            break;
        }

        free(binary);
        free(block_str);
        free(block_str_with_nonce);
        free(block_hash);
        free(hexadecimal);
        nonce++;
    }
    block->nonce = d;
    block->hash = unsigned_strdup(hexadecimal);
    // free(block_hash);

    // // free(hexadecimal);
    // free(block_str);
    // free(block_str_with_nonce);
    free(binary);
    free(chaine_a_comparer);
    free(block_str);
    free(block_str_with_nonce);
    free(block_hash);
    free(hexadecimal);
}

// Question 7.7
// Pas sur que verify marche
int verify_block(Block *block, int d)
{
    int i = 0;
    char *chaine_a_comparer = malloc(sizeof(char) * (d + 1));
    for (i = 0; i < d; i++)
    {
        chaine_a_comparer[i] = '0';
    }
    chaine_a_comparer[i] = '\0';
    printf("Chaine à comparer : %s\n", chaine_a_comparer);
    char *binary = hex_to_bin(block->hash);
    if (strncmp(chaine_a_comparer, binary, d) == 0)
    {
        printf("Block valide\n");
        return 1;
    }
    free(chaine_a_comparer);
    free(binary);
    return 0;
}

// Question 7.8
void simulation_compute_proof_of_work()
{
    clock_t temps_initial;
    clock_t temps_final;
    float temps_cpu;
    char *nom_fichier = "courbe_donnee/generer_data_compute_proof_of_work.txt";
    float somme_temps = 0;
    FILE *file = fopen(nom_fichier, "w");
    for (int d = 1; d < 12; d++)
    {
        generate_random_data(100, 10);
        Key *pKey = malloc(sizeof(Key));
        Key *sKey = malloc(sizeof(Key));
        Block *block = (Block *)(malloc(sizeof(Block)));
        init_pair_keys(pKey, sKey, 7, 3);
        block->votes = read_protected_from_file("election_donnee/declaration.txt");
        block->nonce = 0;
        block->author = pKey;
        block->previous_hash = str_to_SHA256("");
        somme_temps = 0;
        for (int i = 0; i < 10; i++)
        {
            // printf("%s\n", block_to_str(block));
            temps_initial = clock();
            compute_proof_of_work(block, d);
            temps_final = clock();
            temps_cpu = (temps_final - temps_initial) * pow(10, -6);
            somme_temps = somme_temps + temps_cpu;
            printf("Iteration %d pour %d nb zero Duree %f\n", i, d, temps_cpu);
            // free(pKey);
        }
        delete_block(block);
        free(sKey);
        block = NULL;
        somme_temps = somme_temps / 10;
        printf("%lf\n", somme_temps);
        fprintf(file, "%d %f\n", d, (somme_temps));
    }
    fclose(file);
}