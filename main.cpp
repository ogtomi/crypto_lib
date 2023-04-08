#include <iostream>
#include <string>
#include "rsa/rsa.h"
#include "sha256/sha256.h"
#include "des/des.h"
#include "des/des_ecb.h"
#include "des/des_cbc.h"
#include "des3/des3.h"
#include "aes/aes.h"

int main()
{
    std::string key_192 = "8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b";
    std::string key_128 = "2b7e151628aed2a6abf7158809cf4f3c";
    std::string message = "00112233445566778899aabbccddeeff";

    AES aes(AES_key_length::AES_128);
    aes.generate_keys(key_128);
    std::cout << message << std::endl;
    aes.encrypt(message);
    std::cout << message << std::endl;

    return 0;
}
