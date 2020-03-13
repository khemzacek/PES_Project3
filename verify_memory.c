/*
 * verify_memory.c
 *
 *  Created on: Mar 10, 2020
 *      Author: Katherine
 */
#include "verify_memory.h"

uint8_t verify_memory(uint8_t extra1, uint8_t extra2, uint8_t extra3, uint32_t extra4)
{
    if(allocStart == NULL){
    	//PRINTF("Memory not allocated\n");
    	return 1;
    }else{
    	//PRINTF("Memory allocated at %#x\n", allocMem);
    	return 0;
    }
}
