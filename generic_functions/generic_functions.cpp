#include "generic_functions.h"

void xor_iv(std::string &submessage, const std::string &init_vec, const uint8_t &block_size)
{
    uint8_t submessage_bin[block_size];
    uint8_t init_vec_bin[block_size];

    hexstr_to_uint8t(init_vec, init_vec_bin);
    hexstr_to_uint8t(submessage, submessage_bin);

    for(int i = 0; i < block_size; i++)
    {
        submessage_bin[i] ^= init_vec_bin[i];
    }

    uint8t_to_hexstr(submessage, submessage_bin, block_size);
}

void bytes_to_hex_str(std::string &hex_str, const unsigned char *byte_arr, const int size)
{
    std::stringstream ss;
    ss << std::setfill('0') << std::hex;

    for(int i = 0; i < size; i++)
    {
        ss << std::setw(2) << std::hex << (unsigned)byte_arr[i];
    }

    hex_str = ss.str();
}
