/*
 * allocate_bytes.h
 *
 *  Created on: Mar 10, 2020
 *      Author: Katherine
 */

#ifndef ALLOCATE_BYTES_H_
#define ALLOCATE_BYTES_H_

#include "Project3.h"

#define MAX_ALLOC_SIZE	0xFFU

uint8_t allocate_bytes(uint8_t allocSize, uint8_t extra1, uint8_t extra2, uint32_t extra3);

#endif /* ALLOCATE_BYTES_H_ */
