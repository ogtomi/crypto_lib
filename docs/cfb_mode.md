# CFB

CFB (Cipher Feedback Mode) is an operating mode in which block ciphers are operated as stream ciphers. In this mode the output of the block cipher is combined with the plaintext XOR to form the ciphertext. The output ciphertext data flows as input to the next block for encryption. This results in self-synchronization as a major difference to the [OFB](/docs/ofb_mode.md) mode. This means that the recipent does not have to know the exact content of the block cipher during decryption.

## Encryption formula

![](/docs/images/CFB_encryption.png)

## Decyrption formula

![](/docs/images/CFB_decryption.png)

## Advantages of CFB mode

The main advantage of the CFB mode is that, since it doesn't use decryption algorithm, it is generally faster than the [CBC](/docs/cbc_mode.md). CFB encryption is also non-deterministic, which means it does not reveal any patterns the plaintext may have.

## Disadvantages of CFB mode

The disadvantages of CFB are identical to those of the [CBC](/docs/cbc_mode.md). The encryption cannot tolerate block losses, nor can multiple blocks be encrypted in parallel. However, decryption is both loss-tolerant and can be parallelized.
