#include "aes128.h"

void AES_128::ascii_to_hex(std::string &ascii_str)
{
    std::stringstream ss;

    for(size_t i = 0; i < ascii_str.size(); i++)
    {
        ss.width(2);
        ss << std::hex << (unsigned int) ascii_str[i];
    }

    ascii_str = ss.str();
}

void AES_128::get_state_arr(const std::string &hex_str, uint8_t state_arr[][4])
{   
    std::string byte_str;
    int byte_num = 0;
    int word_num = 0;

    for(size_t i = 0; i < hex_str.size(); i+=2)
    {   
        byte_str = hex_str.substr(i, 2);
        state_arr[word_num][byte_num] = std::stoul(byte_str, 0, 16);

        byte_num++;

        if(byte_num == 4)
        {
            byte_num = 0;
            word_num++;
        }
    }
}

void AES_128::run_testing(std::string &input)
{
    ascii_to_hex(input);
    get_state_arr(input, state_arr);

    for(const auto &word: state_arr)
        for(const auto &byte: word)
            std::cout << std::hex << (unsigned int) byte;
    std::cout << "\n";
    std::cout << input << std::endl;
}
