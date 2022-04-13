#include "exercice3.h"
// Question 3.2
void init_key(Key *key, long val, long n)
{
    key->a = val;
    key->b = n;
}

// Question 3.3
void init_pair_keys(Key *pKey, Key *sKey, long low_size, long up_size)
{
    long p = random_prime_number(low_size, up_size, 5000);
    long q = random_prime_number(low_size, up_size, 5000);
    long n, s, u;

    while (p == q)
    {
        q = random_prime_number(low_size, up_size, 5000);
    }

    generate_key_values(p, q, &n, &s, &u);

    // On veut des cles positives :
    if (u < 0)
    {
        long t = (p - 1) * (q - 1);
        u = u + t;
    }

    init_key(pKey, s, n);
    init_key(sKey, u, n);
}

// Question 3.4
char *key_to_str(Key *key)
{
    char *buffer = (char *)malloc(sizeof(char) * 156);
    if (buffer == NULL)
    {
        printf("Erreur lors de l'allocation\n");
        return NULL;
    }
    // conversion de unsigned en chaine de caractere
    sprintf(buffer, "(%lx,%lx)", key->a, key->b);
    return buffer;
}

Key *str_to_key(char *str)
{
    long unsigned int a, b;
    sscanf(str, "(%lx,%lx)", &a, &b);

    Key *res = (Key *)(malloc(sizeof(Key)));
    if (res == NULL)
    {
        printf("Erreur lors de l'allocation\n");

        return NULL;
    }
    init_key(res, a, b);
    return res;
}

// Question 3.6
Signature *init_signature(long *content, int size)
{
    Signature *signature = (Signature *)malloc(sizeof(Signature));
    assert(signature);
    signature->tab = content;
    signature->size = size;
    return signature;
}

// Question 3.7
Signature *sign(char *mess, Key *sKey)
{
    long *content = encrypt(mess, sKey->a, sKey->b);
    int size = strlen(mess);
    return init_signature(content, size);
}

// Question 3.8
char *signature_to_str(Signature *sgn)
{
    char *result = malloc(10 * sgn->size * sizeof(char));
    result[0] = '#';
    int pos = 1;
    char buffer[156];
    for (int i = 0; i < sgn->size; i++)
    {
        sprintf(buffer, "%lx", sgn->tab[i]);
        for (int j = 0; j < (int)strlen(buffer); j++)
        {
            result[pos] = buffer[j];
            pos = pos + 1;
        }
        result[pos] = '#';
        pos = pos + 1;
    }
    result[pos] = '\0';
    result = realloc(result, (pos + 1) * sizeof(char));
    return result;
}

Signature *str_to_signature(char *str)
{
    int len = strlen(str);
    long *content = (long *)(malloc(sizeof(long) * len));
    int num = 0;
    char buffer[256];
    int pos = 0;

    for (int i = 0; i < len; i++)
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

// Question 3.10
Protected *init_protected(Key *pKey, char *mess, Signature *sgn)
{
    Protected *protected = malloc(sizeof(Protected));
    if (protected == NULL)
    {
        printf("Erreur lors de l'allocation\n");
        return NULL;
    }

protected
    ->pKey = pKey;
protected
    ->message = strdup(mess);
protected
    ->signature = sgn;
    return protected;
}

// Question 3.11
int verify(Protected *pr)
{
    if (pr == NULL)
    {
        return 0;
    }

    Signature *sgn = pr->signature;
    Key *pKey = pr->pKey;
    char *mess = pr->message;
    char *s = decrypt(sgn->tab, sgn->size, pKey->a, pKey->b);

    if (strcmp(mess, s) != 0)
    {
        free(s);
        return 0;
    }
    free(s);
    return 1;
}

// Question 3.12
char *protected_to_str(Protected *pr)
{
    char *ptr = signature_to_str(pr->signature);
    char *tmp = key_to_str(pr->pKey);
    strcat(tmp, " ");
    strcat(tmp, pr->message);
    strcat(tmp, " ");
    strcat(tmp, ptr);
    free(ptr);
    return tmp;
}

Protected *str_to_protected(char *str)
{
    char x[256];
    char y[256];
    char z[256];
    Key *cle;
    Signature *s;
    Protected *p;

    sscanf(str, "%s %s %s", x, y, z);
    cle = str_to_key(x);
    s = str_to_signature(z);
    p = init_protected(cle, y, s);
    return p;
}