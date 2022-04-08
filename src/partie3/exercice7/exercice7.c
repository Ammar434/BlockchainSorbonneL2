#include "exercice7.h"

// Question 7.1
void write_block_to_file(Block b)
{
    char *filename = "election_donnee/block";
    char *author = key_to_str(b.author);
    // printf("%s", strcat(filename, author));

    // FILE *f = fopen(strcat(filename, author), "w");
    FILE *f = fopen(filename, "w");

    if (f == NULL)
    {
        printf("erreur lors de l'ouverture");
        return;
    }

    // Ecriture de l’auteur du bloc, sa valeur hachee, la valeur hachee du bloc precedent, sa preuve de travail
    fprintf(f, "%s %s %s %d ", author, (unsigned char *)b.hash, (unsigned char *)b.previous_hash, b.nonce);
    free(author);

    // Ecriture de toutes les declarations de votes
    // Je n'arrive pas à faire, il ya une erreur de segmentation
    CellProtected *tmp = b.votes;
    while (tmp)
    {
        char *ptr = protected_to_str(tmp->data);
        fprintf(f, "%s ", ptr);
        tmp = tmp->next;
    }
    fprintf(f, "\n");
    fclose(f);
}

// // Question 7.2
// Block *read_block_from_file(char *filename)
// {
//     Block *newBlock = malloc(sizeof(Block));
//     char buff[BUFFER_SIZE];
//     char buff2[BUFFER_SIZE];
//     char auteur[BUFFER_SIZE];
//     char votes[BUFFER_SIZE];
//     char hash[BUFFER_SIZE];
//     char previous_hash[BUFFER_SIZE];
//     int nonce;

//     FILE *f = fopen(filename, "w");
//     if (f == NULL)
//     {
//         printf("erreur lors de l'ouverture");
//         return;
//     }
//     while (fgets(buff, BUFFER_SIZE, f) != 0)
//     {

//         if (sscanf(buff, "%s %s %s %d %s", auteur, hash, previous_hash, &nonce, buff2) != 4)
//         {
//             printf("erreur lecture\n");
//             return NULL;
//         }
//         newBlock->author = str_to_key(auteur);
//         newBlock->hash = strdup(hash);
//         newBlock->previous_hash = strdup(previous_hash);
//         newBlock->nonce = nonce;

//         while (sscanf(buff2, "%s", cp))
//         {
//             CellProtected *cp = create_cell_protected();
//         }
//     }

//     return newBlock;
// }

// // Question 7.3
// char *block_to_str(Block *block)
// {
//     int len = 0;
//     if (block != NULL)
//     {
//         len = strlen(block->author) + 1 + strlen(block->hash) + 1 + strlen(block->previous_hash) + BUFFER_SIZE;
//         CellProtected *tmp = block->votes;
//         while (tmp != NULL)
//         {
//             char *chaine = key_to_str(tmp->key);
//             len = len + strlen(chaine);
//             free(chaine);
//             tmp = tmp->next;
//         }
//     }
//     char *res = malloc(sizeof(char));

//     strcat(res, block->author);
//     strcat(res, block->previous_hash);
//     strcat(res, atoi(block->nonce));
//     CellProtected *tmp = block->votes;
//     while (tmp != NULL)
//     {
//         char *chaine = key_to_str(tmp->key);
//         strcat(res, chaine);
//         free(chaine);
//         tmp = tmp->next;
//     }
// }

// // Question 7.4
// unsigned char *str_to_SHA256(char *chaine)
// {
//     unsigned char *d = SHA256(chaine, strlen(chaine), 0);
//     for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
//         printf("%02x", d[i]);
//     printf("\n");
//     return d;
// }

// int compute_proof_of_work(Block *B, int d)
// {
// }

// // Question