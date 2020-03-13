/*
 * invert_block.c
 *
 *  Created on: Mar 10, 2020
 *      Author: Katherine
 */

#include "invert_block.h"

uint8_t invert_block(uint8_t offset, uint8_t num_bytes, uint8_t extra3, uint32_t extra4)
{
	// check bounds
	if(offset > allocSize){
		return 1; // Out of Range
	}else if((offset + num_bytes) > allocSize){
		num_bytes = allocSize - offset;	// start at addr given by offset, invert to end of allocated mem
	}
	// start inverting byte-by-byte
	uint8_t *invert_index;
	invert_index = allocStart + offset;
	for(uint8_t i = 0; i < num_bytes; i++){
		*invert_index ^= 0xFF;
		invert_index++;
	}
	//PRINTF("%d bytes inverted at %#x\n", invertSize, (allocMem + offset));
	return 0;
}
