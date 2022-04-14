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
int update_height(CellTree *father, CellTree *child);
void add_child(CellTree *father, CellTree *child);
void delete_node(CellTree *node);
int max(int a, int b);
void print_tree(CellTree *ct);
void print_tabulation(int count);
void print_tree_tmp(CellTree *ct, int level);

CellTree *highest_child(CellTree *cell);
CellTree *last_node(CellTree *tree);
CellTree *highest_child(CellTree *cell);

#endif
