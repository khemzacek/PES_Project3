/*
 * free_allocated.c
 *
 *  Created on: Mar 10, 2020
 *      Author: Katherine
 */
#include "free_allocated.h"


uint8_t free_allocated(uint8_t extra1, uint8_t extra2, uint8_t extra3, uint32_t extra4)
{
    if(allocStart == NULL){
    	//PRINTF("No memory allocated.\n");
    	return 1;
    }else{
    	free(allocStart);
    	allocStart = NULL;
    	allocEnd = NULL;

    	return 0;
    }
    //PRINTF("Allocated memory freed.\n");
}
