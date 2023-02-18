#include "des.h"
#include <iostream>

void DES::to_binary(const std::string &str)
{
    uint8_t m_len = 0;
    uint64_t value;

    for(size_t i = 0; i < str.size(); i++)
    {   
        std::string str_i(&str[i], 1);
        value = std::stoi(str_i, nullptr, 16);

        m_data[m_len++] = value >> 3;
        m_data[m_len++] = value >> 2;
        m_data[m_len++] = value >> 1;
        m_data[m_len++] = value;
    }
}

void DES::permute()
{
    for(int i = 0; i < 56; i++)
    {
        perm_key[i] = m_data[pc_1[i] - 1];
    }
}

void DES::split_key()
{      
    for(size_t i = 0; i < 28; i++)
    {
        right_half_key[i] = perm_key[i + 28];
        left_half_key[i] = perm_key[i];
    }
}

void DES::run_testing(const std::string &key)
{
    to_binary(key);
    permute();
    split_key();
}
