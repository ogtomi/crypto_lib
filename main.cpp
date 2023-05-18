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
#include "meta/gcm.h"

int main()
{
    std::string key_128 = "000102030405060708090a0b0c0d0e0f";
    std::string key_192 = "000102030405060708090a0b0c0d0e0f1011121314151617";
    std::string key_256 = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
    std::string message = "00112233445566778899aabbccddeeff";
    std::string message_ll = "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff";

    std::string auth_data = "00000000000000000000000000000000";
    std::string auth_tag{};

    AES aes(AES_key_length::AES_128);
    aes.generate_keys(key_128);
    GCM<AES> aes_gcm(aes);

    std::cout << message_ll << std::endl;
    aes_gcm.encrypt(message_ll, auth_data, auth_tag);
    std::cout << message_ll << std::endl;
    aes_gcm.decrypt(message_ll, auth_data, auth_tag);
    std::cout << message_ll << std::endl;

    return 0;
}
