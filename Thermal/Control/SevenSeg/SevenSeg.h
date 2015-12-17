/*
 *SevenSeg.h
 *Copyright (C) Vasilenko Victor, 2015.
*/

/*
  Copyright 2015 Vasilenko Victor

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose except commercial use 
  is hereby granted without fee, provided that the above copyright 
  notice appear in all copies and that both that the copyright 
  notice and this permission notice and warranty disclaimer appear
  in supporting documentation, and that the name of the author 
  not be used in advertising or publicity pertaining to 
  distribution of the software without specific, written 
  prior permission.

  The author disclaims all warranties with regard to this software.
  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use and data, arising out of 
  or in connection with the use or performance of this software.
*/

#ifndef SEVENSEG_H_
#define SEVENSEG_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ShiftReg/ShiftReg.h"

#define ANODES_DDR		(DDRD)
#define ANODES_PORT		(PORTD)
#define ANODES_COUNT	2
#define ANODE_1			1
#define ANODE_2			2

#define SEGMENT_A	SHIFT_Q6
#define SEGMENT_B	SHIFT_Q7
#define SEGMENT_C	SHIFT_Q1
#define SEGMENT_D	SHIFT_Q2  
#define SEGMENT_E	SHIFT_Q3
#define SEGMENT_F	SHIFT_Q4
#define SEGMENT_G	SHIFT_Q5

#define SELECT_ANODE_1()		do { ANODES_PORT &= ~(1 << ANODE_1);} while(0)
#define SELECT_ANODE_2()		do { ANODES_PORT &= ~(1 << ANODE_2);} while(0)
#define DESELECT_ANODE_ALL()	do { ANODES_PORT |= (1 << ANODE_1) | (1 << ANODE_2); } while(0)

void SevenSeg_Init(void);

void _SevenSeg_SelectAnode(uint8_t anodeNumber);

void SevenSeg_SetSegmentValue(uint8_t segmentNumber, uint8_t segmentValue);
void SevenSeg_GetNext(void);


#endif /* SEVENSEG_H_ */