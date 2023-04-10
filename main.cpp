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
    std::string key_128 = "000102030405060708090a0b0c0d0e0f";
    std::string key_192 = "000102030405060708090a0b0c0d0e0f1011121314151617";
    std::string key_256 = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
    std::string message = "00112233445566778899aabbccddeeff";

    AES aes(AES_key_length::AES_256);
    aes.generate_keys(key_256);
    std::cout << message << std::endl;
    aes.encrypt(message);
    std::cout << message << std::endl;
    aes.decrypt(message);
    std::cout << message << std::endl;

    return 0;
}
