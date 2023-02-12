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
    std::bitset<32> state[8];

    for(uint8_t i = 0; i < 8 ; i++)
    {
        state[i] = hash_val[i];
    }

    for(uint8_t i = 0, j = 0; i < 16; i++, j += 4)
    {
        m[i] = (m_data[j].to_ulong() << 24 | (m_data[j + 1].to_ulong() << 16) | (m_data[j + 2].to_ulong() << 8) | m_data[j + 3].to_ulong());
    }

    for(uint8_t i = 16; i < 64 ; i++)
    {
        m[i] = sig1(m[i - 2]).to_ulong() + m[i - 7].to_ulong() + sig0(m[i - 15]).to_ulong() + m[i - 16].to_ulong();
    }
}

uint64_t SHA256::get_m_size()
{
    return m_len * byte_size;
}

std::bitset<32> SHA256::rotate_r(std::bitset<32> w, uint32_t n)
{
    return ((w >> n)  | (w  << (32 - n)));
}

std::bitset<32> SHA256::sig0(std::bitset<32> w)
{
    return (rotate_r(w, 7) ^ rotate_r(w, 18) ^ (w >> 3));
}

std::bitset<32> SHA256::sig1(std::bitset<32> w)
{
    return (rotate_r(w, 17) ^ rotate_r(w, 19) ^ (w >> 10));
}

std::bitset<32> SHA256::choose(std::bitset<32> e, std::bitset<32> f, std::bitset<32> g)
{
    return (e & f) ^ (~e & g);
}

std::bitset<32> SHA256::majority(std::bitset<32> a, std::bitset<32> b, std::bitset<32> c)
{
    return (a & (b | c)) | (b & c);
}

void SHA256::run_testing()
{
    std::string str{"Hello world"};
    to_binary(str);
    pad();
    transform();

    for(std::bitset<8> &byte: m_data)
    {
        //std::cout << byte << std::endl;
    }
}
