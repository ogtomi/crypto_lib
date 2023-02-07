#include "euclidean.h"

long long int Euclidean::euclidean(long long int a, long long int b)
{
    if(b == 0)
        return a;
    
    return euclidean(b, a % b);
}

long long int Euclidean::extended_euclidean(long long int a, long long int b, long long int &x, long long int &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;

        return a;
    }

    long long int x1, y1;
    long long int gcd = extended_euclidean(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    
    return gcd;
}
