#include <string>
#include <iomanip>
#include <sstream>

void hexstr_to_uint8t(const std::string &hex_str, uint8_t *data);
void uint8t_to_hexstr(std::string &hex_str, uint8_t *data, const size_t data_len);
