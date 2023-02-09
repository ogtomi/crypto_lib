#ifndef _RSA_H_
#define _RSA_H_

#include <gmp.h>
#include <gmpxx.h>
#include "../math_algorithms/euclidean.h"

struct PublicKey
{
    mpz_class e;
    mpz_class n;
};

struct PrivateKey
{
    mpz_class d;
    mpz_class n;
};

class RSA : Euclidean
{
private:
    const mpz_class e = 3;
    mpz_class p;
    mpz_class q;
    mpz_class phi;
    mpz_class n;
    mpz_class d;

    PublicKey* public_key;
    PrivateKey* private_key;

public:
    RSA();
    ~RSA();

    void gen_keys();
    void encrypt(mpz_class &enrypted_message, mpz_class message);
    void decrypt(mpz_class &decrypted_message, mpz_class message);

private:
    bool is_prime(mpz_class num) const;
    mpz_class make_positive(mpz_class num, mpz_class mod);
    void set_params();
    void calculate_d();
    void gen_public_key();
    void gen_private_key();
};

#endif
