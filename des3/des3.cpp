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

}
