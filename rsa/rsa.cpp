#include <iostream>
#include <random>
#include <cmath>
#include "rsa.h"

RSA::RSA(long long int p, long long int q)
    :p(p), q(q), phi(0), n(0), e(0), d(0), public_key(nullptr), private_key(nullptr)
{
}

RSA::~RSA()
{
    delete public_key;
    delete private_key;
}

bool RSA::is_prime(long long int num) const
{
    for(int i = 2; i < num; i++)
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

void RSA::calculate_e()
{   

    srand((unsigned int)time(NULL));

    while(true)
    {
        e = rand() % phi;
        
        if(euclidean(e, phi) == 1 && euclidean(e, n) == 1 && e > 1)
            break;
    }
}

void RSA::calculate_d()
{
    long long int x = 0;
    extended_euclidean(phi, e, x, d);
    d = d < 0 ? make_positive(d, phi) : d;
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

double RSA::encrypt(int message)
{   
    std::cout << "N: " << n << std::endl;
    std::cout << "Phi: " << phi << std::endl;
    std::cout << "Public key e: " << public_key->e << std::endl;
    std::cout << "Private key d: " << private_key->d << std::endl;
    
    return fmod((pow(message, public_key->e)), public_key->n);
}

double RSA::decrypt(int message)
{
    return fmod((pow(message, private_key->d)), private_key->n);
}
