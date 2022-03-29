#ifndef PARTIE3_H
#define PARTIE3_H
#include "partie2.h"
typedef struct cellKey
{
    Key *key;
    struct cellKey *next;
} CellKey;

typedef struct cellProtected
{
    Protected *data;
    struct cellProtected *next;
} CellProtected;

CellKey *create_cell_key(Key *key);
CellKey *add_key_to_head(CellKey *cellKey, Key *key);

CellKey *read_public_keys(char *filename);
void print_list_keys(CellKey *LCK);
void delete_cell_key(CellKey *c);
void delete_list_keys(CellKey *c);
CellProtected *create_cell_protected(Protected *pr);
CellProtected *read_protected_from_file(char *filename);
void print_list_protected(CellProtected *cellProtected);
void delete_cell_protect(CellProtected *cp);
void delete_list_protected(CellProtected *c);
CellProtected *supprimer_fausse_signature(CellProtected *cellProtected);

#endif // PARTIE3_H