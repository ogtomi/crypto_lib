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

void AES_128::get_arr(const std::string &hex_str, uint8_t arr[][4])
{   
    std::string byte_str;
    int row = 0;
    int col = 0;

    for(size_t i = 0; i < hex_str.size(); i+=2)
    {   
        byte_str = hex_str.substr(i, 2);
        arr[row][col] = std::stoul(byte_str, 0, 16);

        row++;

        if(row == 4)
        {
            row = 0;
            col++;
        }
    }
}

void AES_128::sub_bytes(uint8_t arr[][4])
{
    uint8_t row_value = 0;
    uint8_t col_value = 0;

    for(int col = 0; col < 4; col++)
    {
        for(int row = 0; row < 4; row++)
        {
            row_value = (arr[row][col] >> 4) & 0x0F;
            col_value = arr[row][col] & 0x0F;
            arr[row][col] = s_box[row_value][col_value];
        }
    }
}

void AES_128::rot_word(uint8_t *word)
{
    uint8_t temp = word[0];

    for(int i = 0; i < 3; i++)
    {
        word[i] = word[i + 1];
    }

    word[3] = temp;
}

void AES_128::add_round_key(uint8_t key_arr[][4])
{

}



void AES_128::run_testing(std::string &key, std::string &message)
{
    ascii_to_hex(key);
    get_arr(key, key_arr);
    sub_bytes(key_arr);
    
    for(const auto &byte: key_arr[0])
    {
        std::cout << std::hex << (unsigned) byte;
    }

    std::cout << "\n";

    rot_word(key_arr[0]);

    for(const auto &byte: key_arr[0])
    {
        std::cout << std::hex << (unsigned) byte;
    }

    std::cout << "\n";

}
