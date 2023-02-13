# RSA

RSA is a public-key algorithm for encrypting and signing messages. It uses the receiver's public key to encrypt the data and the receiver's private key to decrypt it.

## Steps in algorithm

### Key generation

1. Set `e = 65537`
2. Choose two prime numbers `p` and `q` so that `phi(n) = (p-1)(q-1)` and `e` are coprime
3. Calculate `n = pq`
4. Calculate `ed = 1 (mod phi(n))`
    > NOTE: `d` is calculated using extended euclidean algorithm
5. Bundle the keys:
- private key = (`d`,`n`)
- public key = (`e`, `n`)
