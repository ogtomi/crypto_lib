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

public:
    OFB(AlgorithmType& alg)
        :alg(alg)
    {
    };

    void encrypt(std::string &message)
    {
        std::string init_vec = rng.generate_iv();
        std::vector<std::string> message_vec;
        std::string temp_vec{};

        split_message(message, message_vec);

        for(size_t i = 0; i < message_vec.size(); i++)
        {
            if(i == 0)
            {
                temp_vec = init_vec;
            }

            alg.encrypt(temp_vec);
            xor_iv(message_vec[i], temp_vec);
        }

        message = "";

        for(size_t i = 0; i < message_vec.size(); i++)
        {
            message += message_vec[i];
        }
    };

    void decrypt(std::string &cipher)
    {
        std::string init_vec = rng.generate_iv();
        std::vector<std::string> cipher_vec;
        std::string temp_vec{};

        split_message(cipher, cipher_vec);

        for(size_t i = 0; i < cipher_vec.size(); i++)
        {
            if(i == 0)
            {
                temp_vec = init_vec;
            }

            alg.encrypt(temp_vec);
            xor_iv(cipher_vec[i], temp_vec);
        }

        cipher = "";

        for(size_t i = 0; i < cipher_vec.size(); i++)
        {
            cipher += cipher_vec[i];
        }
    };
};

#endif
