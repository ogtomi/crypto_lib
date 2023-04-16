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

    round_keys = new uint8_t**[nr + 1];
    
    for(int i = 0; i < (nr + 1); i++)
    {
        round_keys[i] = new uint8_t*[4];

        for(int j = 0; j < 4; j++)
        {
            round_keys[i][j] = new uint8_t[4];
        }
    }
}

AES::~AES()
{
    for(int i = 0; i < (nr + 1); i++)
    {
        for(int j = 0; j < 4; j++)
        {
            delete[] round_keys[i][j];
        }

        delete[] round_keys[i];
    }

    delete[] round_keys;
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

void AES::rot_word(uint8_t *byte_arr)
{
    uint8_t temp = byte_arr[0];

    for(int i = 0; i < 4; i++)
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

void AES::add_rcon(uint8_t *byte_arr, int round)
{
    uint8_t rcon = 0x01; 
    
    for(int i = 0; i < (round - 1); i++)
    {
        rcon = (rcon << 1) ^ (((rcon >> 7) & 0x01) * 0x011b);
    }
    
    byte_arr[0] ^= rcon;
}

void AES::expand_key(uint8_t key_arr[][4], uint8_t key_expanded[][4])
{
    uint8_t temp_arr[4];

    for(int i = 0; i < nk; i++)
    {   
        for(int j = 0; j < 4; j++)
        {
            key_expanded[i][j] = key_arr[i][j];
        }
    }

    for(int i = nk; i < (nr + 1) * 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            temp_arr[j] = key_expanded[i - 1][j];
        }
        
        if(i % nk == 0)
        {
            rot_word(temp_arr);
            sub_word(temp_arr);
            add_rcon(temp_arr, (i / nk));
        }
        else if (nk > 6 && i % nk == 4)
        {
            sub_word(temp_arr);
        }
        
        for(int j = 0; j < 4; j++)
        {
            key_expanded[i][j] = key_expanded[i - nk][j] ^ temp_arr[j];
        }
    }
}

void AES::get_round_keys(uint8_t key_expanded[][4])
{
    int k = 0;

    for(int i = 0; i < (nr + 1); i++)
    {
        for(int row = 0; row < 4; row++)
        {
            for(int byte = 0; byte < 4; byte++)
            {
                round_keys[i][row][byte] = key_expanded[k][byte];
            }
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

void AES::sub_bytes(uint8_t state_arr[][4])
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
            b[i] = (state_arr[i][col] << 1) ^ (h * 0x1b);
        }

        state_arr[0][col] = b[0] ^ b[1] ^ a[1] ^ a[2] ^ a[3];
        state_arr[1][col] = a[0] ^ b[1] ^ b[2] ^ a[2] ^ a[3];
        state_arr[2][col] = a[0] ^ a[1] ^ b[2] ^ b[3] ^ a[3];
        state_arr[3][col] = b[0] ^ a[0] ^ a[1] ^ a[2] ^ b[3];
    }
}

void AES::generate_keys(std::string &key)
{
    uint8_t key_arr[nk][4];
    uint8_t key_expanded[(nr + 1) * 4][4];

    get_key_arr(key, key_arr);
    expand_key(key_arr, key_expanded);
    get_round_keys(key_expanded);
}

void AES::inv_sub_bytes(uint8_t state_arr[][4])
{
    uint8_t row_value = 0;
    uint8_t col_value = 0;

    for(int col = 0; col < 4; col++)
    {
        for(int row = 0; row < 4; row++)
        {
            row_value = (state_arr[row][col] >> 4) & 0x0F;
            col_value = state_arr[row][col] & 0x0F;
            state_arr[row][col] = inv_s_box[row_value][col_value];
        }
    }
}

void AES::inv_shift_rows(uint8_t state_arr[][4])
{   
    for(int row = 0; row < 4; row++)
    {
        for(int i = 0; i < row; i++)
        {
            uint8_t temp = state_arr[row][3];

            for(int j = 3; j > 0; j--)
            {
                state_arr[row][j] = state_arr[row][j - 1];
            }

            state_arr[row][0] = temp;
        }
    }
}

void AES::inv_mix_columns(uint8_t state_arr[][4])
{
    uint8_t a[4];
    uint8_t b[4];
    uint8_t c[4];
    uint8_t d[4];
    uint8_t h;

    for(int col = 0; col < 4; col++)
    {
        for(int i = 0; i < 4; i++)
        {
            a[i] = state_arr[i][col];

            h = (a[i] >> 7) ^ 0x01;
            b[i] = (a[i] << 1) ^ (h * 0x1b);

            h = (b[i] >> 7) ^ 0x01;
            c[i] = (b[i] << 1) ^ (h * 0x1b);

            h = (c[i] >> 7) ^ 0x01;
            d[i] = (c[i] << 1) ^ a[i] ^ (h * 0x1b) ;
        }

        state_arr[0][col] = (d[0] ^ c[0] ^ b[0] ^ a[0]) ^ (d[1] ^ b[1]) ^ (d[2] ^ c[2]) ^ d[3];
        state_arr[1][col] = d[0] ^ (d[1] ^ c[1] ^ b[1] ^ a[1]) ^ (d[2] ^ b[2]) ^ (d[3] ^ c[3]);
        state_arr[2][col] = (d[0] ^ c[0]) ^ d[1] ^ (d[2] ^ c[2] ^ b[2] ^ a[2]) ^ (d[3] ^ b[3]);
        state_arr[3][col] = (d[0] ^ b[0]) ^ (d[1] ^ c[1]) ^ d[2] ^ (d[3] ^ c[3] ^ b[3] ^ a[3]);
    }
}

void AES::encrypt(std::string &message)
{
    uint8_t state_arr[4][4];
    
    get_state_arr(message, state_arr);
    add_round_key(state_arr, 0);

    for(int round = 1; round < nr; round++)
    {
        sub_bytes(state_arr);
        shift_rows(state_arr);
        mix_columns(state_arr);
        add_round_key(state_arr, round);
    }

    sub_bytes(state_arr);
    shift_rows(state_arr);
    add_round_key(state_arr, nr);

    bytes_to_hex_str(message, state_arr);
}

void AES::decrypt(std::string &cipher)
{
    uint8_t state_arr[4][4];
    
    get_state_arr(cipher, state_arr);
    add_round_key(state_arr, nr);

    for(int round = (nr - 1); round > 0; round--)
    {
        inv_sub_bytes(state_arr);
        inv_shift_rows(state_arr);
        add_round_key(state_arr, round);
        inv_mix_columns(state_arr);
    }

    inv_sub_bytes(state_arr);
    inv_shift_rows(state_arr);
    add_round_key(state_arr, 0);

    bytes_to_hex_str(cipher, state_arr);
}

void AES::bytes_to_hex_str(std::string &message, uint8_t state_arr[][4])
{
    std::stringstream ss;
    ss << std::setfill('0') << std::hex;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            ss << std::setw(2) << std::hex << (unsigned)state_arr[j][i];
        }
    }

    message = ss.str();
}

