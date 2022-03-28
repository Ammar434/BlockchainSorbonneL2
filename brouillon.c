#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "main1.h"

typedef struct
{
    long val;
    long n;
} Key;

typedef struct
{
    long *content;
    int size;
} Signature;

typedef struct
{
    Key *pKey;
    char *mess;
    Signature *sgn;
} Protected;

void init_key(Key *key, long val, long n)
{
    key->val = val;
    key->n = n;
}

void init_pair_keys(Key *pKey, Key *sKey, long low_size, long up_size)
{
    long p = random_prime_number(3, 7, 5000);
    long q = random_prime_number(3, 7, 5000);
    while (p == q)
        q = random_prime_number(3, 7, 5000);
    long n, s, u;
    generate_keys_values(p, q, &n, &s, &u);
    // Pour avoir des cles positives :
    if (u < 0)
    {
        long t = (p - 1) * (q - 1);
        u = u + t; // on aura toujours s*u mod t = 1
    }
    init_key(pKey, s, n);
    init_key(sKey, u, n);
}

char *key_to_str(Key *key)
{
    char *buffer = (char *)malloc(sizeof(char) * 156);
    sprintf(buffer, "(%lx,%lx)", key->val, key->n);
    return buffer;
}

Key *str_to_key(char *str)
{
    long l1, l2;
    while (*str != '(')
        str++;
    if (sscanf(str, "(%lx,%lx)", &l1, &l2) != 2)
        return NULL;
    Key *k = (Key *)malloc(sizeof(Key));
    init_key(k, l1, l2);
    return k;
}

Signature *init_signature(long *content, int size)
{
    Signature *sgn = (Signature *)malloc(sizeof(Signature));
    sgn->content = content;
    sgn->size = size;
    return sgn;
}

Signature *sign(char *mess, Key *sKey)
{
    long *content = encrypt(mess, sKey->val, sKey->n);
    int size = strlen(mess);
    return init_signature(content, size);
}

char *signature_to_str(Signature *sgn)
{
    char *result = malloc(10 * sgn->size * sizeof(char));
    result[0] = '#';
    int pos = 1;
    char buffer[156];
    for (int i = 0; i < sgn->size; i++)
    {
        sprintf(buffer, "%lx", sgn->content[i]);
        for (int j = 0; j < strlen(buffer); j++)
        {
            result[pos] = buffer[j];
            pos++;
        }
        result[pos] = '#';
        pos++;
    }
    result[pos] = '\0';
    result = realloc(result, (pos + 1) * sizeof(char));
    return result;
}

Signature *str_to_signature(char *str)
{
    long *content = (long *)malloc(sizeof(long) * strlen(str));
    int num = 0;
    char buffer[256];
    int pos = 0;
    while (*str != '#')
        str++;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != '#')
        {
            buffer[pos] = str[i];
            pos++;
        }
        else
        {
            if (pos != 0)
            {
                buffer[pos] = '\0';
                sscanf(buffer, "%lx", &(content[num]));
                num++;
                pos = 0;
            }
        }
    }
    content = realloc(content, num * sizeof(long));
    return init_signature(content, num);
}

Protected *init_protected(Key *pKey, char *mess, Signature *sgn)
{
    Protected *pr = (Protected *)malloc(sizeof(Protected));
    pr->pKey = pKey;
    pr->mess = mess;
    pr->sgn = sgn;
    return pr;
}

int egalite_cles(Key *k1, Key *k2)
{
    if (!k1 || !k2)
        return 0;
    return ((k1->val == k2->val) && (k1->n == k2->n));
}

int verify(Protected *pr)
{ // verifie que la signature contenue dans pr correspond bien au mess et a la personne contenus dans pr.
    if (strlen(pr->mess) != pr->sgn->size)
        return 0;
    char *check = decrypt(pr->sgn->content, pr->sgn->size, pr->pKey->val, pr->pKey->n);
    // printf("%s vs %s\n", check, pr->mess);
    if (strcmp(check, pr->mess) != 0)
    {
        free(check);
        return 0;
    }
    free(check);
    return 1;
}

char *protected_to_str(Protected *pr)
{
    char *str;
    char *result = (char *)malloc(sizeof(char) * 156);
    str = key_to_str(pr->pKey);
    strcat(result, str);
    free(str);
    result[strlen(result)] = ' ';
    strcat(result, pr->mess);
    result[strlen(result)] = ' ';
    str = signature_to_str(pr->sgn);
    strcat(result, str);
    result[strlen(result)] = '\0';
    return result;
}

void supprimer_signature(Signature *sgn)
{
    free(sgn->content);
    free(sgn);
}

void supprimer_protected(Protected *pr)
{
    free(pr->mess);
    supprimer_signature(pr->sgn);
    free(pr->pKey);
    free(pr);
}

Protected *str_to_protected(char *str)
{
    Key *pKey = str_to_key(str);
    Signature *sgn = str_to_signature(str);
    char *mess = (char *)malloc(sizeof(char) * 20);
    if (sscanf(str, "%*s %s", mess) != 1)
    {
        printf("erreur lecture str_to_protected\n");
        return NULL;
    }
    return init_protected(pKey, mess, sgn);
}

