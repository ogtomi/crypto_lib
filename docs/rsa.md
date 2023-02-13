# RSA

RSA is a public-key algorithm for encrypting and signing messages. It uses the receiver's public key to encrypt the data and the receiver's private key to decrypt it.

## Steps in algorithm

### Key generation

1. Set:

    $ e = 65537 $
2. Choose two prime numbers `p` and `q` so that: 

    $ phi(n) = (p-1)(q-1) $ and `e` are coprime
    > NOTE: `phi(n)` and `e` are coprime when the greatest common divisor is 1. To calculate that the euclidean algorithm was used
3. Calculate:

    $ n = pq $

4. Calculate:

    $ ed = 1 (mod phi(n)) $
    > NOTE: `d` is calculated using extended euclidean algorithm
5. Bundle the keys:
- private key = (`d`,`n`)
- public key = (`e`, `n`)

## Encrytpion & Decryption Function

1. Encryption:

    $ ciphertext = plaintext ^ e (mod (n)) $

2. Decryption:

    $ plaintext = ciphertext ^ d (mod (n)) $

## Math algorithms used to calculate values in the RSA algorithm
### Euclidean algorithm
This algorithm is an afficient method for computing the greatest common divisor of two integers - the largest number that divides them both without a remainder.

### Extended euclidean algorithm
This algorithm is an extension to the euclidean algorithm. It computes integers `x` and `y` such that:

$ ax + by = gcd(a, b)$

## Used libraries

### GMP
`The GNU Multiple Precision Arithmetic Library` is a free library for arbitrary precision arithmetic, operating on signed integers, rational numbers, and floating-point numbers. There is no practical limit to the precision except the ones implied by the available memory in the machine GMP runs on.
