#include "partie2.h"
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
    while (p == q)
    {
        q = random_prime_number(3, 7, 5000);
    }
    long n, s, u;
    generate_key_values(p, q, &n, &s, &u);

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

// Question 3.6
Signature *init_signature(long *content, int size)
{
    Signature *signature = (Signature *)malloc(sizeof(Signature));
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
    long unsigned int *a = ((long unsigned int *)(&(content[num])));
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
                sscanf(buffer, "%lx", a);
                num = num + 1;
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
protected
    ->pKey = pKey;
protected
    ->message = mess;
protected
    ->signature = sgn;
    return protected;
}

// Question 3.11
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

// Question 3.12
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

void generer_all_data(char *filename, int nv)
{
    // Genere carte electorale de toute la population
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("erreur lors de l'ouverture");
        return;
    }
    for (int i = 0; i < nv; i++)
    {
        Key *pKey = malloc(sizeof(Key));
        Key *sKey = malloc(sizeof(Key));
        init_pair_keys(pKey, sKey, 3, 7);
        fprintf(f, "%s %s\n", key_to_str(pKey), key_to_str(sKey));
        free(pKey);
        free(sKey);
    }
    fclose(f);
}

void generer_selection_candidat(char *filename, char *filename2, int nv, int nc)
{
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen(filename2, "w");
    int i = 0;
    char buffer[BUFFER_SIZE];
    char kPublic[BUFFER_SIZE];
    char kPrivee[BUFFER_SIZE];
    if (f == NULL || f2 == NULL)
    {
        printf("erreur lors de la lecture\n");
        return;
    }
    // Selection des candidats
    for (int j = 0; j < nc; j++)
    {
        int random = rand() % nv;
        printf("Candidat a la ligne %d se presente au election\n", random);
        while (fgets(buffer, sizeof(buffer), f) != 0)
        {
            i++;
            if (i == random)
            {
                sscanf(buffer, "%s %s", kPublic, kPrivee);
                printf("%s\n", buffer);
                fprintf(f2, "%s\n", kPublic);
                // printf("%s\n", kPublic);
                break;
            }
        }
        rewind(f);
        i = 0;
    }
    fclose(f);
    fclose(f2);
}

void generer_declaration_vote(char *filename, char *filename2, char *filename3, int nbCandidates)
{
    Key **tabCandidates = malloc(sizeof(Key *) * nbCandidates);
    for (int i = 0; i < nbCandidates; i++)
    {
        tabCandidates[i] = malloc(sizeof(Key));
    }

    char buff[BUFFER_SIZE];
    char pKey[BUFFER_SIZE];
    char sKey[BUFFER_SIZE];

    int elemAtTabCandidates = 0;

    FILE *f = fopen(filename, "r");   // prendre toute la population
    FILE *f2 = fopen(filename2, "r"); // prendre tous les candidats
    FILE *f3 = fopen(filename3, "w"); // declaration de vote de chacun

    if (f == NULL || f2 == NULL || f3 == NULL)
    {
        printf("erreur lors de la lecture\n");
        return;
    }

    char *mess;
    Signature *sgn;
    Protected *pr;
    char *chaine;

    // Generer tab candidat
    while (fgets(buff, BUFFER_SIZE, f2) != 0)
    {
        if (sscanf(buff, "%s", pKey) != 1)
        {
            printf("erreur lecture\n");
        }
        Key *candidatKey = malloc(sizeof(Key));
        candidatKey = str_to_key(pKey);
        tabCandidates[elemAtTabCandidates] = candidatKey;
        elemAtTabCandidates++;
    }

    while (fgets(buff, BUFFER_SIZE, f) != 0)
    {
        Key *publicKey = NULL;
        Key *secureKey = NULL;
        if (sscanf(buff, "%s %s", pKey, sKey) != 2)
        {
            printf("erreur lecture\n");
            return;
        }
        publicKey = str_to_key(pKey);
        secureKey = str_to_key(sKey);
        int votePour = rand() % nbCandidates;
        mess = key_to_str(tabCandidates[votePour]);
        // printf("%s vote pour %s \n", key_to_str(publicKey), mess);

        printf("Message %s\n", mess);
        printf("privee %s\n", sKey);
        sgn = sign(mess, secureKey);

        // pr = init_protected(publicKey, mess, sgn);

        // chaine = protected_to_str(pr);

        // fprintf(f3, "%s\n", chaine);
        free(publicKey);
        free(secureKey);
    }

    for (int i = 0; i < nbCandidates; i++)
        free(tabCandidates[i]);
    free(tabCandidates);
    fclose(f);
    fclose(f2);
    fclose(f3);
}

void generate_random_data(int nv, int nc)
{
    // Creation fichier toutes les clés

    char *filename = "election_donnee/keys.txt";
    char *filename2 = "election_donnee/candidates.txt";
    char *filename3 = "election_donnee/declaration.txt";
    generer_all_data(filename, nv);
    generer_selection_candidat(filename, filename2, nv, nc);
    generer_declaration_vote(filename, filename2, filename3, nc);
}
