# OFB

OFB (Output Feedback Mode) is an operating mode in which block ciphers can be operated. In this mode the output of the cipher is XORed with the plaintext to form the ciphertext. The output of the block cipher is fed back to its input, resulting in continuous stream of encrypted blocks. Similar to the [CBC](/docs/cbc_mode.md) mode, the initialization vector is to be seen as the start value and is independent of the selected key.

## Encryption formula

![](/docs/images/OFB_encryption.png)

## Decryption formula

![](/docs/images/OFB_decryption.png)

## Advantages of OFB mode

One of the advantages is that the bit sequence with which plaintext data is XORed can be calculated in advance. Furthermore, as with all stream ciphers, OFB has the advantage that during decryption, transmission errors in the ciphertext only affect the corresponding bit position in the decrypted plaintext and the error is not propagated in the plaintext.

## Disadvantages of OFB mode

A disadvantage of OFB is the time-consuming synchronization of the block ciphers between transmitter and receiver, since OFB, in contrast to [CFB](/docs/cfb_mode.md) is fundamentally not self-synchronizing.
