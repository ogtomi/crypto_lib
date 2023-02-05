#ifndef _EUCLIDEAN_H_
#define _EUCLIDEAN_H_

class Euclidean
{
public:
    Euclidean() = default;
    ~Euclidean(){};
    int euclidean(int a, int b);
    int extended_euclidean(int a, int b, int &x, int &y);
};

#endif
