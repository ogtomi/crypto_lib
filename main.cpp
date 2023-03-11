#include <iostream>
#include <string>
#include "rsa/rsa.h"
#include "sha256/sha256.h"
#include "des/des.h"

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

    DES des;
    des.generate_keys(key);
    std::cout << message << std::endl;
    des.encrypt(message);
    std::cout << message << std::endl;
    des.decrypt(message);
    std::cout << message << std::endl;

    return 0;
}
