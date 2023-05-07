#ifndef _RNG_H_
#define _RNG_H_

#include "../generic_functions/generic_functions.h"
#include <iostream>
#include <string>
#include <openssl/rand.h>
#include <openssl/err.h>

class RNG
{
public:
    std::string generate_iv(uint8_t len);
};

#endif
