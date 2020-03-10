/*
 * random_bytes.h
 *
 *  Created on: Mar 9, 2020
 *      Author: Katherine
 */

#ifndef RANDOM_BYTES_H_
#define RANDOM_BYTES_H_

#include <stdio.h>
#include <stdint.h>

/* Pseudorandom Number Generator using xorshift algorithm
 * Accepts a seed value and returns the next in a psuedorandom number series.
 * Creates pseudorandom number from seed by performing xor on seed and a
 * shifted version of the seed (several times with different shifts).
 *
 * Referenced:
 * https://en.wikipedia.org/wiki/Xorshift
 * http://www.fractalforums.com/programming/8-bit-random-(unsigned)/
*/
uint8_t xorshift(uint8_t rand_byte);

/* Creates random byte pattern
 * Accepts a number of bytes, a seed value, and a pointer to a byte array to store
 * the output of the function.
 * Implements xorshift algorithm to write a random byte pattern of specified length into
 * specified memory location. Will return the same pattern each time it is run with the
 * same starting seed value.
*/
void gen_pattern(uint8_t num_bytes, uint8_t seed, uint8_t* byte_array);

/* Checks random byte pattern against written memory
 * Accepts number of bytes to check, a seed value for random number generation, and a
 * pointer to the beginning of the memory to be checked.
 * Generates pseudorandom bytes, which are determined by the seed an n in the same manner
 * as gen_pattern. As each byte is generated, it is checked against the corresponding byte
 * in the memory region indicated. If one byte is found not to match, the function breaks
 * and returns FALSE (0). If all bytes are found to be identical after checking num_bytes
 * bytes, the function returns TRUE (1).
 */
uint8_t check_pattern(uint8_t num_bytes, uint8_t seed, uint8_t* byte_array);


#endif /* RANDOM_BYTES_H_ */
