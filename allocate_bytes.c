/*
 * allocate_bytes.c
 *
 *  Created on: Mar 10, 2020
 *      Author: Katherine
 */
#include "allocate_bytes.h"


uint8_t allocate_bytes(uint8_t num_bytes, uint8_t extra2, uint8_t extra3, uint32_t extra4)
{
	if(num_bytes > MAX_ALLOC_SIZE){
//		PRINTF("Memory allocation size too big. Max size allocated.\n");
		num_bytes = MAX_ALLOC_SIZE;
		return 1;
	}
	allocSize = num_bytes;
	allocStart = malloc(allocSize*sizeof(uint8_t));
	allocEnd = allocStart + allocSize;
	return 0;
}


