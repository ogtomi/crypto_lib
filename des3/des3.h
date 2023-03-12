#ifndef _DES3_H_
#define _DES3_H_

#include "../des/des.h"
#include <iostream>

class DES3: DES
{
private:
    std::bitset<1> subkeys[3][16][56];
    std::bitset<1> perm_subkeys[3][16][48];
    
public:
    void generate_keys(const std::string *keys);
    void encrypt(std::string &message);
    void decrypt(std::string &cipher);

private:
    void permute_pc2();
};

#endif
