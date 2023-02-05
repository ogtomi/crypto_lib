#include "euclidean.h"

int Euclidean::euclidean(int a, int b)
{
    if(b == 0)
        return a;
    
    return euclidean(b, a % b);
}