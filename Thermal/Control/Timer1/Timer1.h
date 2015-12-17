/*
 *Timer1.h
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

#ifndef TIMER1_H_
#define TIMER1_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define TIMER1_PRESCALER_1		(1 << CS10)
#define TIMER1_PRESCALER_8		(1 << CS11)
#define TIMER1_PRESCALER_64		( (1 << CS11) | (1 << CS10) )
#define TIMER1_PRESCALER_256	(1 << CS12)
#define TIMER1_PRESCALER_1024	( (1 << CS12) | (1 << CS10) )

#define TIMER1_CYCLES_1MS	F_CPU/1000

#define TIMER1_CYCLES_MS_PS_1		(TIMER1_CYCLES_1MS)
#define TIMER1_CYCLES_MS_PS_8		(TIMER1_CYCLES_1MS/8)
#define TIMER1_CYCLES_MS_PS_64		(TIMER1_CYCLES_1MS/64)
#define TIMER1_CYCLES_MS_PS_256		(TIMER1_CYCLES_1MS/256)
#define TIMER1_CYCLES_MS_PS_1024	(TIMER1_CYCLES_1MS/1024)

#define TIMER1_PS_1_MAX_MS		(UINT16_MAX/TIMER1_CYCLES_MS_PS_1)
#define TIMER1_PS_8_MAX_MS		(UINT16_MAX/TIMER1_CYCLES_MS_PS_8)
#define TIMER1_PS_64_MAX_MS		(UINT16_MAX/TIMER1_CYCLES_MS_PS_64)
#define TIMER1_PS_256_MAX_MS	(UINT16_MAX/TIMER1_CYCLES_MS_PS_256)
#define TIMER1_PS_1024_MAX_MS	(UINT16_MAX/TIMER1_CYCLES_MS_PS_1024)


void Timer1_Init(void);
void Timer1_Start(void);
void Timer1_Stop(void);
void Timer1_SetCycleMs(uint16_t cycleMs);
/*
	Maximum value is 65536/F_CPU*1000*1024
	For example: if F_CPU = 8MHz then Max = 65536/8000000*1000*1024 = 8388ms
*/

void Timer1_EVENT_OnCycle(void);	//Implement in your code


#endif /* TIMER1_H_ */