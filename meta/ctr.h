#ifndef _CTR_H_
#define _CTR_H_

#include "../conversion/conversion.h"
#include "../random_gen/rng.h"
#include "../generic_functions/generic_functions.h"
#include <string>
#include <vector>

template<typename AlgorithmType>
class CTR
{
private:
    AlgorithmType& alg;
    RNG rng;
    uint8_t iv_len = 16;
    std::string iv;

public:
    CTR(AlgorithmType& alg, const uint8_t &iv_len)
        :alg(alg), iv_len(iv_len)
    {
        iv = rng.generate_iv(iv_len);
    };

    void encrypt(std::string &message, const uint8_t &block_size)
    {
        std::string init_vec = iv;
        std::string counter = init_vec;
        uint8_t counter_arr[16];
        std::vector<std::string> message_vec;

        split_message(message, message_vec, block_size * 2);

        int j = 15;

        for(size_t i = 0; i < message_vec.size(); i++)
        {
            if(i > 0)
            {
                init_vec = counter;
            }

            alg.encrypt(init_vec);
            xor_iv(message_vec[i], init_vec, block_size);
            
            hexstr_to_uint8t(counter, counter_arr);
            counter_arr[j]++;

            if(counter_arr[j] == 0xFF)
            {
                j--;
            }
            uint8t_to_hexstr(counter, counter_arr, block_size);
        }

        message = "";

        for(size_t i = 0; i < message_vec.size(); i++)
        {
            message += message_vec[i];
        }
    };

    void decrypt(std::string &cipher, const uint8_t &block_size)
    {
        std::string init_vec = iv;
        std::string counter = init_vec;
        uint8_t counter_arr[block_size];
        std::vector<std::string> cipher_vec;

        split_message(cipher, cipher_vec, block_size * 2);

        int j = 15;

        for(size_t i = 0; i < cipher_vec.size(); i++)
        {
            if(i > 0)
            {
                init_vec = counter;
            }

            alg.encrypt(init_vec);
            xor_iv(cipher_vec[i], init_vec, block_size);

            hexstr_to_uint8t(counter, counter_arr);
            counter_arr[j]++;

            if(counter_arr[j] == 0xFF)
            {
                j--;
            }
            uint8t_to_hexstr(counter, counter_arr, block_size);
        }

        cipher = "";

        for(size_t i = 0; i < cipher_vec.size(); i++)
        {
            cipher += cipher_vec[i];
        }
    };
};

#endif
