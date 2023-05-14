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
};
