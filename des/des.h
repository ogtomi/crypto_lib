#ifndef _DES_H_
#define _DES_H_

#include <string>
#include <bitset>

class DES
{
private:
    std::bitset<1> k_data[64];
    std::bitset<1> m_data[64];
    std::bitset<1> perm_message[64];
    std::bitset<1> right_half_message[32];
    std::bitset<1> left_half_message[32];
    std::bitset<1> perm_key[56];
    std::bitset<1> right_half_key[28];
    std::bitset<1> left_half_key[28];
    std::bitset<1> subkeys[16][56];
    std::bitset<1> perm_subkeys[16][48];
    
    uint8_t no_shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    const uint8_t pc_1[56] = { 57, 49, 41, 33, 25, 17, 9,
                                1, 58, 50, 42, 34, 26, 18,
                                10, 2, 59, 51, 43, 35, 27,
                                19, 11, 3, 60, 52, 44, 36,
                                63, 55, 47, 39, 31, 23, 15,
                                7, 62, 54, 36, 38, 30, 22,
                                14, 6, 61, 53, 45, 37, 29,
                                21, 13, 5, 28, 20, 12, 4 };

    const uint8_t pc_2[48] = { 14, 17, 11, 24, 1, 5,
                                3, 28, 15, 6, 21, 10,
                                23, 19, 12, 4, 26, 8,
                                16, 7, 27, 20, 13, 2,
                                41, 52, 31, 37, 47, 55,
                                30, 40, 51, 45, 33, 48,
                                44, 49, 39, 56, 34, 53,
                                46, 42, 50, 36, 29, 32 };

    const uint8_t ip[64] = { 58, 50, 42, 34, 26, 18 ,10, 2,
                            60, 52, 44, 36, 28, 20, 12, 4,
                            62, 54, 46, 38, 30, 22, 14, 6,
                            64, 56, 48, 40, 32, 24, 16, 8,
                            57, 49, 41, 33, 25, 17, 9, 1,
                            59, 51, 43, 35, 27, 19, 11, 3,
                            61, 53, 45, 37, 29, 21, 13, 5,
                            63, 55, 47, 39, 31, 23, 15, 7};

public: 
    void run_testing(const std::string &key, const std::string &message);

private:
    void to_binary_key(const std::string &str);
    void to_binary_message(const std::string &str);
    void permute_pc1();
    void permute_pc2();
    void ip_message();
    void split_key();
    void split_message();
    void rotate(int n);
    void generate_keys();
};

#endif