void AES::split_message(const std::string &message, std::vector<std::string> &message_vec)
{
    int message_block_len = 32;

    for(size_t i = 0; i < message.size(); i+= message_block_len)
    {
        message_vec.push_back(message.substr(i, message_block_len));
    }
}

void AES::encrypt_ecb(std::string &message)
{
    std::vector<std::string> message_vec;
    split_message(message, message_vec);

    for(size_t i = 0; i < message_vec.size(); i++)
    {
        encrypt(message_vec[i]);
    }

    message = "";

    for(size_t i = 0; i < message_vec.size(); i++)
    {
        message += message_vec[i];
    }
}

void AES::decrypt_ecb(std::string &cipher)
{
    std::vector<std::string> cipher_vec;
    split_message(cipher, cipher_vec);

    for(size_t i = 0; i < cipher_vec.size(); i++)
    {
        decrypt(cipher_vec[i]);
    }

    cipher = "";

    for(size_t i = 0; i < cipher_vec.size(); i++)
    {
        cipher += cipher_vec[i];
    }
}

std::string AES::generate_iv()
{
    return "000102030405060708090a0b0c0d0e0f";
}

void AES::xor_iv(std::string &submessage, const std::string &init_vec)
{
    uint8_t submessage_bin[32];
    uint8_t init_vec_bin[32];
    size_t data_len = sizeof(submessage_bin) / (2 * sizeof(*submessage_bin));

    hexstr_to_uint8t(init_vec, init_vec_bin);
    hexstr_to_uint8t(submessage, submessage_bin);

    for(int i = 0; i < 64; i++)
    {
        submessage_bin[i] ^= init_vec_bin[i];
    }

    uint8t_to_hexstr(submessage, submessage_bin, data_len);
}

