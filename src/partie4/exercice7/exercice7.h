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

void print_hash(unsigned char *hash);

void write_block_to_file(Block *b, char *filename);

Block *read_block_from_file(char *filename);
char *block_to_str(Block *block);
long int len_block(Block *block);
void delete_block(Block *block);
unsigned char *str_to_SHA256(char *chaine);
void compute_proof_of_work(Block *B, int d);
char *hex_to_bin(unsigned char *hexdec);
unsigned char *unsigned_strdup(char *chaine);
int hash_compare(unsigned char *hash1, unsigned char *hash2);

char *random_string(int length);
int verify_block(Block *block, int d);
void simulation_compute_proof_of_work();
#endif