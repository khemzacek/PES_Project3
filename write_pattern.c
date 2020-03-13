/*
 * write_pattern.c
 *
 *  Created on: Mar 10, 2020
 *      Author: Katherine
 */

#include "write_pattern.h"

uint8_t write_pattern(uint8_t num_bytes, uint8_t seed, uint8_t extra3, uint32_t extra4)
{
	if(num_bytes > allocSize){
		num_bytes = allocSize; // will only write pattern to end of allocated region
		//PRINTF("Not enough memory allocated. Writing pattern the size of allocated memory.\n");
		return 1;
	}
	gen_pattern(num_bytes, seed, allocStart);
	//PRINTF("Pattern length %d written to %#x\n", patternSize, allocMem);
	return 0;
}
