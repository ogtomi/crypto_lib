#ifndef _ECB_H_
#define _ECB_H_

#include "../conversion/conversion.h"
#include <string>
#include <vector>

template<typename AlgorithmType>
class ECB
{
private:
    AlgorithmType& alg;

public:
    ECB(AlgorithmType& alg)
        :alg(alg)
    {
    };

    void encrypt(std::string &message)
    {
        std::vector<std::string> message_vec;
        split_message(message, message_vec);

        for(size_t i = 0; i < message_vec.size(); i++)
        {
            alg.encrypt(message_vec[i]);
        }

        message = "";

        for(size_t i = 0; i < message_vec.size(); i++)
        {
            message += message_vec[i];
        }   
    };

    void decrypt(std::string &cipher)
    {
        std::vector<std::string> cipher_vec;
        split_message(cipher, cipher_vec);

        for(size_t i = 0; i < cipher_vec.size(); i++)
        {
            alg.decrypt(cipher_vec[i]);
        }

        cipher = "";

        for(size_t i = 0; i < cipher_vec.size(); i++)
        {
            cipher += cipher_vec[i];
        }
    };
};

#endif
