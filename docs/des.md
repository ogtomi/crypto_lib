# DES

DES (Data Encryption Standard) is a symmetric key algorithm for data encrption. It is based on the two fundamental attributes of cryptography: substitution and transposition. DES consists of 16 steps, each of which is called a round. Each round performs the steps fo substitution and transposition.

## Steps in algorithm

DES is a block cipher - it operates on plaintext blocks of a given size (64-bits) and returns ciphertext blocks of the same size.

### Subkeys generation

1. Permutation of the original key<br>
To generate subkeys a hexadecimel key `K` is needed. The 63-bit key is permuted according to the `pc_1` table.
    > NOTE: Only 56 bits of the original key appear in the permuted key.

2. Split the key into left and right halves

3. Series of left bit rotations<br>
    With left and right halves previously defined, sixteen operations of left bit rotations are performed. The number of bits to rotate is defined in the `no_shifts` array.

4. Permutation of the result<br>
    The key which is a concatenated pair of the halves obtained in the previous step is permutated according to the `pc_2` table.

### Encoding the data

1. Initial permutation<br>
    Plaintext message is permutated according to the `ip` table.

2. Split the message into left and right halves.

3. Applying `f` function<br>
    This step consists of 16 iterations. It uses `f` function which operates on two blocks of data (data block and a subkey) to produce block of 32-bits.

    $L_n = R_{n-1}$<br>
    $R_n = L_{n-1} + f(R_{n-1}, K_n)$

    where:<br>
    $L_n$ - left message half in the $n$-th iteration<br>
    $R_n$ - right message half in the $n$-th iteration<br>
    $K_n$ - $n$-th subkey<br>

    To calculate `f` first each block is expanded from 32 bits to 48 bits. This is done using `expansion_table`. Next that output is XORed with subkey $K_n$. The next step is to apply `s_boxes` array. To do that 48-bit message is split into eight groups of six bits.

    > NOTE: First bit and last bit represent binary number from 0 to 3 which corresponds to the number of the row in the S-box. The middle 4 bits represent binary number from 0 to 15 which is the number of column.

    The final stage in the calculation of `f` is to do a permutation according to the `p` table.<br>

    That process is repeated for sixteen rounds. In the last round the order of two halves is reversed.

4. Final permutation<br>
    In this step the final permutation is applied according to the table `inv_ip`. Result of that operation is the encrypted message.

## Cracking of the DES

DES algorithm has been found vulnerable to powerful attacks and therefore, the popularity of DES has been found on the decline. It was officially withdrawn in 2005.
