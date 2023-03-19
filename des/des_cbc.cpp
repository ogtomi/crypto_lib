#include "des_cbc.h"

void DES_CBC::split_message(const std::string &message, std::vector<std::string> &message_vec)
{
    int message_block_len = 16;

    for(size_t i = 0; i < message.size(); i += message_block_len)
    {
        message_vec.push_back(message.substr(i, message_block_len));
    }
}

void DES_CBC::encrypt(std::string &message)
{

}

void DES_CBC::decrypt(std::string &cipher)
{

}
