#ifndef _EUCLIDEAN_H_
#define _EUCLIDEAN_H_

class Euclidean
{
public:
    Euclidean() = default;
    ~Euclidean(){};
    long long int euclidean(long long int a, long long int b);
    long long int extended_euclidean(long long int a, long long int b, long long int &x, long long int &y);
};

#endif
