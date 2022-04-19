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
        Protected *pr = malloc(sizeof(Protected));
        pr->message = strdup(tmpC1->data->message);
        pr->pKey = malloc(sizeof(Key));
        pr->pKey->a = tmpC1->data->pKey->a;
        pr->pKey->b = tmpC1->data->pKey->b;

        pr->signature = malloc(sizeof(Signature));
        pr->signature->tab = malloc(sizeof(long) * tmpC1->data->signature->size);

        for (int i = 0; i < tmpC1->data->signature->size; i++)
        {
            pr->signature->tab[i] = tmpC1->data->signature->tab[i];
        }
        pr->signature->size = tmpC1->data->signature->size;
        add_cell_protected_to_head(&fusion, pr);
        tmpC1 = tmpC1->next;
    }

    while (tmpC2 != NULL)
    {
        Protected *pr = malloc(sizeof(Protected));
        pr->message = strdup(tmpC2->data->message);
        pr->pKey = malloc(sizeof(Key));
        pr->pKey->a = tmpC2->data->pKey->a;
        pr->pKey->b = tmpC2->data->pKey->b;

        pr->signature = malloc(sizeof(Signature));
        pr->signature->tab = malloc(sizeof(long) * tmpC2->data->signature->size);

        for (int i = 0; i < tmpC2->data->signature->size; i++)
        {
            pr->signature->tab[i] = tmpC2->data->signature->tab[i];
        }
        pr->signature->size = tmpC2->data->signature->size;

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

// CellProtected *fusion_cell_protected(CellProtected *l1, CellProtected *l2)
// {
//     if (l1 == NULL)
//     {
//         return l2;
//     }
//     CellProtected *cour = l1;
//     while (cour->next)
//     {
//         cour = cour->next;
//     }
//     cour->next = l2;
//     return l1;
// }

// Question 8.9
CellProtected *fusion_cell_protected_from_all_node(CellTree *ct)
{
    CellTree *courant = highest_child(ct);

    CellProtected *fusion = NULL;
    fusion = fusion_cell_protected(ct->block->votes, fusion);

    while (courant != NULL)
    {
        CellProtected *fusionTmp = fusion_cell_protected(courant->block->votes, fusion); // Souvent, la liste de déclarations signées sera plus courte que res, donc on est potentiellement plus efficaces
        delete_list_protected(fusion);
        fusion = fusionTmp;
        courant = highest_child(courant); // Highest child nous permet de choisir le bon suivant dans le parcours, sa complexité dépend du nombre de frères
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
            free(pr);
        }
        free(tmp);
    }
    // free(c);
}