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
