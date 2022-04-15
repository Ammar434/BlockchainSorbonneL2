#ifndef EXERCICE_9_H
#define EXERCICE_9_H
#include <dirent.h>
#define PENDING_VOTE_FILE_PATH "Blockchain/pendings/Pending_votes.txt"
#define PENDING_BLOCK_FILE_PATH "Blockchain/pendings/Pending_blocks.txt"
#define VALID_BLOCK_PATH "Blockchain/blocks/"
#define DIFFICULTE 4
#include "../exercice8/exercice8.h"

void submit_vote(Protected *p);
void create_block(CellTree *tree, Key *author, int d);
void add_block(int d, char *name);
int count_file_in_directory(char *directory);

CellTree *read_tree();
Key *compute_winner_BT(CellTree *tree, CellKey *candidates, CellKey *voters, int sizeC, int sizeV);
#endif