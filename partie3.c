#include "partie3.h"
CellKey *create_cell_key(Key *key)
{
    CellKey *cell = malloc(sizeof(CellKey));
    cell->key = key;
    cell->next = NULL;
    return cell;
}

void add_key_to_head(CellKey *cellKey, Key *key)
{
    if (cellKey == NULL)
    {
        cellKey = create_cell_key(key);
    }
    CellKey *newCell = create_cell_key(key);
    newCell->next = cellKey;
    cellKey = newCell;
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
        return;
    }
    while (fgets(buff, BUFFER_SIZE, f) != 0)
    {
        if (sscanf(buff, "%s", pKey) != 1)
        {
            printf("erreur lecture\n");
            return NULL;
        }
        Key *publicKey = malloc(sizeof(Key));
        publicKey = str_to_key(pKey);
        add_key_to_head(cell, publicKey);
    }
    fclose(f);
    return cell;
}

void print_list_keys(CellKey *LCK)
{
    CellKey *cell = LCK;
    while (cell != NULL)
    {
        printf("%s\n", key_to_str(cell->key));
        cell = cell->next;
    }
}

void delete_cell_key(CellKey *c)
{
    free(c->data);
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