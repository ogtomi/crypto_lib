#ifndef _AES_128_H_
#define _AES_128_H_

#include <string>
#include <iostream>
#include <sstream>

class AES_128
{
public:
    void run_testing(std::string &input);

private:
    void ascii_to_hex(std::string &ascii_str);
};

#endif
