#include "primalite.h"
#include <time.h>
int main()
{
    printf("%ld \n", modpow(2, 9, 1));
    printf("%ld \n", modpow_naive(2, 9, 1));
    return 0;
}
