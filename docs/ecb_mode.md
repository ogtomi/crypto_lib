# ECB

ECB (Electronic code book) is a simple mode of operation with a block cipher that is mostly used with symmetric key encryption. It is a straightforward way of processing a series of sequentially listed message blocks.

## Formula

The input plaintext is broken into numerous blocks. The blocks are individually encrypted using the encryption key. As a result, each encrypted block can also be decrypted individually. ECB can support a separate encryption key for each block type.<br>

In ECB, each block of plaintext has a defined corresponding ciphertext value and vice versa. So, identical plaintexts with identical keys always encrypt to identical ciphertexts. This means that if plaintext blocks are encrypted multiple times under the same key, the output ciphertext blocks will always be the same. In other words, the same plaintext value will always result in the same ciphertext value.

## Encryption

![](/docs/images/Ecb_encryption.png)

## Decryption

![](/docs/images/Ecb_decryption.png)
