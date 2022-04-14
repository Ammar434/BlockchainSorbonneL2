#ifndef EXERCICE_9_H
#define EXERCICE_9_H
#define PENDING_VOTE_FILE_PATH "Blockchain/Pending_votes.txt"
#define PENDING_BLOCK_FILE_PATH "election_donnee/blocks/Pending_blocks.txt"
#include "../exercice8/exercice8.h"

void submit_vote(Protected *p);
void create_block(CellTree *tree, Key *author, int d);
void add_block(int d, char *name);
CellTree *read_tree();
Key *compute_winner_BT(CellTree *tree, CellKey *candidates, CellKey *voters, int sizeC, int sizeV);
#endif