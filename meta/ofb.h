#ifndef _OFB_H_
#define _OFB_H_

#include "../conversion/conversion.h"
#include "../random_gen/rng.h"
#include "../generic_functions/generic_functions.h"
#include <string>
#include <vector>

template<typename AlgorithmType>
class OFB
{
private:
    AlgorithmType& alg;
    RNG rng;
    uint8_t iv_len = 16;
    std::string iv;

public:
    OFB(AlgorithmType& alg, const uint8_t &iv_len)
        :alg(alg), iv_len(iv_len)
    {
        iv = rng.generate_iv(iv_len);
    };

    void encrypt(std::string &message, const uint8_t &block_size)
    {
        std::string init_vec = iv;
        std::vector<std::string> message_vec;
        std::string temp_vec{};

        split_message(message, message_vec, block_size * 2);

        for(size_t i = 0; i < message_vec.size(); i++)
        {
            if(i == 0)
            {
                temp_vec = init_vec;
            }

            alg.encrypt(temp_vec);
            xor_iv(message_vec[i], temp_vec, block_size);
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
        std::vector<std::string> cipher_vec;
        std::string temp_vec{};

        split_message(cipher, cipher_vec, block_size * 2);

        for(size_t i = 0; i < cipher_vec.size(); i++)
        {
            if(i == 0)
            {
                temp_vec = init_vec;
            }

            alg.encrypt(temp_vec);
            xor_iv(cipher_vec[i], temp_vec, block_size);
        }

        cipher = "";

        for(size_t i = 0; i < cipher_vec.size(); i++)
        {
            cipher += cipher_vec[i];
        }
    };
};

#endif
