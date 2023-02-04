#include <iostream>
#include <random>
#include "rsa.h"

RSA::RSA(double p, double q)
    :p{p}, q{q}
{
}

int RSA::gcd(int a, int b)
{
    if(b == 0)
        return a;
    
    return gcd(b, a % b);
}

void RSA::choose_e()
{   
    while(e < phi)
    {
        if(gcd(e, phi) == 1 && e > 1)
            break;

        e++;
    }
}

void RSA::calculate_d()
{
    d = (1 + (k * phi)) / e;
}

double RSA::encrypt(double message)
{   
    calculate_n();
    calculate_phi();
    choose_e();

    double c = pow(message, e);
    return fmod(c, n);
}

double RSA::decrypt(double message)
{
    calculate_d();
    double m = pow(message, d);
    return fmod(m, n);
}
