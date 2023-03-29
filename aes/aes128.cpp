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
    int row = 0;
    int col = 0;

    for(size_t i = 0; i < hex_str.size(); i+=2)
    {   
        byte_str = hex_str.substr(i, 2);
        state_arr[row][col] = std::stoul(byte_str, 0, 16);

        row++;

        if(row == 4)
        {
            row = 0;
            col++;
        }
    }
}

void AES_128::sub_bytes(uint8_t state_arr[][4])
{
    uint8_t row_value = 0;
    uint8_t col_value = 0;

    for(int col = 0; col < 4; col++)
    {
        for(int row = 0; row < 4; row++)
        {
            row_value = (state_arr[row][col] >> 4) & 0x0F;
            col_value = state_arr[row][col] & 0x0F;
            state_arr[row][col] = s_box[row_value][col_value];
        }
    }
}

void AES_128::run_testing(std::string &key, std::string &message)
{
    ascii_to_hex(key);
    get_state_arr(key, state_arr);

    /*(for(auto const &bytes: state_arr)
    {
        for(auto const &byte: bytes)
        {
            std::cout << std::hex << (unsigned) byte << " ";
        }
        std::cout << "\n";
    }*/
    sub_bytes(state_arr);
    std::cout << "\n";
    std::cout << key << std::endl;
}
