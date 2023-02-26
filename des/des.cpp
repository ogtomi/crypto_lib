#include "des.h"
#include <iostream>
#include <sstream>
#include <iomanip>

void DES::to_binary_key(const std::string &str)
{
    uint8_t k_len = 0;
    uint64_t value;

    for(size_t i = 0; i < str.size(); i++)
    {   
        std::string str_i(&str[i], 1);
        value = std::stoi(str_i, nullptr, 16);

        k_data[k_len++] = value >> 3;
        k_data[k_len++] = value >> 2;
        k_data[k_len++] = value >> 1;
        k_data[k_len++] = value;
    }
}

void DES::to_binary_message(const std::string &str)
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
        perm_key[i] = k_data[pc_1[i] - 1];
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

void DES::ip_message()
{
    for(int i = 0; i < 64; i++)
    {
        perm_message[i] = m_data[ip[i] - 1];
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
        right_half_message[i] = perm_message[i + 32];
        left_half_message[i] = perm_message[i];
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

void DES::generate_keys(const std::string &key)
{
    to_binary_key(key);
    permute_pc1();
    split_key();

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
    
    permute_pc2();
}

void DES::encrypt(std::string &message)
{
    to_binary_message(message);
    ip_message();
    split_message();

    std::bitset<1> right_half_message_expanded[48];
    std::bitset<1> xor_subkey[48];
    std::bitset<1> s[32];
    std::bitset<1> s_p[32];
    std::bitset<1> temp[32];
    std::bitset<1> c_message[64];
    std::bitset<1> c_message_perm[64];

    int row;
    int col;
    int s_num;
    int s_index;

    for(int i = 0; i < 16; i++)
    {
        s_num = 0;
        s_index = 0;

        // Expansion
        for(int j = 0; j < 48; j++)
        {
            right_half_message_expanded[j] = right_half_message[expansion_table[j] - 1];
        }

        // XOR with subkey
        for(int j = 0; j < 48; j++)
        {   
            xor_subkey[j] = (perm_subkeys[i][j] ^ right_half_message_expanded[j]);
        }

        // Perform s_boxes operations
        for(int j = 0; j < 48; j+=6)
        {
            row = (xor_subkey[j].to_ulong() << 1) + (xor_subkey[j + 5].to_ulong());
            col = (xor_subkey[j + 1].to_ulong() << 3) + (xor_subkey[j + 2].to_ulong() << 2) + (xor_subkey[j + 3].to_ulong() << 1) + xor_subkey[j + 4].to_ulong();

            s[s_index++] = s_boxes[s_num][row][col] >> 3;
            s[s_index++] = s_boxes[s_num][row][col] >> 2;
            s[s_index++] = s_boxes[s_num][row][col] >> 1;
            s[s_index++] = s_boxes[s_num][row][col];

            s_num++;
        }

        // Permutation
        for(int j = 0; j < 32; j++)
        {
            s_p[j] = s[p[j] - 1];
        }

        // Feistel cipher
        for(int j = 0; j < 32; j++)
        {
            temp[j] = left_half_message[j];
            left_half_message[j] = right_half_message[j];
            right_half_message[j] = temp[j] ^ s_p[j];
        }
    }

    int j = 0;
    
    // Concat right and left halves of messages
    for(int i = 0; i < 64; i++)
    {
        if(j < 32)
        {
            c_message[i] = right_half_message[j];
        }
        else
        {
            c_message[i] = left_half_message[j - 32];
        }

        j++;
    }

    // Final permutation
    for(int i = 0; i < 64; i++)
    {
        c_message_perm[i] = c_message[inv_ip[i] - 1];
    }

    int k = 0;
    for(int i = 0; i < 16; i++)
    {
        cipher_message[i] = (c_message_perm[k++].to_ulong() << 3) + (c_message_perm[k++].to_ulong() << 2) + (c_message_perm[k++].to_ulong() << 1) + (c_message_perm[k++].to_ulong());
    }
}

void DES::bits2string(std::string &message)
{
    std::stringstream ss;
    ss << std::setfill('0') << std::hex;

    for(const auto &b: cipher_message)
    {
        ss << std::setw(1) << b.to_ulong();
    }

    message = ss.str();
}

void DES::run_testing(const std::string &key, std::string &message)
{
    generate_keys(key);
    encrypt(message);
    bits2string(message);
}
