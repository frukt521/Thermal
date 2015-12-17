/*
 *Timer0.c
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

#include "Timer0.h"

volatile bool isDelay = false;
volatile uint8_t delayCyclesLeft = 0;

void Timer0_Init(void)
{
	TCCR0 |= (1 << CS02) | (1 << CS00);	//Set prescaler = 1024
	TIMSK |= (1 << TOIE0);				//Enable interrupt on owerflow
	//60 Hz for 7-segement indicator
	//Cycles count for 60Hz: 8000000/60/2/1024 = 65
	//Start value: 255-65 = 190
	TCNT0 = 190;
}

void Timer0_Delay(uint8_t cycles)
{
	delayCyclesLeft = cycles;
	isDelay = true;
}

ISR (TIMER0_OVF_vect)
{
	TCNT0 = 190;
	Timer0_EVENT_Cycle120Hz();
	if (isDelay)
	{
		delayCyclesLeft--;
		if (delayCyclesLeft == 0) isDelay = false;
	} 
	else
		Timer0_EVENT_CycleButton();
}