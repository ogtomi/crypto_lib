#include "aes.h"

AES::AES(const AES_key_length key_length)
{
    switch(key_length)
    {
        case AES_key_length::AES_128:
            this->nk = 4;
            this->nr = 10;
            break;
        
        case AES_key_length::AES_192:
            this->nk = 6;
            this->nr = 12;
            break;
        
        case AES_key_length::AES_256:
            this->nk = 8;
            this->nr = 14;
            break;
    }
}

AES::~AES()
{
    for(unsigned i = 0; i < (nr + 1); i++)
    {
        for(unsigned j = 0; j < nk; j++)
        {
            delete[] round_keys[i][j];
        }

        delete[] round_keys[i];
    }

    delete[] round_keys;
}

void AES::init_round_keys()
{
    for(unsigned i = 0; i < (nr + 1); i++)
    {
        round_keys[i] = new uint8_t*[nk];

        for(unsigned j = 0; j < nk; j++)
        {
            round_keys[i][j] = new uint8_t[4];
        }
    }
}

void AES::ascii_to_hex(std::string &ascii_str)
{
    std::stringstream ss;

    for(size_t i = 0; i < ascii_str.size(); i++)
    {
        ss.width(2);
        ss << std::hex << (unsigned int) ascii_str[i];
    }

    ascii_str = ss.str();
}

void AES::get_state_arr(const std::string &hex_str, uint8_t state_arr[][4])
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

void AES::get_key_arr(const std::string &hex_str, uint8_t key_arr[][4])
{   
    std::string byte_str;
    int row = 0;
    int col = 0;

    for(size_t i = 0; i < hex_str.size(); i+=2)
    {   
        byte_str = hex_str.substr(i, 2);
        key_arr[row][col] = std::stoul(byte_str, 0, 16);

        col++;

        if(col == 4)
        {
            col = 0;
            row++;
        }
    }
}

void AES::uint8_to_32(const uint8_t *arr, uint32_t &word)
{
    word = ((arr[3] << 24) | (arr[2] << 16) | (arr[1] << 8) | arr[0]);
}

void AES::uint32_to_8(uint8_t *arr, const uint32_t &word)
{
    arr[3] = (word & 0xFF000000) >> 24;
    arr[2] = (word & 0x00FF0000) >> 16;
    arr[1] = (word & 0x0000FF00) >> 8;
    arr[0] = (word & 0x000000FF);
}

void AES::rot_word(uint8_t *byte_arr)
{
    uint8_t temp = byte_arr[0];

    for(int i = 0; i < 3; i++)
    {
        byte_arr[i] = byte_arr[i + 1];
    }

    byte_arr[3] = temp;
}

void AES::sub_word(uint8_t *byte_arr)
{
    uint8_t row_value = 0;
    uint8_t col_value = 0;

    for(int i = 0; i < 4; i++)
    {
        row_value = (byte_arr[i] >> 4) & 0x0F;
        col_value = byte_arr[i] & 0x0F;
        byte_arr[i] = s_box[row_value][col_value];
    }
}

void AES::expand_key(uint8_t key_arr[][4], uint32_t *key_expanded)
{
    uint32_t temp;
    uint8_t temp_arr[4];

    for(int i = 0; i < 4; i++)
    {
        uint8_to_32(key_arr[i], key_expanded[i]);
    }

    for(int i = 4; i < 44; i++)
    {
        temp = key_expanded[i - 1];

        if(i % 4 == 0)
        {
            uint32_to_8(temp_arr, temp);
            rot_word(temp_arr);
            sub_word(temp_arr);
            uint8_to_32(temp_arr, temp);

            temp ^= rcon[i / 4];
        }

        key_expanded[i] = key_expanded[i - 4] ^ temp; 
    }
}

void AES::get_round_keys(uint32_t *key_expanded)
{
    int k = 0;

    for(int i = 0; i < 11; i++)
    {
        for(int row = 0; row < 4; row++)
        {
            uint32_to_8(round_keys[i][row], key_expanded[k]);
            k++;
        }
    }
}

void AES::add_round_key(uint8_t state_arr[][4], int round)
{
    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            state_arr[row][col] ^= round_keys[round][col][row];
        }
    }
}

void AES::sub_bytes(uint8_t arr[][4])
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

void AES::shift_rows(uint8_t state_arr[][4])
{
    for(int row = 0; row < 4; row++)
    {
        for(int i = 0; i < row; i++)
        {
            uint8_t temp = state_arr[row][0];

            for(int j = 0; j < 3; j++)
            {
                state_arr[row][j] = state_arr[row][j + 1];
            }

            state_arr[row][3] = temp;
        }
    }
}

void AES::mix_columns(uint8_t state_arr[][4])
{
    uint8_t a[4];
    uint8_t b[4];
    uint8_t h;

    for(int col = 0; col < 4; col++)
    {
        for(int i = 0; i < 4; i++)
        {
            a[i] = state_arr[i][col];
            h = (state_arr[i][col] >> 7) & 0x01;
            b[i] = state_arr[i][col] << 1;
            b[i] ^= h * 0x1b;
        }

        state_arr[0][col] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
        state_arr[1][col] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
        state_arr[2][col] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
        state_arr[3][col] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
    }
}

void AES::generate_keys(std::string &key)
{
    uint8_t key_arr[4][4];
    uint32_t key_expanded[44];

    init_round_keys();
    ascii_to_hex(key);
    get_key_arr(key, key_arr);
    expand_key(key_arr, key_expanded);
    get_round_keys(key_expanded);
}

void AES::encrypt(std::string &message)
{
    uint8_t state_arr[4][4];
    
    ascii_to_hex(message);
    get_state_arr(message, state_arr);
    
    add_round_key(state_arr, 0);

    for(int round = 1; round < 10; round++)
    {
        sub_bytes(state_arr);
        shift_rows(state_arr);
        mix_columns(state_arr);
        add_round_key(state_arr, round);
    }

    sub_bytes(state_arr);
    shift_rows(state_arr);
    add_round_key(state_arr, 10);

    bytes_to_hex_str(message, state_arr);
}

void AES::bytes_to_hex_str(std::string &message, uint8_t state_arr[][4])
{
    std::stringstream ss;
    ss << std::setfill('0') << std::hex;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            ss << std::setw(2) << std::hex << unsigned(state_arr[j][i]);
        }
    }

    message = ss.str();
}
