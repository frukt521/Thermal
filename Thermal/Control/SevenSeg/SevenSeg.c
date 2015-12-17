/*
 *SevenSeg.c
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

#include "SevenSeg.h"

const uint8_t Numbers[] =
{
	/*0*/ 0xFF & ~SEGMENT_A & ~SEGMENT_B & ~SEGMENT_C & ~SEGMENT_D & ~SEGMENT_E & ~SEGMENT_F,
	/*1*/ 0xFF & ~SEGMENT_B & ~SEGMENT_C,
	/*2*/ 0xFF & ~SEGMENT_A & ~SEGMENT_B & ~SEGMENT_D & ~SEGMENT_E & ~SEGMENT_G,
	/*3*/ 0xFF & ~SEGMENT_A & ~SEGMENT_B & ~SEGMENT_C & ~SEGMENT_D & ~SEGMENT_G,
	/*4*/ 0xFF & ~SEGMENT_B & ~SEGMENT_C & ~SEGMENT_F & ~SEGMENT_G,
	/*5*/ 0xFF & ~SEGMENT_A & ~SEGMENT_C & ~SEGMENT_D & ~SEGMENT_F & ~SEGMENT_G,
	/*6*/ 0xFF & ~SEGMENT_A & ~SEGMENT_C & ~SEGMENT_D & ~SEGMENT_E & ~SEGMENT_F & ~SEGMENT_G,
	/*7*/ 0xFF & ~SEGMENT_A & ~SEGMENT_B & ~SEGMENT_C,
	/*8*/ 0xFF & ~SEGMENT_A & ~SEGMENT_B & ~SEGMENT_C & ~SEGMENT_D & ~SEGMENT_E & ~SEGMENT_F & ~SEGMENT_G,
	/*9*/ 0xFF & ~SEGMENT_A & ~SEGMENT_B & ~SEGMENT_C & ~SEGMENT_D & ~SEGMENT_F & ~SEGMENT_G,
	/*Empty*/ 0xFF
};
#define SEGMENT_EMPTY 10

volatile uint8_t selectedAnode = 0;
volatile uint8_t currentDisplayNumber[2] = {SEGMENT_EMPTY, SEGMENT_EMPTY};

void SevenSeg_Init(void)
{
	ANODES_DDR |= (1 << ANODE_1) | (1 << ANODE_2);
	DESELECT_ANODE_ALL();
	ShiftReg_Init();
}

void _SevenSeg_SelectAnode(uint8_t anodeNumber)
{
	DESELECT_ANODE_ALL();
	switch (anodeNumber)
	{
		case 1:
			SELECT_ANODE_1();
			break;
		case 2:
			SELECT_ANODE_2();
			break;
	}
}

void SevenSeg_SetSegmentValue(uint8_t segmentNumber, uint8_t segmentValue)
{
	if ( (segmentNumber > ANODES_COUNT) || (segmentValue > 9) ) return; 
	currentDisplayNumber[segmentNumber-1] = segmentValue;
}

void SevenSeg_GetNext(void)
{
	selectedAnode++;
	if (selectedAnode > ANODES_COUNT) selectedAnode = 1;
	ShiftReg_LoadByte(Numbers[currentDisplayNumber[selectedAnode-1]]);
	_SevenSeg_SelectAnode(selectedAnode);
}