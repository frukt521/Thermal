/*
 *Timer1.c
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

#include "Timer1.h"

volatile uint8_t currentPrescaler;

void Timer1_Init(void)
{
	//CTC mode, max on OCR1A
	TCCR1A |= (1 << WGM12);
	TIMSK |= (1 << OCIE1A);
}

void Timer1_SetCycleMs(uint16_t cycleMs)
{
	//Select prescaler for current time
	if (cycleMs <= TIMER1_PS_1_MAX_MS)
	{
		currentPrescaler = TIMER1_PRESCALER_1;
		OCR1A = TIMER1_CYCLES_MS_PS_1*cycleMs;
	}
	else
		if (cycleMs <= TIMER1_PS_8_MAX_MS)
		{
			currentPrescaler = TIMER1_PRESCALER_8;
			OCR1A = TIMER1_CYCLES_MS_PS_8*cycleMs;
		}
		else
			if (cycleMs <= TIMER1_PS_64_MAX_MS)
			{
				currentPrescaler = TIMER1_PRESCALER_64;
				OCR1A = TIMER1_CYCLES_MS_PS_64*cycleMs;
			}
			else
				if (cycleMs <= TIMER1_PS_256_MAX_MS)
				{
					currentPrescaler = TIMER1_PRESCALER_256;
					OCR1A = TIMER1_CYCLES_MS_PS_256*cycleMs;
				}
				else
					if (cycleMs <= TIMER1_PS_1024_MAX_MS)
					{
						currentPrescaler = TIMER1_PRESCALER_1024;
						OCR1A = TIMER1_CYCLES_MS_PS_1024*cycleMs;
					} 
	if ( (TCCR1B & ((1 << CS12) | (1 << CS11) | (1 << CS10))) != 0 )
	{
		TCNT1 = 0;
		//TCCR1B &= ( 0xFF & ~((1 << CS12) | (1 << CS11) | (1 << CS10)) );
		TCCR1B |= currentPrescaler;
	}
}

void Timer1_Start(void)
{
	TCNT1 = 0;
	TCCR1B |= currentPrescaler;
}

void Timer1_Stop(void)
{
	TCCR1B &= ( 0xFF & ~((1 << CS12) | (1 << CS11) | (1 << CS10)) );
}

ISR (TIMER1_COMPA_vect)
{
	TCNT1 = 0;
	Timer1_EVENT_OnCycle();
}