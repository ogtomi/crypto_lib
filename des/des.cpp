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

void DES::permute_pc1()
{
    for(int i = 0; i < 56; i++)
    {
        perm_key[i] = m_data[pc_1[i] - 1];
    }
}

void DES::permute_pc2()
{
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 48; j++)
        {
            perm_subkeys[i][j] = subkeys[i][pc_2[j] - 1];
        }
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

void DES::split_message()
{
    for(size_t i = 0; i < 32; i++)
    {
        right_half_message[i] = m_data[i + 32];
        left_half_message[i] = m_data[i];
    }
}

void DES::rotate(int n)
{
    std::bitset<1> temp_right[28];
    std::bitset<1> temp_left[28];
    int k = 0;

    for(int i = n; i < 28; i++)
    {
        temp_right[k] = right_half_key[i];
        temp_left[k] = left_half_key[i];
        k++;
    }

    for(int i = 0; i < n; i++)
    {
        temp_right[k] = right_half_key[i];
        temp_left[k] = left_half_key[i];
        k++;
    }

    for(int i = 0; i < 28; i++)
    {
        right_half_key[i] = temp_right[i];
        left_half_key[i] = temp_left[i];
    }
}

void DES::generate_keys()
{
    for(size_t i = 0; i < 16; i++)
    {
        rotate(no_shifts[i]);

        for(size_t j = 0; j < 56; j++)
        {   
            if(j < 28)
            {
                subkeys[i][j] = left_half_key[j];
            }
            else
            {
                subkeys[i][j] = right_half_key[j - 28];
            }
        }
    }   
}

void DES::run_testing(const std::string &key)
{
    split_message();
    to_binary(key);
    permute_pc1();
    split_key();
    generate_keys();
    permute_pc2();

    for(auto const &subkey: perm_subkeys)
    {
        for(auto const &bit: subkey)
        {
            std::cout << bit;
        }
        std::cout << "\n";
    }
}
