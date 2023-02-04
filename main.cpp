#include <iostream>
#include "rsa/rsa.h"

int main()
{
    int p = 3;
    int q = 7;
    RSA rsa(p, q);

    double message = 19;
    
    double encrypted_message = rsa.encrypt(message);
    double decrypted_message = rsa.decrypt(encrypted_message);

    std::cout << message << std::endl;
    std::cout << encrypted_message << std::endl;
    std::cout << decrypted_message << std::endl;
    return 0;
}