void generate_random_data(int nv, int nc)
{
    int i;
    Key *pKey1 = NULL;
    Key *pKey2 = NULL;
    Key *sKey = NULL;
    char *sgn_str = NULL;
    Signature *sgn = NULL;
    char bufferkeys[156];
    char buffercand[156];
    char bufferskey[20];
    int random;
    int currentline = 0;
    FILE *fkeys = fopen("keys.txt", "w+");
    FILE *fcand = fopen("candidates.txt", "w+");
    FILE *fdecl = fopen("declarations.txt", "w+");
    assert(fkeys);
    assert(fcand);
    assert(fdecl);

    for (i = 0; i < nv; i++)
    { // generer tous les voteurs
        pKey1 = malloc(sizeof(Key));
        sKey = malloc(sizeof(Key));
        init_pair_keys(pKey1, sKey, 3, 7);
        fprintf(fkeys, "(%lx,%lx) (%lx,%lx)\n", pKey1->val, pKey1->n, sKey->val, sKey->n);
        free(pKey1);
        free(sKey);
    }

    for (i = 0; i < nc; i++)
    { // generer les candidats aleatoirement
        do
        {
            currentline = 0;
            rewind(fcand);
            rewind(fkeys);
            random = rand() % nv;
            while (currentline != random)
            {
                fgets(bufferkeys, 156, fkeys);
                currentline++;
            }
            fgets(bufferkeys, 156, fkeys);
            pKey1 = str_to_key(bufferkeys);
            while (!feof(fcand))
            {
                fgets(buffercand, 156, fcand);
                pKey2 = str_to_key(buffercand);
                if (egalite_cles(pKey1, pKey2))
                {
                    free(pKey2);
                    break;
                }
            }
            if (feof(fcand))
                break;
            ;

        } while (1);

        fprintf(fcand, "(%lx,%lx)\n", pKey1->val, pKey1->n);
        free(pKey1);
    }

    rewind(fcand);
    rewind(fkeys);
    for (i = 0; i < nv; i++)
    { // generer les declarations de votes
        currentline = 0;
        rewind(fcand);
        fgets(bufferkeys, 256, fkeys);
        if (sscanf(bufferkeys, "%*s %s", bufferskey) != 1)
        {
            printf("erreur lecture generate_random_data\n");
            return;
        }
        sKey = str_to_key(bufferskey);
        pKey1 = str_to_key(bufferkeys);
        random = rand() % nv;
        while (currentline != random)
        {
            fgets(buffercand, 156, fcand);
            currentline++;
        }
        fgets(buffercand, 156, fcand);
        sgn = sign(buffercand, sKey);
        sgn_str = signature_to_str(sgn);
        supprimer_signature(sgn);
        buffercand[strlen(buffercand) - 1] = '\0';
        fprintf(fdecl, "(%lx,%lx) %s %s\n", pKey1->val, pKey1->n, buffercand, sgn_str);
        free(sgn_str);
        free(pKey1);
        free(sKey);
    }

    fclose(fkeys);
    fclose(fcand);
    fclose(fdecl);
}

int main(void)
{
    srand(time(NULL));

    // Testing Init Keys
    Key *pKey = malloc(sizeof(Key));
    Key *sKey = malloc(sizeof(Key));
    init_pair_keys(pKey, sKey, 3, 7);
    printf("pKey: (%lx, %lx)\n", pKey->val, pKey->n);
    printf("sKey: (%lx, %lx)\n", sKey->val, sKey->n);

    // Testing Key Serialization
    char *chaine = key_to_str(pKey);
    printf("key to str: %s\n", chaine);
    Key *k = str_to_key(chaine);
    if (!k)
    {
        printf("erreur conversion str_to_key\n");
        exit(1);
    }
    printf("str to key: (%lx, %lx)\n", k->val, k->n);

    // Testing signature
    // Candidate keys:
    Key *pKeyC = malloc(sizeof(Key));
    Key *sKeyC = malloc(sizeof(Key));
    init_pair_keys(pKeyC, sKeyC, 3, 7);
    printf("pKeyC: (%lx, %lx)\n", pKeyC->val, pKeyC->n);
    printf("sKeyC: (%lx, %lx)\n", sKeyC->val, sKeyC->n);
    // Declaration:
    char *mess = key_to_str(pKeyC);
    printf("%s vote pour %s\n", key_to_str(pKey), mess);

    Signature *sgn = sign(mess, sKey);
    printf("signature: ");
    print_long_vector(sgn->content, sgn->size);
    free(chaine);
    chaine = signature_to_str(sgn);
    printf("signature to str: %s\n", chaine);
    // supprimer_signature(sgn);
    sgn = str_to_signature(chaine);
    printf("str to signature: ");
    print_long_vector(sgn->content, sgn->size);

    // Testing protected:
    Protected *pr = init_protected(pKey, mess, sgn);
    // Verification:
    if (verify(pr))
        printf("Signature valide\n");
    else
        printf("Signature non valide\n");

    free(chaine);
    chaine = protected_to_str(pr);
    printf("protected to str: %s\n", chaine);
    // supprimer_protected(pr);
    pr = str_to_protected(chaine);

    free(mess);
    mess = key_to_str(pr->pKey);
    free(chaine);
    chaine = signature_to_str(pr->sgn);
    printf("str to protected: %s %s %s \n", mess, pr->mess, chaine);

    free(pKey);
    free(sKey);
    free(pKeyC);
    free(sKeyC);
    free(mess);
    free(chaine);
    free(k);
    supprimer_protected(pr);

    generate_random_data(10, 5); // exo 4

    return 0;
}