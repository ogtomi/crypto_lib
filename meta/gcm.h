#include "../conversion/conversion.h"
#include "../random_gen/rng.h"
#include "../generic_functions/generic_functions.h"
#include <string>
#include <vector>

template<typename AlgorithmType>
class GCM
{
private:
    AlgorithmType& alg;
    RNG rng;
    uint8_t iv_len = 16;
    std::string iv;

public:
    GCM(AlgorithmType& alg)
        :alg(alg)
    {
        iv = rng.generate_iv(iv_len);
    };

    void encrypt(std::string &message, std::string auth_data, std::string &auth_tag)
    {
        std::string init_vec = iv;
        std::string counter = init_vec;
        uint8_t counter_arr[16];
        std::vector<std::string> message_vec;
        std::string message_len = std::to_string(message.size() * 8);

        split_message(message, message_vec);

        int j = 15;
        
        hexstr_to_uint8t(counter, counter_arr);
        if(counter_arr[j] == 0xFF)
        {
            j--;
        }
        counter_arr[j]++;
        uint8t_to_hexstr(counter, counter_arr, 16);

        for(size_t i = 0; i < message_vec.size(); i++)
        {
            if(i > 0)
            {
                init_vec = counter;
            }

            alg.encrypt(init_vec);
            xor_iv(message_vec[i], init_vec);
            xor_iv(auth_data, message_vec[i]);
            gf_multiplication(auth_data, iv);

            hexstr_to_uint8t(counter, counter_arr);
            if(counter_arr[j] == 0xFF)
            {
                j--;
            }
            counter_arr[j]++;
            uint8t_to_hexstr(counter, counter_arr, 16);

            for(size_t i = 0; i < message_vec.size(); i++)
            {
                message += message_vec[i];
            }
        }

        xor_iv(auth_data, message_len);

        auth_tag = iv;
        alg.encrypt(auth_tag);
        xor_iv(auth_tag, auth_data);

        message = "";

        for(size_t i = 0; i < message_vec.size(); i++)
        {
            message += message_vec[i];
        }
    };

    void decrypt(std::string &cipher, std::string auth_data, const std::string &auth_tag)
    {
        std::string init_vec = iv;
        std::string counter = init_vec;
        std::string auth_iv = iv;
        uint8_t counter_arr[16];
        std::vector<std::string> cipher_vec;
        std::string cipher_len = std::to_string(cipher.size() * 8);
        
        split_message(cipher, cipher_vec);

        int j = 15;

        hexstr_to_uint8t(counter, counter_arr);
        if(counter_arr[j] == 0xFF)
        {
            j--;
        }
        counter_arr[j]++;
        uint8t_to_hexstr(counter, counter_arr, 16);

        for(size_t i = 0; i < cipher_vec.size(); i++)
        {
            if(i > 0)
            {
                init_vec = counter;
            }

            alg.encrypt(init_vec);
            xor_iv(cipher_vec[i], init_vec);
            xor_iv(auth_data, cipher_vec[i]);
            gf_multiplication(auth_data, iv);

            hexstr_to_uint8t(counter, counter_arr);
            if(counter_arr[j] == 0xFF)
            {
                j--;
            }
            counter_arr[j]++;
            uint8t_to_hexstr(counter, counter_arr, 16);
        }

        xor_iv(auth_data, cipher_len);

        alg.encrypt(auth_iv);
        xor_iv(auth_iv, auth_data);

        cipher = "";

        for(size_t i = 0; i < cipher_vec.size(); i++)
        {
            cipher += cipher_vec[i];
        }

        std::cout << auth_iv << std::endl;
        std::cout << auth_tag << std::endl;
    };

    void gf_multiplication(std::string &auth_data, const std::string &hash_key)
    {
        uint8_t auth_data_bin[16];
        uint64_t auth_data_bin_expanded[2];
        uint8_t hash_key_bin[16];
        uint64_t hash_key_bin_expanded[2];

        size_t auth_data_len = sizeof(auth_data_bin) / (2 * sizeof(*auth_data_bin));

        hexstr_to_uint8t(hash_key, hash_key_bin);
        hexstr_to_uint8t(auth_data, auth_data_bin);
        uint8t_to_uint64t_arr(hash_key_bin, hash_key_bin_expanded, 2);

        uint8t_to_hexstr(auth_data, auth_data_bin, auth_data_len);
    }
    
    void uint8t_to_uint64t_arr(uint8_t *uint8t_arr, uint64_t *uint64t_arr, const size_t &uint64t_arr_size)
    {
        int j = 0;

        for(size_t i = 0; i < uint64t_arr_size; i++)
        {  
            uint64t_arr[i] = (((uint64_t)uint8t_arr[j] << 56) & 0xFF00000000000000) |
                             (((uint64_t)uint8t_arr[j + 1] << 48) & 0x00FF000000000000) | 
                             (((uint64_t)uint8t_arr[j + 2] << 40) & 0x0000FF0000000000) | 
                             (((uint64_t)uint8t_arr[j + 3] << 32) & 0x000000FF00000000) |
                             (((uint64_t)uint8t_arr[j + 4] << 24) & 0x00000000FF000000) | 
                             (((uint64_t)uint8t_arr[j + 5] << 16) & 0x0000000000FF0000) | 
                             (((uint64_t)uint8t_arr[j + 6] << 8) & 0x000000000000FF00) | 
                             (((uint64_t)uint8t_arr[j + 7]) & 0x00000000000000FF);

            j += 8;
        }
    }
};
