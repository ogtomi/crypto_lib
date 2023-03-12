#include "des3.h"

void DES3::permute_pc2()
{
    for(int k = 0; k < 3; k++)
    {
        for(int i = 0; i < 16; i++)
        {
            for(int j = 0; j < 48; j++)
            {
                perm_subkeys[k][i][j] = subkeys[k][i][pc_2[j] - 1];
            }
        }
    }
}

void DES3::generate_keys(const std::string *keys)
{
    for(int k = 0; k < 3; k++)
    {
        std::bitset<1> k_data[64];
        std::bitset<1> perm_key[56];
        std::bitset<1> left_half_key[28];
        std::bitset<1> right_half_key[28];

        to_binary(keys[k], k_data);
        permute_pc1(perm_key, k_data);
        split_key(left_half_key, right_half_key, perm_key);

        for(size_t i = 0; i < 16; i++)
        {
            rotate(no_shifts[i], left_half_key, right_half_key);
                    
            for(size_t j = 0; j < 56; j++)
            {
                if(j < 28)
                {
                    subkeys[k][i][j] = left_half_key[j];
                }
                else
                {
                    subkeys[k][i][j] = right_half_key[j - 28];
                }
            }
        }
    }

    permute_pc2();
}

void DES3::encrypt(std::string &message)
{
    std::bitset<1> m_data[64];
    std::bitset<1> perm_message[64];
    std::bitset<1> left_half_message[32];
    std::bitset<1> right_half_message[32];
    std::bitset<1> c_message[64];
    std::bitset<1> c_message_perm[64];
    std::bitset<4> cipher_message[16];

    to_binary(message, m_data);

    // 1st round - encryption with the first set of subkeys
    ip_message(perm_message, m_data);
    split_message(left_half_message, right_half_message, perm_message);

    for(int i = 0; i < 16; i++)
    {
        round_op(i, left_half_message, right_half_message, perm_subkeys[0]);
    }

    concat_halves(c_message, left_half_message, right_half_message);
    final_permutation(c_message_perm, c_message);

    // 2nd round - decryption with the second set of subkeys
    ip_message(perm_message, c_message_perm);
    split_message(left_half_message, right_half_message, perm_message);

    for(int i = 15; i >= 0; i--)
    {
        round_op(i, left_half_message, right_half_message, perm_subkeys[1]);
    }

    concat_halves(c_message, left_half_message, right_half_message);
    final_permutation(c_message_perm, c_message);

    // 3rd round - encryption with the third set of subkeys
    ip_message(perm_message, c_message_perm);
    split_message(left_half_message, right_half_message, perm_message);

    for(int i = 0; i < 16; i++)
    {
        round_op(i, left_half_message, right_half_message, perm_subkeys[2]);
    }

    concat_halves(c_message, left_half_message, right_half_message);
    final_permutation(c_message_perm, c_message);
    get_message(cipher_message, c_message_perm);
    bits2string(message, cipher_message);
}

void DES3::decrypt(std::string &cipher)
{
    std::bitset<1> m_data[64];
    std::bitset<1> perm_message[64];
    std::bitset<1> left_half_message[32];
    std::bitset<1> right_half_message[32];
    std::bitset<1> p_message[64];
    std::bitset<1> p_message_perm[64];
    std::bitset<4> plain_message[16];

    to_binary(cipher, m_data);
    
    // 1st round - decryption with the 3rd set of keys
    ip_message(perm_message, m_data);
    split_message(left_half_message, right_half_message, perm_message);

    for(int i = 15; i >= 0; i--)
    {
        round_op(i, left_half_message, right_half_message, perm_subkeys[2]);
    }

    concat_halves(p_message, left_half_message, right_half_message);
    final_permutation(p_message_perm, p_message);

    // 2nd round - encryption with the 2nd set of keys
    ip_message(perm_message, p_message_perm);
    split_message(left_half_message, right_half_message, perm_message);

    for(int i = 0; i < 16; i++)
    {
        round_op(i, left_half_message, right_half_message, perm_subkeys[1]);
    }

    concat_halves(p_message, left_half_message, right_half_message);
    final_permutation(p_message_perm, p_message);

    // 3rd round - decryption with the 1st set of keys
    ip_message(perm_message, p_message_perm);
    split_message(left_half_message, right_half_message, perm_message);

    for(int i = 15; i >= 0; i--)
    {
        round_op(i, left_half_message, right_half_message, perm_subkeys[0]);
    }

    concat_halves(p_message, left_half_message, right_half_message);
    final_permutation(p_message_perm, p_message);
    get_message(plain_message, p_message_perm);
    bits2string(cipher, plain_message);
}
