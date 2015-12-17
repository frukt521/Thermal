/*
 *ShiftReg.c
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

#include "ShiftReg.h"

void ShiftReg_Init(void)
{
	SPI_Init();
	STORAGE_CLK_DDR |= (1 << STORAGE_CLK_NUM);
	_STORAGE_CLK_DOWN();
}

void ShiftReg_LoadByte(uint8_t loadByte)
{
	_STORAGE_CLK_DOWN();
	SPI_CheckMaster();
	SPI_LoadByte(loadByte);
}

void SPI_EVENT_OnTransmit(void)
{
	_STORAGE_CLK_UP();
	_delay_us(50);
	_STORAGE_CLK_DOWN();		
}