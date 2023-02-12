#ifndef _SHA256_H_
#define _SHA256_H_

#include <string>
#include <bitset>
#include <vector>

class SHA256
{
private:
    const uint8_t byte_size = 8;
    std::bitset<8> m_data[64];
	std::bitset<32> hash_val[8];
    uint64_t m_len;

public:
    SHA256();
    ~SHA256() {};
	std::string get_hash_str(std::string input_str);

private:
    void to_binary(const std::string &str);
    void pad();
	void transform();
    uint64_t get_m_size();

	std::bitset<32> rotate_r(std::bitset<32> w, uint32_t n);
	std::bitset<32> sig0(std::bitset<32> w);
	std::bitset<32> sig1(std::bitset<32> w);
	std::bitset<32> choose(std::bitset<32> e, std::bitset<32> f, std::bitset<32> g);
	std::bitset<32> majority(std::bitset<32> a, std::bitset<32> b, std::bitset<32> c);

	static constexpr std::bitset<32> K[64] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
		0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
		0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
		0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
		0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
		0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
		0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
		0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
		0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};
};

#endif
