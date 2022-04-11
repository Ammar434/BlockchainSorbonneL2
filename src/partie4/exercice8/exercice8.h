#ifndef EXERCICE_8_H
#define EXERCICE_8_H

#include "../exercice7/exercice7.h"
typedef struct block_tree_cell
{
    Block *block;
    struct block_tree_cell *father;
    struct block_tree_cell *firstChild;
    struct block_tree_cell *nextBro;
    int height;
} CellTree;

CellTree *create_node(Block *b);

#endif
