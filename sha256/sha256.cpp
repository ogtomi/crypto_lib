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
}

uint8_t SHA256::get_m_size()
{
    return m_len * byte_size;
}

void SHA256::run_testing()
{
    std::string str{"Hello world"};
    to_binary(str);
    pad();
    
    for(std::bitset<8> &byte: m_data)
    {
        std::cout << byte << std::endl;
    }
}
