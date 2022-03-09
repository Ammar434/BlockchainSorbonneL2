#include "primalite.h"

int main()
{
    // // POUR EXO1
    // // calcul_1();
    // /*calcul_2();
    // printf("%ld\n",random_prime_number(25,100,5));
    // */
    // //-------------------------------------------------------------------------------------------------
    // // Generation de cle
    // srand(time(NULL));
    // long p = random_prime_number(3, 7, 5000);
    // long q = random_prime_number(3, 7, 5000);
    // while (p == q)
    // {
    //     q = random_prime_number(3, 7, 5000);
    // }
    // long n, s, u;
    // printf("LA\n");
    // generate_key_values(p, q, &n, &s, &u);
    // printf("LA\n");
    // if (u < 0)
    // {
    //     long t = (p - 1) * (q - 1);
    //     u += t; // on aura toujour s*u mod t = 1
    // }
    // // printf("s=%ld n=%ld u=%ld\n",s,n,u);
    // printf("cle publique = (%lx, %lx)\n", s, n);
    // printf("cle privee = (%lx, %lx)\n", u, n);
    // printf("cle publique = (%ld, %ld)\n", s, n);
    // printf("cle privee = (%ld, %ld)\n", u, n);
    // char message[10] = "Hello";
    // int len = strlen(message);

    // // Chiffrement:
    // long *crypted = encrypt(message, s, n);
    // printf("Initial message: %s\n", message);
    // printf("Encoded representation : \n");

    // print_long_vector(crypted, len);

    // // Dechiffrement

    // char *decoded = decrypt(crypted, len, u, n);
    // printf("Decoded: %s\n", decoded);
    // free(crypted);
    // free(decoded);
    Key *k = malloc(sizeof(Key));
    k->a = 1121212121921;
    k->b = 121213131232112;
    // char *test = key_to_str(k);
    // printf("%s\n", test);
    return 0;
}