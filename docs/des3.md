# Triple DES

Tripple DES is a symmetric key block cipher which applies the [DES](/docs/des.md) algorithm three times to each data block.

## Steps in algorithm

First the key is generated. It consists of three different [DES](/docs/des.md) keys- `k1`, `k2`, `k3`. This means the key has a length of 168bits (3*56 bits).

## Encryption

The process is as follows:

1. Encrypt the plaintext blocks using single [DES](/docs/des.md) with key `k1`
2. Decrypt the output of the previous step using single [DES](/docs/des.md) `k2`
3. Encrypt the output of the previous step using single [DES](/docs/des.md) with key `k3`

## Decryption

Decryption of a ciphertext is a reverse process of encryption.

## Triple DES vs single DES

Triple DES systems are significantly more secure than single DES, but the process of encryption/ decryption is much slower compared to single DES. Triple DES was introduced because it would take an enourmous amount of time and money to change encryption algorithms that were widely adopted and embedded in large security architectures. Thus the change of the manner in which single DES was used.
