# CTR

CTR (Counter Mode) is a mode of operation for a block encryption method. The special feature of counter mode compared to other modes of operation is the fact that the initialization vector here consists of a random number (nonce) to be selected for each ciphertext combined with a counter that is incremented with each additional block.

## Encryption formula

![](/docs/images/CTR_encryption.png)

## Decryption formula

![](/docs/images/CTR_decryption.png)

## Advantages of CTR mode

Since blocks are independent of one another with the CTR mode, once the pad vectors have been generated, both encryption and decryption of blocks can be parallelly done. The lack of interdependancy also means that the CTR mode is tolerant to a loss in blocks. The CTR mode is considered to be very secure and efficient for most purposes.

## Disadvantages of CTR mode

The serious disadvantage of CTR mode is that it requires a synchronous counter at sender and receiver. Loss of synchronization leads to incorrect recovery of plaintext.
