# CBC

CBC (Cipher-block chaining) is a block cipher mode that trumps the [ECB](/docs/ecb_mode.md) mode hiding away patterns in the plaintext. CBC mode achieves this by XORing the first plaintext block with an initialization vecotr before encrypting it. CBC also involves block chaining as every subsequent block is XORed with the ciphertext of the previous block.

## Encryption formula

$C_i = E_k(B_i \oplus C_{i-1})$

where:<br>
$E_k$ - block encryption algorithm using key $k$<br>
$C_{i-1}$ - cipher corresponding to the $B_{i-1}$

![](/docs/images/CBC_encryption.png)

## Decryption formula

$B_i = D_k(C_i) \oplus (C_{i-1})$

where:<br>
$D_k$ - block decryption algorithm using key $k$

![](/docs/images/CBC_decryption.png)

## Advantages of CBC

The reatest advantage CBC has over [ECB](/docs/ecb_mode.md) mode is that identical blocks do not have the same cipher. This is because the initialization vecotr addds a random factor to each block.

## Disadvantages of CBC mode

Encryption is not tolerant of block loses. This is because blocks depend on their previous blocks for encryption. So, if a block is lost, the encryption of all subsequent blocks will not be possible. This chained behaviour also means that the encryption of blocks needs to be done sequentially, not in parallel. However, these disadvantages do not extend to decryption, which can be done in parallel if all ciphertext blocks are available and can tolerate block losses.
