#ifndef PARTIE3_H
#define PARTIE3_H
#include "partie2.h"
#define NOMBRE_OR (sqrt(5) - 1) / 2

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

typedef struct hashcell
{
    Key *key;
    int val;
} HashCell;

typedef struct hashtable
{
    HashCell **tab;
    int size;
} HashTable;

typedef struct candidat
{
    Key *key;
    long nb;
} Candidat;

typedef struct hashtableCandidat
{
    Candidat **tab;
    int size;
} HashtableCandidat;

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
void check_signature(CellProtected **LCP);

HashCell *create_hashcell(Key *key);
int hash_function(Key *key, int size);
int find_position(HashTable *t, Key *key);
HashTable *create_hashtable(CellKey *keys, int size);
void delete_hashtable(HashTable *t);
Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV);

#endif // PARTIE3_H