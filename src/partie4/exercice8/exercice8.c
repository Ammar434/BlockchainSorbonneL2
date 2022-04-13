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
    ct->block = malloc(sizeof(Block));
    ct->block = b;
    ct->father = NULL,
    ct->firstChild = NULL;
    ct->nextBro = NULL;
    ct->height = 0;
    return ct;
}

// Question 8.2
int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int update_height(CellTree *father, CellTree *child)
{
    // La hauteur est modifier?
    if (father->height != (child->height + 1))
    {
        father->height = max(father->height, child->height + 1);
        return 1;
    }
    return 0;
}

// Question 8.3 à revoir
void add_child(CellTree *father, CellTree *child)
{

    if (father->firstChild == NULL)
    {
        father->firstChild = child;
        return;
    }
    CellTree *cramwler = father->nextBro;
    while (cramwler)
    {
        cramwler = cramwler->nextBro;
    }
    cramwler = child;
    update_height(father, child);
}

// Question 8.4 à revoir
void print_tree(CellTree *ct)
{
    if (ct != NULL)
    {
        printf("hauteur du noeud : %d\n", ct->height);
        CellTree *cramwler = ct->firstChild;
        while (cramwler != NULL)
        {

            printf("hauteur du noeud : %d\n", ct->height);
            cramwler = cramwler->nextBro;
        }
    }
}

// Question 8.5 à revoir
void delete_node(CellTree *node)
{
    if (node)
    {
        delete_node(node->firstChild);
        delete_node(node->nextBro);
        delete_node(node);
    }
}

// Question 8.6
CellTree *highest_child(CellTree *cell)
{
    if (cell == NULL)
    {
        return NULL;
    }
    return NULL;
    // cell->
}
// Question 8.7

// Question 8.8

// Question 8.9
