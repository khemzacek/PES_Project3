/* PSEUDORANDOM BYTE PATTERN GENERATOR */
#include "random_bytes.h"

/* PRNG using xorshift algorithm */
uint8_t xorshift(uint8_t rand_byte)
{
	rand_byte ^= (rand_byte << 7);
	rand_byte ^= (rand_byte >> 5);
	rand_byte ^= (rand_byte << 3);
	return rand_byte;
}

/* Creates random byte pattern */
void gen_pattern(uint8_t num_bytes, uint8_t seed, uint8_t* byte_array)
{
	if(seed == 0){
		seed = 1;
		// 0 is an invalid seed for the xorshift algorithm
	}
	
	uint8_t random_byte;
	for(uint8_t i = 0; i < num_bytes; i++){
		random_byte = xorshift(seed);	// run PRNG algorithm
		*byte_array = random_byte;		// write that byte to byte array
		seed = random_byte;				// random number becomes seed for next run
		byte_array++;					// increase pointer to next array index
	}
	// bytes are written into memory byte-by-byte <- keep in mind on little-endian machines
}

uint8_t check_pattern(uint8_t num_bytes, uint8_t seed, uint8_t* byte_array)
{
	if(seed == 0){
			seed = 1;
			// 0 is an invalid seed for the xorshift algorithm
		}

		uint8_t random_byte;
		for(uint8_t i = 0; i < num_bytes; i++){
			random_byte = xorshift(seed);	// run PRNG algorithm
			if(*byte_array != random_byte){
				return 0;		// if generated number != written number, patterns same is FALSE
			}
			seed = random_byte;				// random number becomes seed for next run
			byte_array++;					// increase pointer to next array index
		}
		// checked byte-by-byte <- keep in mind on little-endian machines

		// if reached, all bytes were identical
		return 1;	// patterns same is TRUE
}
