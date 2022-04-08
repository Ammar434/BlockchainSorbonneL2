#ifndef EXERCICE_7_H
#define EXERCICE_7_H
// #include <openssl/sha.h>
#include "../exercice6/exercice6.h"

typedef struct block
{
    Key *author;
    CellProtected *votes;
    unsigned char *hash;
    unsigned char *previous_hash;
    int nonce;
} Block;

void write_block_to_file(Block b);
Block *read_block_from_file(char *filename);
char *block_to_str(Block *block);
unsigned char *str_to_SHA256(char *chaine);
int compute_proof_of_work(Block *B, int d);

#endif