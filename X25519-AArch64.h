/* X25519-AArch64 by Emil Lenngren (2018)
 *
 * To the extent possible under law, the person who associated CC0 with
 * X25519-AArch64 has waived all copyright and related or neighboring rights
 * to X25519-AArch64.
 *
 * You should have received a copy of the CC0 legalcode along with this
 * work.  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

/*
 * This is an AArch64 implementation of X25519.
 * It follows the reference implementation where the representation of
 * a field element [0..2^255-19) is represented by a 256-bit little endian integer,
 * reduced modulo 2^256-38, and may possibly be in the range [2^256-38..2^256).
 * The scalar is a 256-bit integer where certain bits are hardcoded per specification.
 *
 * The implementation runs in constant time (~145k cycles on Cortex-A53),
 * and no conditional branches or memory access pattern depend on secret data.
 */

#ifndef X25519_AARCH64_H
#define X25519_AARCH64_H

// Assembler function
void x25519_scalarmult(unsigned char result[32], const unsigned char scalar[32], const unsigned char point[32]);

// User macros
#define X25519_calc_public_key(output_public_key, input_secret_key) do { \
    static const unsigned char basepoint[32] = {9}; \
    x25519_scalarmult(output_public_key, input_secret_key, basepoint); \
} while(0)

#define X25519_calc_shared_secret(output_shared_secret, my_secret_key, their_public_key) \
x25519_scalarmult(output_shared_secret, my_secret_key, their_public_key)

#endif
