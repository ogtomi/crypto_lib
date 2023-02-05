#include <iostream>
#include "rsa/rsa.h"

int main()
{
    int p = 3;
    int q = 5;
    RSA rsa(p, q);

    int message = 8;
    
    int encrypted_message = rsa.encrypt(message);
    int decrypted_message = rsa.decrypt(encrypted_message);

    std::cout << message << std::endl;
    std::cout << encrypted_message << std::endl;
    std::cout << decrypted_message << std::endl;
    return 0;
}
