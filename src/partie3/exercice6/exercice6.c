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
    while (keys->next != NULL)
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
    while (tmpDecl != NULL)
    {

        messageKey = str_to_key(tmpDecl->data->message);
        int hashValueVotant = find_position(votantHashTable, tmpDecl->data->pKey);
        int hashValueCandidate = find_position(candidatsHashTable, messageKey);
        // On regarde si clé da,s table de hachage pour voir si la personne peut voter
        if (compare_cle(votantHashTable->tab[hashValueVotant]->key, tmpDecl->data->pKey))
        {
            // On regarde  dans table de hachage pour voir si la personne a deja voter
            if (votantHashTable->tab[hashValueVotant]->val == 0)
            {
                printf("cle %s\n", key_to_str(candidatsHashTable->tab[hashValueCandidate]->key));
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
    Key *keyVainqueur = malloc(sizeof(Key));
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

// int nb_elem_hashtable(HashTable *t)
// {
//     int i, cpt = 0;
//     for (i = 0; i < t->size; i++)
//     {
//         if (t->tab[i])
//             cpt++;
//     }
//     return cpt;
// }

// int nb_elem_list_protected(CellProtected *LCP)
// { // utilisee que dans la partie 4 pour compter le nb de decl
//     int cpt = 0;
//     while (LCP)
//     {
//         cpt++;
//         LCP = LCP->next;
//     }
//     return cpt;
// }

// Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV)
// {
//     HashTable *tv = create_hashtable(voters, sizeV);
//     HashTable *tc = create_hashtable(candidates, sizeC);
//     HashCell *leader = NULL;

//     printf("\n\nApres la verification des declarations, on a:\n");
//     printf("%d voteurs participants\n", nb_elem_hashtable(tv));
//     printf("%d candidats participants\n", nb_elem_hashtable(tc));
//     printf("%d declarations autorisees et valides\n", nb_elem_list_protected(decl));

//     while (decl)
//     {
//         Key *vote = str_to_key(decl->data->message);
//         int voter_index = find_position(tv, decl->data->pKey);
//         int candidate_index = find_position(tc, vote);

//         if (tv->tab[voter_index]->key == decl->data->pKey)
//         { // si la personne a le droit de voter
//             if (!(tv->tab[voter_index]->val))
//             { // et si cette personne n'a pas encore vote
//                 if (tc->tab[candidate_index]->key == vote)
//                 {                                      // et si la personne sur qui porte le vote est un candidat de l'election
//                     (tc->tab[candidate_index]->val)++; // incrementer le nb de votes pour le candidat vote

//                     // mise a jour du leader actuel de l'election
//                     if (!leader || leader->val < tc->tab[candidate_index]->val)
//                         leader = tc->tab[candidate_index];
//                 }
//             }
//             tv->tab[voter_index]->val = 1; // la personne qui vient de voter ne pourra plus voter
//         }
//         free(vote);
//         decl = decl->next;
//     }

//     // annonce des resultats de l'election
//     Key *vainqueur = (Key *)malloc(sizeof(Key));
//     assert(vainqueur);
//     if (leader)
//     {
//         vainqueur->a = leader->key->a;
//         vainqueur->b = leader->key->b;
//     }

//     // affiche_resultats(tc);
//     delete_hashtable(tv);
//     delete_hashtable(tc);
//     return vainqueur;
// }