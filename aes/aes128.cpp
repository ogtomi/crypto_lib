#include "aes128.h"

void AES_128::ascii_to_hex(std::string &ascii_str)
{
    std::stringstream ss;

    for(size_t i = 0; i < ascii_str.size(); i++)
    {
        ss.width(2);
        ss << std::hex << (unsigned) ascii_str[i];
    }

    ascii_str = ss.str();
}

void AES_128::run_testing(std::string &input)
{
    ascii_to_hex(input);
    std::cout << input << std::endl;
}
