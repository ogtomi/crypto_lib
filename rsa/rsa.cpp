#include <iostream>
#include <random>
#include <cmath>
#include "rsa.h"

RSA::RSA()
    :p(0), q(0), phi(0), n(0), d(0), public_key(nullptr), private_key(nullptr)
{
}

RSA::~RSA()
{
    delete public_key;
    delete private_key;
}

bool RSA::is_prime(long long int num) const
{
    for(long long int i = 2; i < num; i++)
        if(num % i == 0)
            return false;
    
    return true;
}

long long int RSA::make_positive(long long int num, long long int mod)
{
    long long int tmp = num;

    while(tmp < 0)
    {
        tmp += mod;
    }

    return tmp;
}

void RSA::set_params()
{
    srand((unsigned)time(NULL));

    while(true)
    {
        p = rand() % 19 + 2;
        q = rand() % 19 + 2;
        phi = (p - 1) * (q - 1);

        if(is_prime(p) && is_prime(q) && euclidean(e, phi) == 1 && p != q)
        {
            if(p > q)
            {
                long long int tmp;

                tmp = p;
                p = q;
                q = tmp;
            }

            n = p * q;
            break;
        }    
    }
}

void RSA::calculate_d()
{
    long long int x = 0;
    extended_euclidean(phi, e, x, d);
    d = d < 0 ? make_positive(d, phi) : d;
}

void RSA::gen_public_key()
{
    this->public_key = new PublicKey{this->e, this->n};
}

void RSA::gen_private_key()
{
    this->private_key = new PrivateKey{this->d, this->n};
}

void RSA::gen_keys()
{   
    set_params();
    calculate_d();
    gen_public_key();
    gen_private_key();
}

double RSA::encrypt(int message)
{   
    return fmod((pow(message, public_key->e)), public_key->n);
}

double RSA::decrypt(int message)
{
    return fmod((pow(message, private_key->d)), private_key->n);
}
