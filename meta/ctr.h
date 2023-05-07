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
    CTR(AlgorithmType& alg)
        :alg(alg)
    {
        iv = rng.generate_iv(iv_len);
    };

    void encrypt(std::string &message)
    {
        std::string init_vec = iv;
        std::string counter = init_vec;
        uint8_t counter_arr[16];
        std::vector<std::string> message_vec;

        split_message(message, message_vec);

        int j = 15;

        for(size_t i = 0; i < message_vec.size(); i++)
        {
            if(i > 0)
            {
                init_vec = counter;
            }

            alg.encrypt(init_vec);
            xor_iv(message_vec[i], init_vec);
            
            hexstr_to_uint8t(counter, counter_arr);
            counter_arr[j]++;

            if(counter_arr[j] == 0xFF)
            {
                j--;
            }
            uint8t_to_hexstr(counter, counter_arr, 16);
        }

        message = "";

        for(size_t i = 0; i < message_vec.size(); i++)
        {
            message += message_vec[i];
        }
    };

    void decrypt(std::string &cipher)
    {
        std::string init_vec = iv;
        std::string counter = init_vec;
        uint8_t counter_arr[16];
        std::vector<std::string> cipher_vec;

        split_message(cipher, cipher_vec);

        int j = 15;

        for(size_t i = 0; i < cipher_vec.size(); i++)
        {
            if(i > 0)
            {
                init_vec = counter;
            }

            alg.encrypt(init_vec);
            xor_iv(cipher_vec[i], init_vec);

            hexstr_to_uint8t(counter, counter_arr);
            counter_arr[j]++;

            if(counter_arr[j] == 0xFF)
            {
                j--;
            }
            uint8t_to_hexstr(counter, counter_arr, 16);
        }

        cipher = "";

        for(size_t i = 0; i < cipher_vec.size(); i++)
        {
            cipher += cipher_vec[i];
        }
    };
};

#endif
