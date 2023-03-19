#include "des_cbc.h"

void DES_CBC::split_message(const std::string &message, std::vector<std::string> &message_vec)
{
    int message_block_len = 16;

    for(size_t i = 0; i < message.size(); i += message_block_len)
    {
        message_vec.push_back(message.substr(i, message_block_len));
    }
}

void DES_CBC::xor_iv(std::string &submessage, const std::string &init_vec)
{
    std::bitset<1> message_bin[64];
    std::bitset<1> init_vec_bin[64];
    std::bitset<4> message_bin_4[64];
    
    to_binary(init_vec, init_vec_bin);
    to_binary(submessage, message_bin);

    for(int i = 0; i < 64; i++)
    {
        message_bin[i] ^= init_vec_bin[i];
    }

    get_message(message_bin_4, message_bin);
    bits2string(submessage, message_bin_4);
}

void DES_CBC::encrypt(std::string &message, std::string &init_vec)
{
    std::vector<std::string> message_vec;

    split_message(message, message_vec);

    for(size_t i = 0; i < message_vec.size(); i++)
    {
        xor_iv(message_vec[i], init_vec);
        DES::encrypt(message_vec[i]);
        init_vec = message_vec[i];
    }

    message = "";

    for(size_t i = 0; i < message_vec.size(); i++)
    {
        message += message_vec[i];
    }
}

void DES_CBC::decrypt(std::string &cipher, std::string &init_vec)
{

}
