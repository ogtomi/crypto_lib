#include <iostream>
#include <string>
#include "sha256/sha256.h"
#include "des/des.h"
#include "des/des_ecb.h"
#include "des/des_cbc.h"
#include "des3/des3.h"
#include "aes/aes.h"
#include "meta/ecb.h"
#include "meta/cbc.h"
#include "meta/cfb.h"
#include "meta/ofb.h"
#include "meta/ctr.h"

int main()
{
    std::string key_128 = "000102030405060708090a0b0c0d0e0f";
    std::string key_192 = "000102030405060708090a0b0c0d0e0f1011121314151617";
    std::string key_256 = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
    std::string message = "00112233445566778899aabbccddeeff";
    std::string message_ll = "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff";

    AES aes(AES_key_length::AES_128);
    aes.generate_keys(key_128);
    CBC<AES> aes_cbc(aes);
    
    std::cout << "META" << std::endl;
    std::cout << message_ll << std::endl;
    aes_cbc.encrypt(message_ll);
    std::cout << message_ll << std::endl;
    aes_cbc.decrypt(message_ll);
    std::cout << message_ll << std::endl;

    return 0;
}
