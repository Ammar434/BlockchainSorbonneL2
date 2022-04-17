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
void delete_tree(CellTree *ct);

int max(int a, int b);
void print_tree(CellTree *ct);
void print_tabulation(int count);
void print_tree_tmp(CellTree *ct, int level);
CellProtected *fusion_cell_protected(CellProtected *c1, CellProtected *c2);
CellProtected *fusion_cell_protected_from_all_node(CellTree *ct);
void delete_list_protected_from_node(CellProtected *c);

CellTree *highest_child(CellTree *cell);
CellTree *last_node(CellTree *tree);

#endif
