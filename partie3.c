#include "partie3.h"

CellKey *create_cell_key(Key *key)
{
    CellKey *cell = malloc(sizeof(CellKey));
    cell->key = key;
    cell->next = NULL;
    return cell;
}

CellKey *add_key_to_head(CellKey *cellKey, Key *key)
{
    CellKey *newCell = create_cell_key(key);
    (newCell->next) = cellKey;
    cellKey = newCell;
    return cellKey;
}

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

CellProtected *create_cell_protected(Protected *pr)
{
    CellProtected *cell = (CellProtected *)malloc(sizeof(CellProtected));
    cell->data = pr;
    cell->next = NULL;
    return cell;
}

CellProtected *add_cell_prototected_to_head(CellProtected *cellProtected, Protected *pr)
{
    CellProtected *new = create_cell_protected(pr);
    new->next = cellProtected;
    cellProtected = new;
    return cellProtected;
}

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
        if (sscanf(buff, "%[^\n]", protected_text) != 1)
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

void delete_cell_protect(CellProtected *cp)
{
    free(cp->data);
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