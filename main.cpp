#include <iostream>
#include "rsa/rsa.h"

int main()
{
    long long int p = 3;
    long long int q = 5;

    RSA rsa(p, q);
    rsa.gen_keys();

    int message = 8;
    
    double encrypted_message = rsa.encrypt(message);
    double decrypted_message = rsa.decrypt(encrypted_message);

    std::cout << "____________________" << std::endl;
    std::cout << "Plain message: " << message << std::endl;
    std::cout << "Encrypted message: " << encrypted_message << std::endl;
    std::cout << "Decrypted message: " << decrypted_message << std::endl;

    return 0;
}
