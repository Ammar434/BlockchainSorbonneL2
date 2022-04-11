#include "exercice8.h"

// Question 8.1
CellTree *create_node(Block *b)
{
    CellTree *ct = (CellTree *)(malloc(sizeof(CellTree)));
    if (ct == NULL)
    {
        printf("Erreur lors de l'allocation\n");
        return NULL;
    }
    ct->block = b;
    ct->father = NULL,
    ct->firstChild = NULL;
    ct->nextBro = NULL;
    ct->height = 0;
    return ct;
}

// Question 8.2 à revoir
int update_height(CellTree *father, CellTree *child)
{
    if (father->height == child->height + 1)
    {
        return 0;
    }
    else
    {
        if (father->height < child->height + 1)
        {
            father->height = father->height + child->height;
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

// Question 8.3
void add_child(CellTree *father, CellTree *child)
{
    father->firstChild = child;
    update_height(father, child);
}

// Question 8.4
void print_tree(CellTree *ct)
{
    if (ct)
    {
        printf("hauteur du noeud : %d\n", ct->height);
        print_tree(ct->firstChild);
        print_tree(ct->nextBro);
    }
}

// Question 8.5
void delete_node(CellTree *node)
{
    if (node)
    {
        delete_node(node->firstChild);
        delete_node(node->nextBro);
        delete_node(node);
    }
}