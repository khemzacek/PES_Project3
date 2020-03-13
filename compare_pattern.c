/*
 * compare_pattern.c
 *
 *  Created on: Mar 10, 2020
 *      Author: Katherine
 */

#include "compare_pattern.h"

uint8_t compare_pattern(uint8_t num_bytes, uint8_t seed, uint8_t extra3, uint32_t extra4)
{
	//compare_pattern	C
	uint8_t patterns_same;
	if(num_bytes > allocSize){
		num_bytes = allocSize;	// will only compare through allocated region
		//PRINTF("Size larger than allocated region. Checking allocated memory against pattern.\n");
	}
	patterns_same = check_pattern(num_bytes, seed, allocStart);
	//PRINTF("Memory is%s identical to pattern.\n", ((patterns_same) ? "" : " not"));
	return !patterns_same;
}

