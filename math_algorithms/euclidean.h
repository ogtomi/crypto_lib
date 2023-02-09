#ifndef _EUCLIDEAN_H_
#define _EUCLIDEAN_H_

#include <gmp.h>
#include <gmpxx.h>

class Euclidean
{
public:
    Euclidean() = default;
    ~Euclidean(){};
    mpz_class euclidean(mpz_class a, mpz_class b);
    mpz_class extended_euclidean(mpz_class a, mpz_class b, mpz_class &x, mpz_class &y);
};

#endif
