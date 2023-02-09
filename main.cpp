#include <iostream>
#include "rsa/rsa.h"

int main()
{
    RSA rsa;
    rsa.gen_keys();

    mpz_class message = 120;
    mpz_class encrypted_message;
    mpz_class decrypted_message;

    rsa.encrypt(encrypted_message, message);
    rsa.decrypt(decrypted_message, encrypted_message);

    std::cout << "____________________" << std::endl;
    std::cout << "Plain message: " << message << std::endl;
    std::cout << "Encrypted message: " << encrypted_message << std::endl;
    std::cout << "Decrypted message: " << decrypted_message << std::endl;

    return 0;
}
