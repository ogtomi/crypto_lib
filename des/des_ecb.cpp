#include "des_ecb.h"

void DES_ECB::split_message(const std::string &message, std::vector<std::string> &message_vec)
{
    int message_block_len = 16;

    for(size_t i = 0; i < message.size(); i+=message_block_len)
    {
        message_vec.push_back(message.substr(i, message_block_len));
    }
}

void DES_ECB::encrypt(std::string &message)
{   
    std::vector<std::string> message_vec;
    split_message(message, message_vec);

    for(const auto &sub_string: message_vec)
    {
        std::cout << sub_string << std::endl;
    }
}
