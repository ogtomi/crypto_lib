#include "conversion.h"

void hexstr_to_uint8t(const std::string &hex_str, uint8_t *data)
{
    std::string byte_str;
    int j = 0;

    for(size_t i = 0; i < hex_str.size(); i+=2)
    {
        byte_str = hex_str.substr(i, 2);
        data[j] = std::stoul(byte_str, 0, 16);
        j++;
    }
}

void uint8t_to_hexstr(std::string &hex_str, uint8_t *data, const size_t data_len)
{
    std::stringstream ss;
    ss << std::setfill('0') << std::hex;

    for(size_t i = 0; i < data_len; i++)
    {
        ss << std::setw(2) << std::hex << (unsigned)data[i];
    }

    hex_str = ss.str();
}

void ascii_to_hex(std::string &ascii_str)
{
    std::stringstream ss;

    for(size_t i = 0; i < ascii_str.size(); i++)
    {
        ss.width(2);
        ss << std::hex << (unsigned) ascii_str[i];
    }

    ascii_str = ss.str();
}
