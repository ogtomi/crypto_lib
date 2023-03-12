#include "des.h"
#include <iostream>
#include <sstream>
#include <iomanip>

void DES::to_binary(const std::string &str, std::bitset<1> *data)
{
    uint8_t len = 0;
    uint64_t value;

    for(size_t i = 0; i < str.size(); i++)
    {   
        std::string str_i(&str[i], 1);
        value = std::stoi(str_i, nullptr, 16);

        data[len++] = value >> 3;
        data[len++] = value >> 2;
        data[len++] = value >> 1;
        data[len++] = value;
    }
}

void DES::permute_pc1(std::bitset<1> *perm_key, const std::bitset<1> *k_data)
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

void DES::ip_message(std::bitset<1> *perm_message, const std::bitset<1> *m_data)
{
    for(int i = 0; i < 64; i++)
    {
        perm_message[i] = m_data[ip[i] - 1];
    }
}

void DES::split_key(std::bitset<1> *left_half_key, std::bitset<1> *right_half_key, const std::bitset<1> *perm_key)
{      
    for(size_t i = 0; i < 28; i++)
    {
        right_half_key[i] = perm_key[i + 28];
        left_half_key[i] = perm_key[i];
    }
}

void DES::split_message(std::bitset<1> *left_half_message, std::bitset<1> *right_half_message, const std::bitset<1> *perm_message)
{
    for(size_t i = 0; i < 32; i++)
    {
        right_half_message[i] = perm_message[i + 32];
        left_half_message[i] = perm_message[i];
    }
}

void DES::rotate(int n, std::bitset<1> *left_half_key, std::bitset<1> *right_half_key)
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
    std::bitset<1> k_data[64];
    std::bitset<1> perm_key[56];
    std::bitset<1> left_half_key[28];
    std::bitset<1> right_half_key[28];

    to_binary(key, k_data);
    permute_pc1(perm_key, k_data);
    split_key(left_half_key, right_half_key, perm_key);

    for(size_t i = 0; i < 16; i++)
    {
        rotate(no_shifts[i], left_half_key, right_half_key);

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

void DES::round_op(int i, std::bitset<1> *left_half_message, std::bitset<1> *right_half_message)
{
    std::bitset<1> right_half_message_expanded[48];
    std::bitset<1> xor_subkey[48];
    std::bitset<1> s[32];
    std::bitset<1> s_p[32];
    std::bitset<1> temp[32];

    int row;
    int col;
    int s_num;
    int s_index;

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

void DES::concat_halves(std::bitset<1> *concat_m, const std::bitset<1> *left_half_message, const std::bitset<1> *right_half_message)
{
    int j = 0;
    
    // Concat right and left halves of messages
    for(int i = 0; i < 64; i++)
    {
        if(j < 32)
        {
            concat_m[i] = right_half_message[j];
        }
        else
        {
            concat_m[i] = left_half_message[j - 32];
        }

        j++;
    }
}

void DES::final_permutation(std::bitset<1> *perm_m, const std::bitset<1> *m)
{
    // Final permutation
    for(int i = 0; i < 64; i++)
    {
        perm_m[i] = m[inv_ip[i] - 1];
    }
}

void DES::get_message(std::bitset<4> *m, const std::bitset<1> *perm_m)
{
    int k = 0;

    for(int i = 0; i < 16; i++)
    {
        m[i] = (perm_m[k].to_ulong() << 3) + (perm_m[k + 1].to_ulong() << 2) + (perm_m[k + 2].to_ulong() << 1) + (perm_m[k + 3].to_ulong());
        k += 4;
    }
}

void DES::encrypt(std::string &message)
{
    std::bitset<1> m_data[64];
    std::bitset<1> perm_message[64];
    std::bitset<1> left_half_message[32];
    std::bitset<1> right_half_message[32];
    std::bitset<1> c_message[64];
    std::bitset<1> c_message_perm[64];
    std::bitset<4> cipher_message[16];
    
    to_binary(message, m_data);
    ip_message(perm_message, m_data);
    split_message(left_half_message, right_half_message, perm_message);

    for(int i = 0; i < 16; i++)
    {
        round_op(i, left_half_message, right_half_message);
    }

    concat_halves(c_message, left_half_message, right_half_message);
    final_permutation(c_message_perm, c_message);
    get_message(cipher_message, c_message_perm);
    bits2string(message, cipher_message);
}

void DES::decrypt(std::string &cipher)
{
    std::bitset<1> m_data[64];
    std::bitset<1> perm_message[64];
    std::bitset<1> left_half_message[32];
    std::bitset<1> right_half_message[32];
    std::bitset<1> p_message[64];
    std::bitset<1> p_message_perm[64];
    std::bitset<4> plain_message[16];
    
    to_binary(cipher, m_data);
    ip_message(perm_message, m_data);
    split_message(left_half_message, right_half_message, perm_message);

    for(int i = 15; i >= 0; i--)
    {
        round_op(i, left_half_message, right_half_message);
    }
    
    concat_halves(p_message, left_half_message, right_half_message);
    final_permutation(p_message_perm, p_message);
    get_message(plain_message, p_message_perm);
    bits2string(cipher, plain_message);
}

void DES::bits2string(std::string &message, const std::bitset<4> *bits)
{
    std::stringstream ss;
    ss << std::setfill('0') << std::hex;

    for(int i = 0; i < 16; i++)
    {
        ss << std::setw(1) << bits[i].to_ulong();
    }

    message = ss.str();
}
