# X25519 for ARM AArch64

This implements highly optimimzed assembler versions of X25519 for AArch64. It's especially optimized for Cortex-A53 but works fast on other AArch64 processors as well. It utilizes the NEON floating point engine to archieve the high performance.

## X25519
X25519 is an Elliptic curve version of the Diffie-Hellman protocol, using Curve25519 as the elliptic curve, as introduced in https://cr.yp.to/ecdh.html.

### API
```
void X25519_calc_public_key(uint8_t output_public_key[32], const uint8_t input_secret_key[32]);
void X25519_calc_shared_secret(uint8_t output_shared_secret[32], const uint8_t my_secret_key[32], const uint8_t their_public_key[32]);
```

* To use, first generate a 32 byte random value using a Cryptographically Secure Number Generator (specifically do NOT use `rand()` from the C library), which gives your secret key.
* Feed that secret key into `X25519_calc_public_key` which will give you the corresponding public key you then transfer to the other part. The other part does the same.
* When you get the other part's public key, feed that into `X25519_calc_shared_secret` together with your private key which will give you the shared secret. Rather than using this shared secret directly, it should be hashed (for example with SHA-256) on both sides before use. For further usage instructions see the official web site.

Note that this library automatically "clamps" the secret key for you (i.e. sets all the three lowest bits to 0 and the two highest to 0 and 1), compared to some other implementations.

### Setup
* The header file `X25519-AArch64.h` should be included when using the API from C/C++.
* When compiling with GCC, `X25519-AArch64.s` must be added to the project as a compilation unit. The compiler switch `-march=armv8-a` or similar might be needed depending on target architecture.

### Example
An example can be seen in `linux_example.c` that uses `/dev/urandom` to get random data. It can be compiled on for example Raspberry Pi 3 running Debian (64-bit version) with:
```
gcc linux_example.c X25519-AArch64.s -o linux_example
```

### Performance
The library uses only 5840 bytes of code space in compiled form, uses 416 bytes of stack and runs one scalar multiplication in ~145k cycles on Cortex-A53, which is speed record as far as I know. On Amazon AWS's A1 CPU (Cortex-A72), the implementation uses ~150k cycles (at 2.3 GHz).

### Code
The code is written in GCC's assembler syntax.

### Security
The implementation runs in constant time and uses a constant memory access pattern, regardless of the private key in order to protect against side channel attacks.

### Copying
The code is released under CC0.
