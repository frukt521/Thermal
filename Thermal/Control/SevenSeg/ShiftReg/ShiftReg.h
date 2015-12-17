/*
 *ShiftReg.h
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

#ifndef SHIFTREG_H_
#define SHIFTREG_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "SPI_Drv/SPI.h"

#define SHIFT_Q0	(1 << 0)
#define SHIFT_Q1	(1 << 1)
#define SHIFT_Q2	(1 << 2)
#define SHIFT_Q3	(1 << 3)
#define SHIFT_Q4	(1 << 4)
#define SHIFT_Q5	(1 << 5)
#define SHIFT_Q6	(1 << 6)
#define SHIFT_Q7	(1 << 7)

#define STORAGE_CLK_DDR		(DDRC)
#define STORAGE_CLK_PORT	(PORTC)
#define STORAGE_CLK_NUM		2

#define _STORAGE_CLK_UP()		do{ STORAGE_CLK_PORT |= (1 << STORAGE_CLK_NUM); } while(0)
#define _STORAGE_CLK_DOWN()		do{ STORAGE_CLK_PORT &= ~(1 << STORAGE_CLK_NUM); } while(0)

void ShiftReg_Init(void);
void ShiftReg_LoadByte(uint8_t loadByte);


#endif /* SHIFTREG_H_ */