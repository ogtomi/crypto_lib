#ifndef _DES_CBC_H_
#define _DES_CBC_H_

#include "des.h"
#include <vector>

class DES_CBC: public DES
{
private:
    std::bitset<1> subkeys[16][56];
    std::bitset<1> perm_subkeys[16][48];

public:
    void encrypt(std::string &message);
    void decrypt(std::string &cipher);

private:
    void split_message(const std::string &message, std::vector<std::string> &message_vec);
    void xor_iv(std::string &submessage, const std::string &init_vec);
};

#endif
