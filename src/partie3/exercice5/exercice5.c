#include "exercice5.h"
// Exercice 5

// Question 5.1

CellKey *create_cell_key(Key *key)
{
    CellKey *cell = malloc(sizeof(CellKey));
    cell->key = malloc(sizeof(Key));
    if (cell == NULL)
    {
        printf("Erreur lors de l'allocation\n");
        return NULL;
    }
    if (key == NULL)
    {
        printf("Erreur lors de l'allocation\n");
        return NULL;
    }
    cell->key->a = key->a;
    cell->key->b = key->b;
    cell->next = NULL;
    return cell;
}

// Question 5.2
void add_key_to_head(CellKey **cellKey, Key *key)
{
    CellKey *newCell = create_cell_key(key);
    if (newCell == NULL)
    {
        printf("Erreur lors de l'allocation\n");
        return;
    }
    newCell->next = *cellKey;
    *cellKey = newCell;
}

// Question 5.3
CellKey *read_public_keys(char *filename)
{
    CellKey *cell = NULL;
    Key *publicKey;
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
        if (sscanf(buff, "%s", pKey) != 1)
        {
            printf("erreur lecture\n");
            return NULL;
        }
        publicKey = str_to_key(pKey);
        add_key_to_head(&cell, publicKey);
        free(publicKey);
    }
    fclose(f);
    return cell;
}

// Question 5.4
void print_list_keys(CellKey *LCK)
{
    if (!LCK)
    {
        return;
    }
    CellKey *cell = LCK;
    while (cell->next != NULL)
    {
        printf("(%lx,%lx)\n", LCK->key->a, LCK->key->b);
        cell = cell->next;
    }
}

// Question 5.5
void delete_cell_key(CellKey *c)
{
    if (c->key)
    {
        free(c->key);
    }
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
void add_cell_protected_to_head(CellProtected **cellProtected, Protected *pr)
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
Protected *temporaire(char *str)
{
    char a[BUFFER_SIZE];
    char b[BUFFER_SIZE];
    char c[BUFFER_SIZE];
    sscanf(str, "%s %s %s", a, c, b);
    Key *cle = str_to_key(a);
    Signature *s = str_to_signature(b);
    Protected *p = init_protected(cle, c, s);
    return p;
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
        Protected *protected = temporaire(protected_text);
        add_cell_protected_to_head(&cell, protected);
    }
    fclose(f);

    return cell;
}

// Question 5.9
void print_list_protected(CellProtected *cellProtected)
{
    if (!cellProtected)
    {
        return;
    }
    CellProtected *cell = cellProtected;
    Protected *protect = cell->data;

    while (cell)
    {
        if (cell->data == NULL || cell == NULL)
        {
            return;
        }
        protect = cell->data;
        if (protect)
        {
            char *key = key_to_str(protect->pKey);
            char *sign = signature_to_str(protect->signature);
            printf("%s %s %s\n", key, protect->message, sign);
            free(key);
            free(sign);
        }
        cell = cell->next;
    }
}

// Question 5.10
void delete_cell_protect(CellProtected *cp)
{
    Protected *pr = cp->data;
    if (pr)
    {
        free(pr->message);
        free(pr->pKey);
        free(pr->signature->tab);
        free(pr->signature);
        free(pr);
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