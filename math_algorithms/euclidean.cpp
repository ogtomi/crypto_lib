#include "euclidean.h"

int Euclidean::euclidean(int a, int b)
{
    if(b == 0)
        return a;
    
    return euclidean(b, a % b);
}

int Euclidean::extended_euclidean(int a, int b, int &x, int &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;

        return a;
    }

    int x1, y1;
    int gcd = extended_euclidean(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    
    return gcd;
}