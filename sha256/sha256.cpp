#include <iostream>
#include <sstream>
#include <iomanip>
#include "sha256.h"

SHA256::SHA256()
    : m_len(0)
{
    hash_val[0] = 0x6a09e667;
    hash_val[1] = 0xbb67ae85;
    hash_val[2] = 0x3c6ef372;
    hash_val[3] = 0xa54ff53a;
    hash_val[4] = 0x510e527f;
    hash_val[5] = 0x9b05688c;
    hash_val[6] = 0x1f83d9ab;
    hash_val[7] = 0x5be0cd19;
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
    std::bitset<32> maj, ch, t1, t2, sig_a, sig_e;

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

    for(uint8_t i = 0; i < 64; i++)
    {
        maj = majority(state[0], state[1], state[2]);
        ch = choose(state[4], state[5], state[6]);

        sig_a = rotate_r(state[0], 2) ^ rotate_r(state[0], 13) ^ rotate_r(state[0], 22);
        sig_e = rotate_r(state[4], 6) ^ rotate_r(state[4], 11) ^ rotate_r(state[4], 25);

        t1 = state[7].to_ulong() + sig_e.to_ulong() + ch.to_ulong() + K[i].to_ulong() + m[i].to_ulong();
        t2 = sig_a.to_ulong() + maj.to_ulong();

        state[7] = state[6];
        state[6] = state[5];
        state[5] = state[4];
        state[4] = state[3].to_ulong() + t1.to_ulong();
        state[3] = state[2];
        state[2] = state[1];
        state[1] = state[0];
        state[0] = t1.to_ulong() + t2.to_ulong();
    }

    for(uint8_t i = 0; i < 8; i++)
    {
        hash_val[i] = hash_val[i].to_ulong() + state[i].to_ulong();
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

std::string SHA256::get_hash_str(std::string input_str)
{
    std::stringstream ss;
    ss << std::setfill('0') <<std::hex;

    to_binary(input_str);
    pad();
    transform();

    for(auto const &w: hash_val)
    {   
        ss << std::setw(8) << w.to_ulong();
    }

    std::string hash_str(ss.str());
    
    return hash_str;
}
