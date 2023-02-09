#include "euclidean.h"

mpz_class Euclidean::euclidean(mpz_class a, mpz_class b)
{
    if(b == 0)
        return a;
    
    return euclidean(b, a % b);
}

mpz_class Euclidean::extended_euclidean(mpz_class a, mpz_class b, mpz_class &x, mpz_class &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;

        return a;
    }

    mpz_class x1, y1;
    mpz_class gcd = extended_euclidean(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    
    return gcd;
}
