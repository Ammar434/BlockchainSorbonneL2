#ifndef EXERCICE_7_H
#define EXERCICE_7_H
#include <openssl/sha.h>
#include <unistd.h>

#include "../../partie3/partie3.h"

typedef struct block
{
    Key *author;
    CellProtected *votes;
    unsigned char *hash;
    unsigned char *previous_hash;
    int nonce;
} Block;

void write_block_to_file(Block *b);
Block *read_block_from_file(char *filename);
char *block_to_str(Block *block);
int len_block(Block *block);
void delete_block(Block *block);
unsigned char *str_to_SHA256(char *chaine);
void compute_proof_of_work(Block *B, int d);
char *hex_to_bin(unsigned char *hexdec);
char *random_string(int length);
int verify_block(Block *block, int d);
void simulation_compute_proof_of_work();
#endif