#ifndef _RSA_H_
#define _RSA_H_

#include "../math_algorithms/euclidean.h"

struct PublicKey
{
    long long int e;
    long long int n;
};

struct PrivateKey
{
    long long int d;
    long long int n;
};

class RSA : Euclidean
{
private:
    long long int p;
    long long int q;
    long long int phi;
    long long int n;
    long long int e = 3;
    long long int d;

    PublicKey* public_key;
    PrivateKey* private_key;

public:
    RSA();
    ~RSA();

    void gen_keys();
    double encrypt(int message);
    double decrypt(int message);

private:
    bool is_prime(long long int num) const;
    long long int make_positive(long long int num, long long int mod);
    void generate_pq();
    void calculate_d();
    void gen_public_key();
    void gen_private_key();
};

#endif
