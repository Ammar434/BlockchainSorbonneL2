#include "partie3.h"

// Exercice 5

// Question 5.1
CellKey *create_cell_key(Key *key)
{
    CellKey *cell = malloc(sizeof(CellKey));
    if (cell == NULL)
    {
        printf("Erreur lors de l'allocation\n");
        return NULL;
    }
    cell->key = key;
    cell->next = NULL;
    return cell;
}

// Question 5.2
CellKey *add_key_to_head(CellKey *cellKey, Key *key)
{
    CellKey *newCell = create_cell_key(key);
    if (newCell == NULL)
    {
        printf("Erreur lors de l'allocation\n");
        return NULL;
    }
    newCell->next = cellKey;
    cellKey = newCell;
    return cellKey;
}

// Question 5.3
CellKey *read_public_keys(char *filename)
{
    CellKey *cell = NULL;
    char buff[BUFFER_SIZE];
    char pKey[BUFFER_SIZE];
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("erreur lors de la lecture\n");
        return NULL;
    }
    while (fgets(buff, BUFFER_SIZE, f) != 0)
    {
        if (sscanf(buff, "%s ", pKey) != 1)
        {
            printf("erreur lecture\n");
            return NULL;
        }
        Key *publicKey = malloc(sizeof(Key));
        publicKey = str_to_key(pKey);
        cell = add_key_to_head(cell, publicKey);
    }

    fclose(f);
    return cell;
}

// Question 5.4
void print_list_keys(CellKey *LCK)
{
    if (!LCK)
        return;
    CellKey *cell = LCK;
    while (cell->next != NULL)
    {
        printf("%s\n", key_to_str(cell->key));
        cell = cell->next;
    }
}

// Question 5.5
void delete_cell_key(CellKey *c)
{
    free(c->key);
    free(c);
}

void delete_list_keys(CellKey *c)
{
    CellKey *cell = c;
    while (cell != NULL)
    {
        CellKey *tmp = cell;
        cell = cell->next;
        delete_cell_key(tmp);
    }
}

// Question 5.6
CellProtected *create_cell_protected(Protected *pr)
{
    CellProtected *cell = (CellProtected *)malloc(sizeof(CellProtected));
    if (cell == NULL)
    {
        printf("Erreur lors de l'allocation\n");
        return NULL;
    }
    cell->data = pr;
    cell->next = NULL;
    return cell;
}

// Question 5.7
CellProtected *add_cell_prototected_to_head(CellProtected *cellProtected, Protected *pr)
{
    CellProtected *new = create_cell_protected(pr);
    if (new == NULL)
    {
        printf("Erreur lors de l'allocation\n");
        return NULL;
    }
    new->next = cellProtected;
    cellProtected = new;
    return cellProtected;
}

// Question 5.8
CellProtected *read_protected_from_file(char *filename)
{
    CellProtected *cell = NULL;
    char buff[BUFFER_SIZE];
    char protected_text[BUFFER_SIZE];
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("erreur lors de la lecture\n");
        return NULL;
    }
    while (fgets(buff, BUFFER_SIZE, f) != 0)
    {
        if (sscanf(buff, "%[^\t\n]", protected_text) != 1)
        {
            printf("erreur lecture\n");
            return NULL;
        }
        Protected *protected = malloc(sizeof(Protected));
        if (!protected)
            return NULL;
    protected
        = str_to_protected(protected_text);
        cell = add_cell_prototected_to_head(cell, protected);
    }
    fclose(f);
    return cell;
}

// Question 5.9
void print_list_protected(CellProtected *cellProtected)
{
    if (!cellProtected)
        return;
    CellProtected *cell = cellProtected;
    while (cell->next != NULL)
    {
        printf("%s\n", protected_to_str(cell->data));
        cell = cell->next;
    }
}

// Question 5.10 à revoir
void delete_cell_protect(CellProtected *cp)
{
    if (cp->data)
    {
        free(cp->data->pKey);
        free((cp->data->signature)->tab);
        free(cp->data->signature);
        free((cp->data)->message);
        free(cp->data);
    }
    free(cp);
}

void delete_list_protected(CellProtected *c)
{
    CellProtected *cell = c;
    while (cell != NULL)
    {
        CellProtected *tmp = cell;
        cell = cell->next;
        delete_cell_protect(tmp);
    }
}

// Exercice 6
// Question 6.1
CellProtected *supprimer_fausse_signature(CellProtected *cellProtected)
{
    CellProtected *n, *prec;
    if (cellProtected != NULL)
    {
        if (verify(cellProtected->data) == 0)
        { // si premier
            n = cellProtected;
            cellProtected = cellProtected->next;
            delete_cell_protect(n);
        }
        else
        { // sinon voir les autres
            prec = cellProtected;
            n = cellProtected->next;
            while (n != NULL)
            {
                if (verify(n->data) == 0)
                {
                    prec->next = n->next;
                    delete_cell_protect(n);
                    break;
                }
                prec = n;
                n = n->next;
            }
        }
    }
    return cellProtected;
}