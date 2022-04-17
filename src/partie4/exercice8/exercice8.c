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
    // ct->block = malloc(sizeof(Block));
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

// Question 8.3
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

// Question 8.4
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

// Question 8.5
void delete_node(CellTree *node)
{
    if (node != NULL)
    {
        if (node->block != NULL)
        {
            free(node->block->author);
            CellProtected *cell = node->block->votes;
            while (cell != NULL)
            {
                CellProtected *tmp = cell;
                cell = cell->next;
                Protected *pr = tmp->data;
                if (pr)
                {
                    free(pr->message);
                    free(pr->pKey);
                    free(pr->signature->tab);
                    free(pr->signature);
                    free(pr);
                }
                // free(tmp);
            }

            delete_block(node->block);
        }
        free(node);
    }
}

void delete_tree(CellTree *ct)
{

    while (ct != NULL)
    {
        CellTree *toDelete = ct;
        if (ct->firstChild != NULL)
        {
            delete_tree(ct->firstChild);
        }
        ct = ct->nextBro;
        delete_node(toDelete);
    }
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
    if (ct == NULL)
    {
        return NULL;
    }
    if (ct->firstChild == NULL)
        return ct;
    // printf("%s\n", ct->block->hash);
    return last_node(highest_child(ct));
}

CellProtected *fusion_cell_protected(CellProtected *c1, CellProtected *c2)
{

    CellProtected *fusion = NULL;

    CellProtected *tmpC1 = c1;
    CellProtected *tmpC2 = c2;
    while (tmpC1 != NULL)
    {
        Protected *pr = init_protected(tmpC1->data->pKey, tmpC1->data->message, tmpC1->data->signature);

        add_cell_protected_to_head(&fusion, pr);
        tmpC1 = tmpC1->next;
    }

    while (tmpC2 != NULL)
    {
        Protected *pr = init_protected(tmpC2->data->pKey, tmpC2->data->message, tmpC2->data->signature);

        add_cell_protected_to_head(&fusion, pr);
        tmpC2 = tmpC2->next;
    }
    // CellProtected *ptr = NULL;
    // if (c1 == NULL)
    // {
    //     c1 = c2;
    //     return c1;
    // }

    // if (c2 == NULL)
    // {
    //     return c1;
    // }
    // ptr = c1;
    // while (ptr->next != NULL)
    // {
    //     ptr = ptr->next;
    // }
    // ptr->next = c2;
    return fusion;
}

// Question 8.9
CellProtected *fusion_cell_protected_from_all_node(CellTree *ct)
{
    CellProtected *fusion = NULL;
    CellProtected *ctTmp = ct->block->votes;
    while (ctTmp)
    {
        add_cell_protected_to_head(&fusion, ctTmp->data);
        ctTmp = ctTmp->next;
    }

    CellTree *tmp = ct;
    while (tmp->firstChild)
    {
        CellTree *highest = highest_child(tmp);
        CellProtected *fusionTmp = fusion_cell_protected(fusion, highest->block->votes);
        while (fusion != NULL)
        {
            CellProtected *tmp = fusion;
            fusion = fusion->next;
            free(tmp);
        }
        fusion = fusionTmp;
        tmp = tmp->firstChild;
    }
    return fusion;
}

void delete_list_protected_from_node(CellProtected *c)
{
    CellProtected *cell = c;
    while (cell != NULL)
    {
        CellProtected *tmp = cell;
        cell = cell->next;
        Protected *pr = tmp->data;
        if (pr)
        {
            free(pr->message);
            free(pr->pKey);
            free(pr->signature->tab);
            free(pr->signature);
            free(pr);
        }
        // free(tmp);
    }
    // free(c);
}