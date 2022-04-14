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
    CellTree *grandFather = NULL;
    // La hauteur est modifier?
    if (father->height != (child->height + 1))
    {
        father->height = max(father->height, child->height + 1);

        while (father->father != NULL)
        {
            grandFather = father->father;
            grandFather->height = max(father->height + 1, grandFather->height);
            father = father->father;
        }
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
        child->father = father;
        update_height(father, child);
        return;
    }
    CellTree *cramwler = father->firstChild;

    while (cramwler->nextBro != NULL)
    {
        cramwler = cramwler->nextBro;
    }
    cramwler->nextBro = child;
    cramwler->father = father;

    update_height(father, child);
}

void print_tabulation(int count)
{
    for (int i = 0; i < count; i++)
    {
        putchar('\t');
    }
}

// Question 8.4 à revoir
void print_tree_tmp(CellTree *ct, int level)
{
    while (ct != NULL)
    {
        print_tabulation(level);
        printf("Node:");
        printf("%s----%d\n", ct->block->hash, ct->height);

        if (ct->firstChild != NULL)
        {
            print_tabulation(level);
            printf("Children:\n");
            print_tree_tmp(ct->firstChild, level + 1);
        }
        ct = ct->nextBro;
    }
}

void print_tree(CellTree *ct)
{
    print_tree_tmp(ct, 0);
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

void delete_tree(CellTree *ct)
{
}

// Question 8.6
CellTree *highest_child(CellTree *ct)
{
    CellTree *highestNode = NULL;
    CellTree *tmp = NULL;

    if (ct == NULL)
    {
        return NULL;
    }

    highestNode = ct->firstChild;
    tmp = ct->firstChild;
    while (tmp != NULL)
    {
        if (tmp->height > highestNode->height)
        {
            highestNode = tmp;
        }
        tmp = tmp->nextBro;
    }

    return highestNode;
}
// Question 8.7
CellTree *last_node(CellTree *ct)
{
    if (ct->firstChild == NULL)
        return ct;
    // printf("%s\n", ct->block->hash);
    return last_node(highest_child(ct));
}

// Question 8.8
CellProtected *fusion_cell_protected(CellProtected *c1, CellProtected *c2)
{
    if (c1 == NULL)
    {
        return c2;
    }

    if (c2 == NULL)
    {
        return c1;
    }

    while (c1->next != NULL)
    {
        c1 = c1->next;
    }
    c1->next = c2;
    return c1;
}

// Question 8.9
CellProtected *fusion_cell_protected_from_all_node(CellTree *ct)
{
    CellProtected *fusion = ct->block->votes;
    CellTree *tmp = ct->firstChild;

    while (tmp)
    {
        CellTree *highest = highest_child(tmp);
        fusion = fusion_cell_protected(tmp, highest->block->votes);
        tmp = tmp->firstChild;
    }
    return fusion;
}