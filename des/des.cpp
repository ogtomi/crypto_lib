#include "des.h"
#include <iostream>

void DES::to_binary(const std::string str)
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

    for(auto const &bit: m_data)
    {
        std::cout << bit;
    }
}

void DES::permute()
{
    for(int i = 0; i < 56; i++)
    {
        perm_key[i] = m_data[pc_1[i] - 1];
        //std::cout << perm_key[i] << std::endl;
    }
}

void DES::run_testing(std::string key)
{
    to_binary(key);
    for(auto const &bit: m_data)
    {
        std::cout << bit;
    }
    std::cout << "\n";
    permute();
    std::cout << perm_key << std::endl;
}
