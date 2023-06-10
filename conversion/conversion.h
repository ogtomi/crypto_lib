#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

void hexstr_to_uint8t(const std::string &hex_str, uint8_t *data);
void uint8t_to_hexstr(std::string &hex_str, uint8_t *data, const size_t data_len);
void ascii_to_hex(std::string &ascii_str);
void split_message(const std::string &message, std::vector<std::string> &message_vec, const int &block_size);
