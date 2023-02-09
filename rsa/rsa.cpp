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

bool RSA::is_prime(mpz_class num) const
{
    for(mpz_class i = 2; i < num; i++)
        if(num % i == 0)
            return false;
    
    return true;
}

mpz_class RSA::make_positive(mpz_class num, mpz_class mod)
{
    mpz_class tmp = num;

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
        p = rand() % 100 + 3;
        q = rand() % 100 + 3;
        phi = (p - 1) * (q - 1);
        
        if(is_prime(p) && is_prime(q) && euclidean(e, phi) == 1 && p != q)
        {
            if(p > q)
            {
                mpz_class tmp;

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
    mpz_class x = 0;
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

void RSA::encrypt(mpz_class &encrypted_message, mpz_class message)
{   
    mpz_powm_sec(encrypted_message.get_mpz_t(), message.get_mpz_t(), public_key->e.get_mpz_t(), public_key->n.get_mpz_t());
}

void RSA::decrypt(mpz_class &decrypted_message, mpz_class message)
{   
    mpz_powm_sec(decrypted_message.get_mpz_t(), message.get_mpz_t(), private_key->d.get_mpz_t(), private_key->n.get_mpz_t());
}
