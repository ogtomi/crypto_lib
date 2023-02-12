#include <iostream>
#include "sha256.h"

SHA256::SHA256()
    : m_len(0)
{

}

void SHA256::to_binary(const std::string &str)
{
    for(size_t i = 0; i < str.size(); i++)
    {
        m_data[i] = str[i];
        m_len++;
    }
}

void SHA256::pad()
{
    uint8_t i = m_len;
    uint8_t end = 56;

    m_data[i++] = 0x80;
    
    while(i < end)
    {
        m_data[i] = 0x00;
        i++;
    }

    uint64_t m_size = get_m_size();

    // Setting length bytes
    m_data[63] = m_size;
    m_data[62] = m_size >> 8;
    m_data[61] = m_size >> 16;
    m_data[60] = m_size >> 24;
    m_data[59] = m_size >> 32;
    m_data[58] = m_size >> 40;
    m_data[57] = m_size >> 48;
    m_data[56] = m_size >> 56;
}

void SHA256::transform()
{
    std::bitset<32> m[64];

    for(uint8_t i = 0, j = 0; i < 16; i++, j += 4)
    {
        m[i] = (m_data[j].to_ulong() << 24 | (m_data[j + 1].to_ulong() << 16) | (m_data[j + 2].to_ulong() << 8) | m_data[j + 3].to_ulong());
        std::cout << m[i] << std::endl;
    }

    for(uint8_t i = 16; i < 64 ; i++)
    {
        m[i] = 0x00000000;
    }
}

uint64_t SHA256::get_m_size()
{
    return m_len * byte_size;
}

void SHA256::run_testing()
{
    std::string str{"Hello world"};
    to_binary(str);
    pad();
    transform();

    for(std::bitset<8> &byte: m_data)
    {
        std::cout << byte << std::endl;
    }
}
