#ifndef _RNG_H_
#define _RNG_H_

#include <string>
#include <openssl/rand.h>

class RNG
{
public:
    std::string generate_iv();
};

#endif
