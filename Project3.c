/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    Project3.c
 * @brief   Application entry point.
 */

/* GENERAL INCLUDES */
#include <Project3.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/* INCLUDES CREATED FOR PROJECT */
// mem test functions
#include "allocate_bytes.h"
#include "free_allocated.h"
#include "verify_memory.h"
#include "display_memory.h"
#include "write_memory.h"
#include "invert_block.h"
#include "write_pattern.h"
#include "compare_pattern.h"

// other funtions
#include "LED_control.h"

/* GLOBAL VARIABLES */
uint8_t *allocStart = NULL;
uint8_t *allocEnd = NULL;
uint8_t allocSize = 0;

/* TEST SCRIPT */
const uint8_t script_len = 21;
const uint8_t script_wid = 14;
// as defined in project description
const char test_script[21][14] = {
	"A,32", //Allocate a 32 byte region in the heap
	"M", //Verify that memory is allocated (True)
	"P,32,143", //Write a pattern using the seed 143 to the first 32 bytes of the allocated memory
	"D,32", //Display the first 32 bytes of allocated memory
	"D,34", //Display the first 34 bytes of allocated memory (Out of range error)
	"C,32,143", //Compare the first 32 bytes of allocated memory to the pattern with seed 143 (True)
	"W,12,2,0xFFEE", //Write the hex value 0xFFEE to 2 bytes of allocated memory starting at byte 12
	"D,32", //Display the first 32 bytes of allocated memory
	"C,32,143", //Compare the first 32 bytes of allocated memory to the pattern with seed 143 (False)
	"P,16,127", //Write a pattern using the seed 127 to the first 16 bytes of the allocated memory
	"D,16", //Display the first 16 bytes of allocated memory
	"C,16,127", //Compare the first 16 bytes of allocated memory to the pattern with seed 127 (True)
	"I,35,2", //Invert all bits in 2 bytes of allocated memory starting at byte 35 (Out of range error)
	"I,9,2", //Invert all bits in 2 bytes of allocated memory starting at byte
	"D,16", //Display the first 16 bytes of allocated memory
	"C,16,127", //Compare the first 16 bytes of allocated memory to the pattern with seed 127 (False)
	"I,9,2", //Invert all bits in 2 bytes of allocated memory starting at byte 9
	"C,16,127", //Compare the first 16 bytes of allocated memory to the pattern with seed 127 (True)
	"D,16", //Display the first 16 bytes of allocated memory
	"F", //Free the allocated memory in the heap
	"M" //Verify that memory is allocated (False)
};

/* script commands */
char commands[8] = {'A', 'F', 'M', 'D', 'W', 'I', 'P', 'C'};


/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
    LED_init();


    /* ARRAY OF FUNCTION POINTERS */
    uint8_t (*func_ptr[8])(uint8_t, uint8_t, uint8_t, uint32_t);
    func_ptr[0] = &allocate_bytes;
    func_ptr[1] = &free_allocated;
    func_ptr[2] = &verify_memory;
    func_ptr[3] = &display_memory;
    func_ptr[4] = &write_pattern;
    func_ptr[5] = &invert_block;
    func_ptr[6] = &write_pattern;
    func_ptr[7] = &compare_pattern;

    /* START OF MEM TEST */
    LED_on(blue);


    char func = 0;
    uint32_t arg1, arg2, arg3, arg4;
    uint8_t func_return = 0;

    //loop runs test script a line at a time
    for(uint8_t l = 0; l < script_len; l++){
    	//reset args
    	arg1 = 0, arg2 = 0, arg3 = 0, arg4 = 0;
    	//parse script
    	sscanf(test_script[l], "%c,%d,%d,%#x", &func, &arg1, &arg2, &arg4);
    	//match char representing function with function's index in array
    	for(uint8_t i = 0; i < 8; i++){
    		if(func == commands[i]){
    			func = i;
    			break;
    		}
    	}
    	//call function
    	func_return = (*func_ptr[func])((uint8_t)arg1, (uint8_t)arg2, (uint8_t)arg3, arg4);
    	//interpret return - success/failure
    		//light LED according to return
    	if(func_return == 0){
    		LED_on(green);
    	}else if(func_return == 1){
    		LED_on(red);
    	}else{
    		LED_on(blue);
    	}
    	//log activity
    	PRINTF("Test run: %c,%d,%d,%#x\t Result: %d\n", commands[func], arg1, arg2, arg4, func_return);

    }

    return 0 ;
}
