#ifndef _GENERIC_FUNCTIONS_H_
#define _GENERIC_FUNCTIONS_H_

#include "../conversion/conversion.h"
#include <string>
#include <sstream>

void xor_iv(std::string &subemssage, const std::string &init_vec, const uint8_t &block_size);
void bytes_to_hex_str(std::string &hex_str, const unsigned char *byte_arr, const int size);

#endif
