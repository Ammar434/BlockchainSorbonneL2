#include "exercice5.h"
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
    cell->key = malloc(sizeof(Key));
    cell->key->a = key->a;
    cell->key->b = key->b;
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
        Key *publicKey = str_to_key(pKey);
        cell = add_key_to_head(cell, publicKey);
        free(publicKey);
    }

    fclose(f);
    return cell;
}

// Question 5.4
void print_list_keys(CellKey *LCK)
{
    char *tmp = NULL;
    if (!LCK)
        return;
    CellKey *cell = LCK;
    while (cell != NULL)
    {
        tmp = key_to_str(cell->key);
        printf("%s\n", tmp);
        free(tmp);
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
    while (c != NULL)
    {
        CellKey *tmp = c;
        c = c->next;
        delete_cell_key(tmp);
    }
    free(c);
}

// Question 5.6
CellProtected *create_cell_protected(Protected *pr)
{
    CellProtected *cell = malloc(sizeof(CellProtected));
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
void add_cell_prototected_to_head(CellProtected **cellProtected, Protected *pr)
{

    CellProtected *new = create_cell_protected(pr);
    if (new == NULL)
    {
        printf("Erreur lors de l'allocation\n");
        return;
    }
    new->next = *cellProtected;
    *cellProtected = new;
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
        if (sscanf(buff, "%[^\n]", protected_text) != 1)
        {
            printf("erreur lecture\n");
            return NULL;
        }
        Protected *protected = str_to_protected(protected_text);
        add_cell_prototected_to_head(&cell, protected);
    }
    fclose(f);

    return cell;
}

// Question 5.9
void print_list_protected(CellProtected *cellProtected)
{
    char *tmp = NULL;
    if (!cellProtected)
        return;
    CellProtected *cell = cellProtected;
    while (cell != NULL)
    {
        tmp = protected_to_str(cell->data);
        printf("%s\n", tmp);
        cell = cell->next;
        free(tmp);
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
        free(cp->data->message);

        free(cp->data);
    }
    free(cp);
}

void delete_list_protected(CellProtected *c)
{

    while (c != NULL)
    {
        CellProtected *tmp = c;
        c = c->next;
        delete_cell_protect(tmp);
    }
    free(c);
}