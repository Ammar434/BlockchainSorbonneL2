#include "exercice6.h"

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
    while (position <= t->size)
    {
        if (((t->tab)[position]->key->a == key->a) && ((t->tab)[position]->key->b == key->b))
        {
            // printf("Element  trouvé\n");
            return position;
        }
        position = position + 1;
    }
    printf("Element non trouvé\n");
    return hash_function(key, t->size);
}

// Question 6.5
HashTable *create_hashtable(CellKey *keys, int size)
{
    HashTable *hashTable = (HashTable *)(malloc(sizeof(HashTable)));
    hashTable->tab = malloc(sizeof(HashCell *) * size);
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

int compare_cle(Key *key1, Key *key2)
{
    if (key1->a == key2->a && key1->b == key2->b)
        return 1;
    return 0;
}
// Question 6.7
Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV)
{
    HashCell *actuelVainqueur = NULL;

    HashTable *votantHashTable = create_hashtable(voters, sizeV);
    count_element_hashtable(votantHashTable);
    HashTable *candidatsHashTable = create_hashtable(candidates, sizeC);
    count_element_hashtable(candidatsHashTable);
    CellProtected *tmpDecl = decl;
    while (tmpDecl != NULL)
    {

        Key *messageKey = str_to_key(tmpDecl->data->message);
        int hashValueVotant = find_position(votantHashTable, tmpDecl->data->pKey);
        int hashValueCandidate = find_position(candidatsHashTable, messageKey);
        // On regarde si clé da,s table de hachage pour voir si la personne peut voter
        if (compare_cle(votantHashTable->tab[hashValueVotant]->key, tmpDecl->data->pKey))
        {
            // On regarde  dans table de hachage pour voir si la personne a deja voter

            if (votantHashTable->tab[hashValueVotant]->val == 0)
            {
                if (compare_cle(candidatsHashTable->tab[hashValueCandidate]->key, messageKey))
                {
                    (candidatsHashTable->tab[hashValueCandidate])->val = (candidatsHashTable->tab[hashValueCandidate])->val + 1;
                    if (actuelVainqueur == NULL || actuelVainqueur->val < candidatsHashTable->tab[hashValueCandidate]->val)
                    {
                        actuelVainqueur = candidatsHashTable->tab[hashValueCandidate];
                    }
                }
            }
            // On met à -1 pour dire que la personne a deja voté
            votantHashTable->tab[hashValueVotant]->val = -1;
        }

        tmpDecl = tmpDecl->next;
        free(messageKey);
    }
    Key *keyVainqueur;
    if (actuelVainqueur != NULL)
    {
        keyVainqueur = actuelVainqueur->key;
    }

    for (int i = 0; i < candidatsHashTable->size; i++)
    {
        if (candidatsHashTable->tab[i] != NULL)
        {
            char *mess = key_to_str(candidatsHashTable->tab[i]->key);
            printf("Le candidat %s a %d votes\n", mess, candidatsHashTable->tab[i]->val);
            free(mess);
        }
    }
    char *messageVainqueur = key_to_str(keyVainqueur);
    printf("Le vainqueur des élections est le candidat %s avec %d votes\n", messageVainqueur, actuelVainqueur->val);
    free(actuelVainqueur);
    free(messageVainqueur);
    delete_hashtable(votantHashTable);
    delete_hashtable(candidatsHashTable);

    return keyVainqueur;
}
