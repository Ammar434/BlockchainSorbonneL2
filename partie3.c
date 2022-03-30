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
void *add_cell_prototected_to_head(CellProtected **cellProtected, Protected *pr)
{

    CellProtected *new = create_cell_protected(pr);
    if (new == NULL)
    {
        printf("Erreur lors de l'allocation\n");
        return NULL;
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
    if (!cellProtected)
        return;
    CellProtected *cell = cellProtected;
    while (cell != NULL)
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
        free(cp->data);
    }
    free(cp);
}

// void delete_list_protected(CellProtected *c)
// {
//     CellProtected *cell = c;
//     while (cell != NULL)
//     {
//         CellProtected *tmp = cell;
//         cell = cell->next;
//         delete_cell_protect(tmp);
//     }
// }

// Exercice 6
// Question 6.1
CellProtected *supprimer_fausse_signature(CellProtected *cellProtected)
{
    CellProtected *n, *prec;
    if (cellProtected != NULL)
    {
        if (verify(cellProtected->data) == 0)
        { // si premier
          // n = cellProtected;
          // cellProtected = cellProtected->next;
          // delete_cell_protect(n);
        }
        else
        { // sinon voir les autres
            prec = cellProtected;
            n = cellProtected->next;
            while (n != NULL)
            {
                // if (verify(n->data) == 0)
                // {
                //     prec->next = n->next;
                //     delete_cell_protect(n);
                //     break;
                // }
                prec = n;
                n = n->next;
            }
        }
    }
    return cellProtected;
}

void check_signature(CellProtected **LCP)
{
    CellProtected *tmp = *LCP;
    CellProtected *prec = NULL;
    CellProtected *dlt = NULL;
    while (tmp)
    {
        if (verify((tmp)->data) != 1)
        {
            char *sgn_str = signature_to_str((*LCP)->data->signature);
            printf("cette declaration n'est pas valide\n");
            free(sgn_str);

            if (prec)
                prec->next = tmp->next;

            else
                *LCP = (*LCP)->next;

            dlt = tmp;
            tmp = tmp->next;
            delete_cell_protect(dlt);
        }
        else
        {
            printf("cette declaration est valide\n");
            prec = tmp;
            tmp = tmp->next;
        }
    }
}

// Question 6.2
HashCell *create_hashcell(Key *key)
{
    HashCell *hash = (HashCell *)(malloc(sizeof(HashCell)));
    hash->val = 0;
    hash->key = key;
    return hash;
}

// Question 6.3
int hash_function(Key *key, int size)
{
    long cle = (key->a) + (key->b);
    // return (int)(size * (cle * NOMBRE_OR - (int)(cle * NOMBRE_OR)));
    return (int)(cle % size);
}

// Question 6.4
int find_position(HashTable *t, Key *key)
{
    if (t == NULL || key == NULL)
    {
        return 0;
    }
    int position = hash_function(key, t->size);
    while (position < t->size)
    {
        if (((t->tab)[position]->key->a == key->a) && ((t->tab)[position]->key->b == key->b))
        {
            // printf("Element trouvé\n");
            return 1;
        }
        position = position + 1;
    }
    // printf("Element non trouvé\n");
    return 0;
}

// Question 6.5
HashTable *create_hashtable(CellKey *keys, int size)
{
    HashTable *hashTable = (HashTable *)(malloc(sizeof(HashTable)));
    hashTable->tab = malloc(sizeof(HashCell) * size);
    hashTable->size = size;
    for (int i = 0; i < size; i++)
    {
        hashTable->tab[i] = NULL;
    }

    while (keys != NULL)
    {
        int position = hash_function(keys->key, size);
        while (hashTable->tab[position] != NULL && position < size)
        {
            position++;
        }
        HashCell *newCell = create_hashcell(keys->key);
        hashTable->tab[position] = newCell;
        keys = keys->next;
    }
    return hashTable;
} // Question 6.6

void afficher_hashtable(HashTable *hashtable)
{
    for (int i = 0; i < hashtable->size; i++)
    {
        if (hashtable->tab[i] == NULL)
        {
            printf("%d------------------------\n", i);
        }
        else
        {
            printf("%d Personne %s a voté: %d\n", i, key_to_str(hashtable->tab[i]->key), hashtable->tab[i]->val);
        }
    }
}

void count_element_hashtable(HashTable *hashtable)
{
    int j = 0;
    for (int i = 0; i < hashtable->size; i++)
    {
        if (hashtable->tab[i] != NULL)
        {
            j++;
        }
    }
    printf("La table de hashage possede %d elements\n", j);
}

void delete_hashtable(HashTable *t)
{
    for (int i = 0; i < t->size; i++)
    {
        free(t->tab[i]);
    }
    free(t->tab);
    free(t);
}

// Question 6.7
Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV)
{
    HashCell *actuelVainqueur = malloc(sizeof(HashCell));
    actuelVainqueur = NULL;

    HashTable *votantHashTable = create_hashtable(voters, sizeV);
    count_element_hashtable(votantHashTable);
    HashTable *candidatsHashTable = create_hashtable(candidates, sizeC);
    count_element_hashtable(candidatsHashTable);

    CellProtected *tmpDecl = decl;
    while (tmpDecl != NULL)
    {

        Key *messageKey = str_to_key(tmpDecl->data->message);
        int hashValueVotant = hash_function(tmpDecl->data->pKey, sizeV);
        int hashValueCandidate = hash_function(messageKey, sizeC);
        if (find_position(votantHashTable, votantHashTable->tab[hashValueVotant]->key) == 1)
        {
            if (votantHashTable->tab[hashValueVotant]->val >= 0)
            {
                if (find_position(candidatsHashTable, candidatsHashTable->tab[hashValueCandidate]->key) == 1)
                {
                    (candidatsHashTable->tab[hashValueCandidate])->val = (candidatsHashTable->tab[hashValueCandidate])->val + 1;
                    if (actuelVainqueur == NULL || actuelVainqueur->val < candidatsHashTable->tab[hashValueCandidate]->val)
                    {
                        actuelVainqueur = candidatsHashTable->tab[hashValueCandidate];
                    }
                }
                // On met à -1 pour dire que la personne a deja voté
                votantHashTable->tab[hashValueVotant]->val = -1;
            }
        }

        tmpDecl = tmpDecl->next;
        free(messageKey);
    }
    Key *keyVainqueur = malloc(sizeof(Key));
    keyVainqueur = NULL;
    if (actuelVainqueur != NULL)
    {
        keyVainqueur = actuelVainqueur->key;
    }

    for (int i = 0; i < candidatsHashTable->size; i++)
    {
        if (candidatsHashTable->tab[i] != NULL)
            printf("Le candidat %s a %d votes\n", key_to_str(candidatsHashTable->tab[i]->key), candidatsHashTable->tab[i]->val);
    }

    printf("Le vainqueur des élections est le candidat %s avec %d votes\n", key_to_str(keyVainqueur), actuelVainqueur->val);

    free(actuelVainqueur);
    return keyVainqueur;
}
