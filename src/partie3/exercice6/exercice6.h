#ifndef EXERCICE_6_H
#define EXERCICE_6_H
#include "../exercice5/exercice5.h"

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

void supprimer_fausse_signature(CellProtected **cellProtected);

HashCell *create_hashcell(Key *key);
int hash_function(Key *key, int size);
int quadratic_hash_function(Key *key, int size, int pow);

int find_position(HashTable *t, Key *key);
HashTable *create_hashtable(CellKey *keys, int size);
void delete_hashtable(HashTable *t);
Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV);
void afficher_hashtable(HashTable *hashtable);
void count_element_hashtable(HashTable *hashtable);
int compare_cle(Key *key1, Key *key2);

#endif // PARTIE3_H