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

    void encrypt(std::string &message, std::string &auth_tag)
    {
        std::string init_vec = iv;
        std::string counter = init_vec;
        std::string iv_auth = iv;
        uint8_t counter_arr[16];
        std::vector<std::string> message_vec;
        std::string message_len = std::to_string(message.size());

        alg.encrypt(auth_tag);

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
            xor_iv(auth_tag, message_vec[i]);

            hexstr_to_uint8t(counter, counter_arr);
            counter_arr[j]++;

            if(counter_arr[j] == 0xFF)
            {
                j--;
            }
            uint8t_to_hexstr(counter, counter_arr, 16);

            for(size_t i = 0; i < message_vec.size(); i++)
            {
                message += message_vec[i];
            }
        }

        
        xor_iv(auth_tag, message_len);
        alg.encrypt(iv_auth);
        xor_iv(auth_tag, iv_auth);

        message = "";

        for(size_t i = 0; i < message_vec.size(); i++)
        {
            message += message_vec[i];
        }
    };

    void decrypt(std::string &cipher)
    {

    };
};
