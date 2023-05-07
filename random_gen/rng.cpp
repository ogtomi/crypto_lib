#include "rng.h"

std::string RNG::generate_iv(uint8_t len)
{
    std::string iv_str{};
    unsigned char iv[len];

    int rc = RAND_bytes(iv, len);
    unsigned long err = ERR_get_error();

    if(rc != 1)
    {
        std::cout << err << std::endl;
    }

    bytes_to_hex_str(iv_str, iv, len);

    return iv_str;
}
