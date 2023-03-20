#include <iostream>
#include <string>
#include "rsa/rsa.h"
#include "sha256/sha256.h"
#include "des/des.h"
#include "des/des_ecb.h"
#include "des/des_cbc.h"
#include "des3/des3.h"

int main()
{
    /*RSA rsa;
    rsa.gen_keys();

    mpz_class message = 956;
    mpz_class encrypted_message;
    mpz_class decrypted_message;

    rsa.encrypt(encrypted_message, message);
    rsa.decrypt(decrypted_message, encrypted_message);

    std::cout << "____________________" << std::endl;
    std::cout << "Plain message: " << message << std::endl;
    std::cout << "Encrypted message: " << encrypted_message << std::endl;
    std::cout << "Decrypted message: " << decrypted_message << std::endl;

    SHA256 sha256;
    std::string hash_str = sha256.digest("Just trying to make the message longer. Adding some stuff");
    std::cout << hash_str << std::endl; 
    */
    std::string message = "0123456789abcdef";
    std::string key = "133457799bbcdff1";
    
    /*
    DES des;
    des.generate_keys(key);
    std::cout << message << std::endl;
    des.encrypt(message);
    std::cout << message << std::endl;
    des.decrypt(message);
    std::cout << message << std::endl;*/

    /*std::string key_1 = "133457799bbcdff1";
    std::string key_2 = "100457722bbcddd1";
    std::string key_3 = "023457700bbdcff0";
    std::string keys[] = {key_1, key_2, key_3};

    DES3 des3;
    des3.generate_keys(keys);

    std::cout << message << std::endl;
    des3.encrypt(message);
    std::cout << message << std::endl;
    des3.decrypt(message);
    std::cout << message << std::endl;*/

    std::string message_test = "0123456789abcdef1123456789abcdef2123456789abcdef";
    std::string init_vec = "4bfa4d2304bb81fb";
    /*DES_ECB des_ecb;
    des_ecb.generate_keys(key);

    std::cout << message_test << std::endl;
    des_ecb.encrypt(message_test);
    std::cout << message_test << std::endl;
    des_ecb.decrypt(message_test);
    std::cout << message_test << std::endl;*/

    DES_CBC des_cbc;
    des_cbc.generate_keys(key);

    std::cout << message_test << std::endl;
    des_cbc.encrypt(message_test, init_vec);
    std::cout << message_test << std::endl;
    des_cbc.decrypt(message_test, init_vec);
    std::cout << message_test << std::endl;
    
    return 0;
}
