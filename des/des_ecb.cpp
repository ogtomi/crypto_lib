#include "des_ecb.h"

void DES_ECB::split_message(const std::string &message, std::vector<std::string> &message_vec)
{
    int message_block_len = 16;

    for(size_t i = 0; i < message.size(); i += message_block_len)
    {
        message_vec.push_back(message.substr(i, message_block_len));
    }
}

void DES_ECB::encrypt(std::string &message)
{   
    std::vector<std::string> message_vec;
    split_message(message, message_vec);

    for(size_t i = 0; i < message_vec.size(); i++)
    {
        DES::encrypt(message_vec[i]);
    }

    message = "";

    for(size_t i = 0; i < message_vec.size(); i++)
    {
        message += message_vec[i];
    }
}

void DES_ECB::decrypt(std::string &cipher)
{
    std::vector<std::string> cipher_vec;
    split_message(cipher, cipher_vec);

    for(size_t i = 0; i < cipher_vec.size(); i++)
    {
        DES::decrypt(cipher_vec[i]);
    }

    cipher = "";

    for(size_t i = 0; i < cipher_vec.size(); i++)
    {
        cipher += cipher_vec[i];
    }
}