void AES::encrypt_cbc(std::string &message)
{
    std::string init_vec = generate_iv();
    std::vector<std::string> message_vec;

    split_message(message, message_vec);

    for(size_t i = 0; i < message_vec.size(); i++)
    {
        xor_iv(message_vec[i], init_vec);
        encrypt(message_vec[i]);
        init_vec = message_vec[i];
    }

    message = "";

    for(size_t i = 0; i < message_vec.size(); i++)
    {
        message += message_vec[i];
    }
}

void AES::decrypt_cbc(std::string &cipher)
{
    std::string init_vec = generate_iv();
    std::vector<std::string> cipher_vec;
    std::string temp_vec{};

    split_message(cipher, cipher_vec);

    for(size_t i = 0; i < cipher_vec.size(); i++)
    {
        if(i > 0)
        {
            init_vec = temp_vec;
        }

        temp_vec = cipher_vec[i];
        decrypt(cipher_vec[i]);
        xor_iv(cipher_vec[i], init_vec);
    }

    cipher = "";

    for(size_t i = 0; i < cipher_vec.size(); i++)
    {
        cipher += cipher_vec[i];
    }
}

void AES::encrypt_cfb(std::string &message)
{
    std::string init_vec = generate_iv();
    std::vector<std::string> message_vec;
    std::string temp_vec{};

    split_message(message, message_vec);

    for(size_t i = 0; i < message_vec.size(); i++)
    {
        if(i == 0)
        {
            temp_vec = init_vec;
        }

        encrypt(temp_vec);
        xor_iv(temp_vec, message_vec[i]);
        message_vec[i] = temp_vec;
    }

    message = "";

    for(size_t i = 0; i < message_vec.size(); i++)
    {
        message += message_vec[i];
    }
}

void AES::decrypt_cfb(std::string &cipher)
{
    std::string init_vec = generate_iv();
    std::vector<std::string> cipher_vec;
    std::string temp_vec{};
    std::string temp_cipher{};

    split_message(cipher, cipher_vec);

    for(size_t i = 0; i < cipher_vec.size(); i++)
    {
        if(i == 0)
        {
            temp_vec = init_vec;
        }

        encrypt(temp_vec);
        temp_cipher = cipher_vec[i];
        xor_iv(cipher_vec[i], temp_vec);
        temp_vec = temp_cipher;
    }

    cipher = "";

    for(size_t i = 0; i < cipher_vec.size(); i++)
    {
        cipher += cipher_vec[i];
    }
}

void AES::encrypt_ofb(std::string &message)
{
    std::string init_vec = generate_iv();
    std::vector<std::string> message_vec;
    std::string temp_vec{};

    split_message(message, message_vec);

    for(size_t i = 0; i < message_vec.size(); i++)
    {
        if(i == 0)
        {
            temp_vec = init_vec;
        }

        encrypt(temp_vec);
        xor_iv(message_vec[i], temp_vec);
    }

    message = "";

    for(size_t i = 0; i < message_vec.size(); i++)
    {
        message += message_vec[i];
    }
}

void AES::decrypt_ofb(std::string &cipher)
{

}

void AES::encrypt(std::string &message, AES_mode mode)
{
    switch(mode)
    {
        case AES_mode::ECB:
            encrypt_ecb(message);
            break;
        
        case AES_mode::CBC:
            encrypt_cbc(message);
            break;

        case AES_mode::CFB:
            encrypt_cfb(message);
            break;

        case AES_mode::OFB:
            encrypt_ofb(message);
            break;

        default:
            break;
    }
}

void AES::decrypt(std::string &cipher, AES_mode mode)
{
    switch(mode)
    {
        case AES_mode::ECB:
            decrypt_ecb(cipher);
            break;
        
        case AES_mode::CBC:
            decrypt_cbc(cipher);
            break;
        
        case AES_mode::CFB:
            decrypt_cfb(cipher);
            break;

        case AES_mode::OFB:
            decrypt_ofb(cipher);
            break;
            
        default:
            break;
    }
}
