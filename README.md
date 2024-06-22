# ZPK
A simple implementation of the ZPK algorithm using Schnorr's protocol.

## Description
In this program, I used the Schnorr protocol (or Schnorr signature) which is a zero-knowledge proof system used for demonstrating knowledge of a secret value without revealing the secret itself. It involves three main steps:

### Commitment: 
The prover generates a random value, computes a commitment, and sends it to the verifier.
### Challenge: 
The verifier sends a random challenge to the prover.
### Response: 
The prover computes a response using the challenge and the secret and sends it to the verifier.

The verifier checks the response to confirm the prover knows the secret without actually revealing it.

The Schnorr signature algorithm is a digital scheme known for its simplicity. The algorithm utilizes the intractability (the difficulty to influence or control the result) of the discrete logarithmic function, which in computer science and mathematics is a very difficult problem. While it belongs in the NP compexity classification because given the exponent you can check whether the response is easy in polynomial time; it is unknown whether it is NP-complete because there is no known polynomial reduction from NP to NP-complete from any NP problem to the discrete logarithm problem. It is widely believed to be hard and that is why it is used a lot in security and cryptography (e.g., Diffie-Hellman key exchange, EIGamal encryption, etc.).

## Overview of the Schnorr signature algorithm
While the simple ZPK implementation (simple_ZPK.cpp) showcases an easy implementation of the algorithm, the correct way to do this would be to have three different files and split the functionality accordingly. Here is a brief explanation and overview of the whole algorithm.

The Schnorr signature algorithm involves three main processes:
1. **Key Generation**
2. **Signing**
3. **Verification**

### Key Generation
1. Select a large prime *p* and a generator *g* of the multiplicative group of integers modulo *p*. 
2. Choose a private key *x* randomly from the set *{1, 2, ..., p-2}*.
3. Calculate the public key *y = g<sup>x</sup> mod p*.

### Signing
1. Select a random integer *k* from the set *{1, 2, ..., p-2}.
2. Calculate *r = g<sup>k</sup> \mod p*.
3. Calculate the hash *e = **H**(m || r)*, where *m* is the message to be signed, *r* is the value from step 2, and *H* is a cryptographic hash function.
4. Calculate the signature *s = (k - xe) mod(p-1)*.

The signature for the message *m* is the pair *(r, s)*.

### Verification
1. Calculate the hash *e = **H**(m || r)*.
2. Calculate *v<sub>1</sub> = g<sup>s</sup> . y<sup>e</sup> mod p*.
3. Check if *$v<sub>1</sub> \equiv r mod p$*.

The signature *(r, s)* is valid if and only if *$v_1 \equiv r mod p$*.

## Complexity
The theoretical three part program, as well as the simple one posted in the repo, given that *n* is the cardinal number of the digits of the prime number *p*, would be *O(n<sup>3</sup>)*, while its space Complexity is *O(n)*. It is worth noting that each of the programs by itself has this complexity, both for time and space, and combined is *3* times that, i.e., *3O(n<sup>3</sup>)* and *3O(n)*, but due to the nature of the calculation of the complexity, number *3* as a constant, is eliminated.

## Notes
For more on Schnorr's digital signature algorithm and the discrete logarithm problem, you can use the following links:<br>  
[Schnorr signature](https://en.wikipedia.org/wiki/Schnorr_signature)<br>  
[Discrete logarithm problem](https://en.wikipedia.org/wiki/Discrete_logarithm)

## License
This project is licensed under the MIT license.



