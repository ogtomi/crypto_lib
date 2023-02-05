#include <iostream>
#include <random>
#include <math.h>
#include "rsa.h"

RSA::RSA(int p, int q)
    :p(p), q(q), phi(0), n(0), e(0), d(0), public_key(nullptr), private_key(nullptr)
{
}

bool RSA::is_prime(int num)
{
    for(int i = 2; i < num; i++)
        if(num % i == 0)
            return false;
    
    return true;
}

int RSA::make_positive(int num, int mod)
{
    int tmp = num;

    while(tmp < 0)
    {
        tmp += mod;
    }

    return tmp;
}

void RSA::calculate_e()
{   
    while(e < phi)
    {
        if(euclidean(e, phi) == 1 && e > 1)
            break;

        e++;
    }
}

void RSA::calculate_d()
{
    int x = 0;
    extended_euclidean(phi, n, x, d);
    d = d < 0 ? make_positive(d, this->phi) : d;
}

void RSA::set_params()
{
    if(is_prime(p) && is_prime(q))
    {
        n = p * q;
        phi = (p - 1) * (q - 1);
    }

    calculate_e();
    calculate_d();
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
    gen_public_key();
    gen_private_key();
}

int RSA::encrypt(int message)
{   
    gen_keys();
    std::cout << "Phi: " << phi << std::endl;
    std::cout << "Public key e: " << public_key->e << " Public key n: " << public_key->n << std::endl;
    std::cout << "Private key d: " << private_key->d << " Private key n: " << private_key->n << std::endl;
    int c = pow(message, public_key->e);

    return c % public_key->n;
}

int RSA::decrypt(int message)
{
    int m = pow(message, private_key->d);
    return m % private_key->n;
}
