#ifndef _RSA_H_
#define _RSA_H_

#include "../math_algorithms/euclidean.h"

struct PublicKey
{
    int e;
    int n;
};

struct PrivateKey
{
    int d;
    int n;
};

class RSA : Euclidean
{
private:
    int p;
    int q;
    int phi;
    int n;
    int e;
    int d;

    PublicKey* public_key;
    PrivateKey* private_key;

public:
    RSA(int p, int q);
    ~RSA(){};

    int encrypt(int message);
    int decrypt(int message);

private:
    bool is_prime(int num);
    void calculate_e();
    void calculate_d();
    void set_params();
    void gen_public_key();
    void gen_private_key();
    void gen_keys();
};

#endif