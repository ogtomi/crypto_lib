#include "../conversion/conversion.h"
#include "../random_gen/rng.h"
#include "../generic_functions/generic_functions.h"
#include <string>
#include <vector>

template<typename AlgorithmType>
class GCM
{
private:
    AlgorithmType& alg;
    RNG rng;
    uint8_t iv_len = 16;
    std::string iv;

public:
    GCM(AlgorithmType& alg)
        :alg(alg)
    {
        iv = rng.generate_iv(iv_len);
    };

    void encrypt(std::string &message)
    {

    };

    void decrypt(std::string &cipher)
    {

    };
};
