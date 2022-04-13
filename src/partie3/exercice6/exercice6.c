#include "exercice6.h"

// Exercice 6
// Question 6.1
void supprimer_fausse_signature(CellProtected **cellProtected)
{
    CellProtected *ptr = NULL;
    CellProtected *tmp = *cellProtected;
    CellProtected *prec = NULL;

    while (tmp)
    {
        // Si la déclaration est valide
        if (verify((tmp)->data) != 1)
        {
            char *sgn_str = signature_to_str((*cellProtected)->data->signature);
            free(sgn_str);

            if (prec)
            {
                prec->next = tmp->next;
            }
            else
            {
                *cellProtected = (*cellProtected)->next;
            }

            ptr = tmp;
            tmp = tmp->next;
            delete_cell_protect(ptr);
        }
        // Si la déclaration n'est pas valide
        else
        {
            prec = tmp;
            tmp = tmp->next;
        }
    }
}

// Question 6.2
HashCell *create_hashcell(Key *key)
{
    HashCell *hash = (HashCell *)(malloc(sizeof(HashCell)));
    hash->key = malloc(sizeof(Key));
    hash->val = 0;
    hash->key->a = key->a;
    hash->key->b = key->b;
    return hash;
}

// Question 6.3
int hash_function(Key *key, int size)
{

    long cle = (key->a) + (key->b);
    return (int)(cle % size);
}

int quadratic_hash_function(Key *key, int size, int pow)
{
    long cle = (hash_function(key, size) + (pow * pow)) % size;

    return (int)(cle);
}
// Question 6.4
int compare_cle(Key *key1, Key *key2)
{
    if (key1->a == key2->a && key1->b == key2->b)
        return 1;
    return 0;
}

int find_position(HashTable *t, Key *key)
{
    if (t == NULL || key == NULL)
    {
        return 0;
    }
    for (int p = 0; p < t->size; p++)
    {
        int position = quadratic_hash_function(key, t->size, p);
        if (t->tab[position] != NULL)
        {
            if (compare_cle(t->tab[position]->key, key) == 1)
            {
                // printf("Element  trouvé\n");
                return position;
            }
        }
    }
    afficher_hashtable(t);

    char *tmp = key_to_str(key);
    printf("Element non trouvé %s \n", tmp);
    free(tmp);
    return hash_function(key, t->size);
}

// Question 6.5
HashTable *create_hashtable(CellKey *keys, int size)
{
    char *tmp = NULL;
    HashTable *hashTable = (HashTable *)(malloc(sizeof(HashTable)));
    hashTable->tab = malloc(sizeof(HashCell *) * size);
    hashTable->size = size;
    for (int i = 0; i < size; i++)
    {
        hashTable->tab[i] = NULL;
    }
    while (keys != NULL)
    {
        for (int p = 0; p < hashTable->size; p++)
        {
            int position = quadratic_hash_function(keys->key, size, p);
            if (hashTable->tab[position] == NULL)
            {
                tmp = key_to_str(keys->key);
                printf("Insertion de %s a la position %d reussi\n", tmp, position);
                HashCell *newCell = create_hashcell(keys->key);
                hashTable->tab[position] = newCell;
                if (tmp != NULL)
                {
                    free(tmp);
                    tmp = NULL;
                }
                break;
            }
        }
        printf("-----------------------------------------------------------------------------------\n");
        keys = keys->next;
    }
    return hashTable;
}
// Question 6.6
void afficher_hashtable(HashTable *hashtable)
{
    char *tmp = NULL;
    for (int i = 0; i < hashtable->size; i++)
    {
        if (hashtable->tab[i] != NULL)
        {
            tmp = key_to_str(hashtable->tab[i]->key);
            printf("%d Personne %s a voté: %d\n", i, tmp, hashtable->tab[i]->val);
            free(tmp);
        }
        else
        {
            printf("%d------------------------\n", i);
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
    if (t == NULL)
    {
        return;
    }
    for (int i = 0; i < t->size; i++)
    {
        if (t->tab[i] != NULL)
        {
            free(t->tab[i]->key);
            free(t->tab[i]);
        }
    }

    free(t->tab);
    free(t);
}

// Question 6.7
Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV)
{
    HashCell *actuelVainqueur = NULL;
    Key *messageKey = NULL;
    HashTable *votantHashTable = create_hashtable(voters, sizeV);
    count_element_hashtable(votantHashTable);
    HashTable *candidatsHashTable = create_hashtable(candidates, sizeC);
    count_element_hashtable(candidatsHashTable);
    CellProtected *tmpDecl = decl;
    Key *keyVainqueur = malloc(sizeof(Key));

    while (tmpDecl != NULL)
    {

        messageKey = str_to_key(tmpDecl->data->message);
        int hashValueVotant = find_position(votantHashTable, tmpDecl->data->pKey);
        int hashValueCandidate = find_position(candidatsHashTable, messageKey);
        // On regarde si clé dans table de hachage pour voir si la personne peut voter
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
        free(messageKey);

        tmpDecl = tmpDecl->next;
    }
    if (actuelVainqueur != NULL)
    {
        keyVainqueur->a = actuelVainqueur->key->a;
        keyVainqueur->b = actuelVainqueur->key->b;
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
    printf("Le vainqueur des elections est le candidat %s avec %d votes\n", messageVainqueur, actuelVainqueur->val);
    free(messageVainqueur);
    delete_hashtable(votantHashTable);
    delete_hashtable(candidatsHashTable);

    return keyVainqueur;
}
