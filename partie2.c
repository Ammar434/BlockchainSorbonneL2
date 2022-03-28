#include "partie2.h"

// Question 2.1
void generate_key_values(long p, long q, long *n, long *s, long *u)
{
    *n = p * q;
    long t = (p - 1) * (q - 1);
    *s = rand_long(2, t);
    long v;
    while (extended_gcd(*s, t, u, &v) != 1)
    {
        *s = rand_long(2, t);
    }
    // printf("Clé publique : %lx %lx \n", *s, *n);
    // printf("Clé secrete : %lx %lx \n", *u, *n);
}
// Question 2.2
long *encrypt(char *chaine, long s, long n)
{
    int i = 0;
    long m = 0;
    long *tab = (long *)malloc(sizeof(long) * strlen(chaine));
    while (chaine[i] != '\0')
    {
        int tmp = chaine[i];
        m = (long)(tmp);
        tab[i] = modpow(m, s, n);
        i++;
    }

    return tab;
}

// Question 2.3 à rechecker
char *decrypt(long *crypted, int size, long u, long n)
{
    char *tab = (char *)malloc(sizeof(char) * size + 1);
    for (int i = 0; i < size; i++)
    {
        tab[i] = modpow(crypted[i], u, n);
    }
    tab[size] = '\0';
    return tab;
}

void print_long_vector(long *result, int size)
{
    printf("Vector: [");
    for (int i = 0; i < size; i++)
    {
        printf(" %lx ", result[i]);
    }
    printf("]\n");
}

// Question 3.2
void init_key(Key *key, long val, long n)
{
    key->a = val;
    key->b = n;
}

void init_pair_keys(Key *pKey, Key *sKey, long low_size, long up_size)
{
    long p = random_prime_number(low_size, up_size, 5000);
    long q = random_prime_number(low_size, up_size, 5000);
    generate_key_values(
        p, q, &(pKey->b),
        &(pKey->a),
        &(sKey->a));
    sKey->b = pKey->b;
}

char *key_to_str(Key *key)
{
    int len;
    char *str;
    len = getLenNum(key->a) + 1 + getLenNum(key->b) + 2;
    str = malloc(sizeof(char) * len);
    sprintf(str, "(%lx,%lx)", key->a, key->b);
    return str;
}

Key *str_to_key(char *str)
{
    Key *key = malloc(sizeof(Key));
    long unsigned int *a = ((long unsigned int *)(&key->a));
    long unsigned int *b = ((long unsigned int *)(&key->b));
    sscanf(str, "(%lx,%lx)", a, b);
    return key;
}

int getLenNum(long a)
{
    return floor(log10(labs(a))) + 1;
}

Signature *init_signature(long *content, int size)
{
    Signature *signature = malloc(sizeof(Signature));
    signature->tab = malloc(sizeof(long) * size);
    signature->size = size;
    for (int i = 0; i < size; i++)
    {
        signature->tab[i] = content[i];
    }
    return signature;
}

Signature *sign(char *mess, Key *sKey)
{
    Signature *signature = malloc(sizeof(Signature));
    signature->tab = malloc(sizeof(long) * strlen(mess));
    signature->size = strlen(mess);

    signature->tab = encrypt(mess, sKey->a, sKey->b);
    return signature;
}

char *signature_to_str(Signature *sgn)
{
    char *result = malloc(10 * sgn->size * sizeof(char));
    result[0] = '#';
    int pos = 1;
    char buffer[156];
    for (int i = 0; i < sgn->size; i++)
    {
        sprintf(buffer, "%lx ", sgn->tab[i]);
        for (int j = 0; j < (int)strlen(buffer); j++)
        {
            result[pos] = buffer[j];
            pos = pos + 1;
        }
        result[pos] = '#';
        pos = pos + 1;
    }
    result[pos] = '0';
    result = realloc(result, (pos + 1) * sizeof(char));
    return result;
}

Signature *str_to_signature(char *str)
{
    int len = strlen(str);
    long *content = (long *)malloc(sizeof(long) * len);
    int num = 0;
    char buffer[256];
    int pos = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] != '#')
        {
            buffer[pos] = str[i];
            pos = pos + 1;
        }
        else
        {
            if (pos != 0)
            {
                buffer[pos] = '\0';
                sscanf(buffer, "%lx", &(content[num]));
                num = num + 1;
                pos = 0;
            }
        }
    }
    content = realloc(content, num * sizeof(long));
    return init_signature(content, num);
}

Protected *init_protected(Key *pKey, char *mess, Signature *sgn)
{
    Protected *protected = malloc(sizeof(Protected));
protected
    ->pKey = pKey;
protected
    ->message = mess;
protected
    ->signature = sgn;
    return protected;
}

int verify(Protected *pr)
{
    Signature *sgn = pr->signature;
    Key *pKey = pr->pKey;
    char *mess = pr->message;
    char *s = decrypt(sgn->tab, sgn->size, pKey->a, pKey->b);
    if (strcmp(mess, s) != 0)
        return 0;
    return 1;
}

char *protected_to_str(Protected *protected)
{
    int i = 0;
    int j = 0;
    char *key_str = key_to_str(protected->pKey);
    char *sgn_str = signature_to_str(protected->signature);
    int len = strlen(key_str) + strlen(sgn_str) + strlen(protected->message) + 3;
    char *mess_str = malloc(len * sizeof(char));
    while (key_str[j] != '\0')
    {
        mess_str[i] = key_str[i];
        i = i + 1;
        j = j + 1;
    }
    mess_str[i] = ';';
    i = i + 1;
    j = 0;
    while (protected->message[j] != '\0')
    {
        mess_str[i] = protected->message[j];
        i = i + 1;
        j = j + 1;
    }
    mess_str[i] = ';';
    i = i + 1;
    j = 0;
    while (sgn_str[j] != '\0')
    {
        mess_str[i] = sgn_str[j];
        i = i + 1;
        j = j + 1;
    }
    mess_str[len] = '\0';
    return mess_str;
}

Protected *str_to_protected(char *str)
{
    int i = 0;
    int j = 0;
    char *key_str = malloc(256 * sizeof(char));
    char *sgn_str = malloc(256 * sizeof(char));
    char *mess_str = malloc(256 * sizeof(char));
    while (str[i] != ';')
    {
        key_str[j] = str[i];
        i = i + 1;
        j = j + 1;
    }
    key_str[j] = '\0';
    i = i + 1;
    j = 0;
    while (str[i] != ';')
    {
        mess_str[j] = str[i];
        i = i + 1;
        j = j + 1;
    }
    mess_str[j] = '\0';
    i = i + 1;
    j = 0;
    while (str[i] != '\0')
    {
        sgn_str[j] = str[i];
        i = i + 1;
        j = j + 1;
    }
    sgn_str[j] = '\0';

    Key *pKey = str_to_key(key_str);
    Signature *sgn = str_to_signature(sgn_str);
    Protected *protected = init_protected(pKey, mess_str, sgn);
    return protected;
}