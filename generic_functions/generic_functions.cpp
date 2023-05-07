#include "generic_functions.h"

void xor_iv(std::string &submessage, const std::string &init_vec)
{
    uint8_t submessage_bin[32];
    uint8_t init_vec_bin[32];
    size_t data_len = sizeof(submessage_bin) / (2 * sizeof(*submessage_bin));

    hexstr_to_uint8t(init_vec, init_vec_bin);
    hexstr_to_uint8t(submessage, submessage_bin);

    for(int i = 0; i < 64; i++)
    {
        submessage_bin[i] ^= init_vec_bin[i];
    }

    uint8t_to_hexstr(submessage, submessage_bin, data_len);
}