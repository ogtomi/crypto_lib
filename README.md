# Crypto library

Library with popular cryptographic algorithms implemented from scratch.

## Algorithms implemented

1. [RSA](docs/rsa.md)
2. [SHA256](docs/sha256.md)
3. [DES](docs/des.md)
    * [Triple DES](docs/des3.md)
4. [AES](docs/aes.md)
    * AES-128
    * AES-192
    * AES-256

### Modes of operation

Implementation for modes of operation involves template metaprogramming. It is a metaprogramming technique in which templates are used by a compiler to generate temporary source code, which is merged by the compiler with the rest of the source code and then compiled.

1. [ECB](docs/ecb_mode.md)
2. [CBC](docs/cbc_mode.md)
3. [OFB](docs/ofb_mode.md)
4. [CFB](docs/cfb_mode.md)
5. [CTR](docs/ctr_mode.md)

### Libraries used
- [OpenSSL](https://www.openssl.org/)
    - generating pseudo-random initialization vector
- [GMP](https://gmplib.org/)
    - Handling big numbers for RSA algorithm

### Compilation
#### Prerequisites
1. Installed `g++` compiler
2. Installed `OpenSSL` library
3. Installed `GMP` library

#### Compile
The project can be compiled using `g++` compiler with the following flags:
1. `OpenSSL` library
    ```console
    -lssl -lcrypto
    ```

2. `GMP` library
    ```console
    -lgmp -lgmpxx
    ```

### Output example

```console
DES in CTR mode
Message: 
00112233445566778899aabbccddeeff
Encrypted message: 
7d26047d03b91842f5ae8cf58b3190ca
Decrypted message: 
00112233445566778899aabbccddeeff

Triple DES in OFB mode
Message: 
00112233445566778899aabbccddeeff
Encrypted message: 
ffed24f4243e5bb95473c046a1c8ee8d
Decrypted message: 
00112233445566778899aabbccddeeff

AES-128 in CBC mode
Message: 
00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff
Encrypted message: 
a686e9470065c013d237932b55db169762c9f3c77668db2bdd3600b07370828d
Decrypted message: 
00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff

SHA-256 input str: 
Testing input for the SHA256. Hash will be produced from this string.
is: 
13db07605a6413446825ed281e73ba132c7e951f67df7ea879754b5463eaee36
```
