#ifndef _AES_128_H_
#define _AES_128_H_

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

class AES_128
{
private:
    uint8_t state_arr[4][4];

public:
    void run_testing(std::string &input);

private:
    void ascii_to_hex(std::string &ascii_str);
    void get_state_arr(const std::string &hex_str, uint8_t state_arr[][4]);
};

#endif
