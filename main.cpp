#include <iostream>
#include <string>
#include "des/des.h"
#include "des3/des3.h"
#include "aes/aes.h"
#include "meta/ecb.h"
#include "meta/cbc.h"
#include "meta/cfb.h"
#include "meta/ofb.h"
#include "meta/ctr.h"

int main()
{
    // DES & DES3 keys
    std::string key_64 = "0001020304050607";
    std::string key_64_2 = "0011223344556677";
    std::string key_64_3 = "0021324354657687";
    std::string key_arr[3] = {key_64, key_64_2, key_64_3};

    // AES KEYS
    std::string key_128 = "000102030405060708090a0b0c0d0e0f";
    std::string key_192 = "000102030405060708090a0b0c0d0e0f1011121314151617";
    std::string key_256 = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";

    // MESSAGES
    std::string message = "00112233445566778899aabbccddeeff";
    std::string message_ll = "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff";
    
    DES des;
    des.generate_keys(key_64);
    CTR<DES> ctr_des(des, 8);

    std::cout << "\nDES in Counter mode" << std::endl;
    std::cout << message << std::endl;
    ctr_des.encrypt(message, 8);
    std::cout << message << std::endl;
    ctr_des.decrypt(message, 8);
    std::cout << message << std::endl;

    DES3 des3;
    des3.generate_keys(key_arr);
    OFB<DES3> ofb_des3(des3, 8);

    std::cout << "\nTriple DES in OFB mode" << std::endl;
    std::cout << message << std::endl;
    ofb_des3.encrypt(message, 8);
    std::cout << message << std::endl;
    ofb_des3.decrypt(message, 8);
    std::cout << message << std::endl;
    
    AES aes(AES_key_length::AES_128);
    aes.generate_keys(key_128);
    CBC<AES> aes_ecb(aes, 16);

    std::cout << "\nAES-128 in CBC mode" << std::endl;
    std::cout << message_ll << std::endl;
    aes_ecb.encrypt(message_ll, 16);
    std::cout << message_ll << std::endl;
    aes_ecb.decrypt(message_ll, 16);
    std::cout << message_ll << std::endl;

    return 0;
}
