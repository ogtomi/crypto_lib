#ifndef _SHA256_H_
#define _SHA256_H_

#include <string>
#include <bitset>
#include <vector>

class SHA256
{
private:
    const uint8_t byte_size = 8;
    std::bitset<8> m_data[64];
    uint8_t m_len;

public:
    SHA256();
    ~SHA256() {};
    void run_testing();

private:
    void to_binary(const std::string &str);
    void pad();
    uint8_t get_m_size();
};

#endif
