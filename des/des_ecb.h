#ifndef _DES_ECB_H_
#define _DES_ECB_H_

#include "des.h"
#include <string>
#include <bitset>
#include <vector>
#include <iostream>

class DES_ECB: public DES
{
private:
    std::bitset<1> subkeys[16][56];
    std::bitset<1> perm_subkeys[16][48];

public:
    void encrypt(std::string &message);
    void decrypt(std::string &cipher);

private: 
    void split_message(const std::string &message, std::vector<std::string> &message_vec);
};

#endif
