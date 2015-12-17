/*
 *SmartIndicate.c
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

#include "SmartIndicate.h"

void  SmartIndicate_IndicateProcess(IndicateOrder_t* order, uint8_t stages, uint8_t cycles)
{
	for (uint8_t c = 0; c < cycles; c++)
	{
		for (uint8_t s = 0; s < stages; s++)
		{
			switch(order[s].Led.LedState)
			{
				case LED_ON:
					*order[s].Led.LedPort |= (1 << order[s].Led.LedNumber);
					break;
				case LED_OFF:
					*order[s].Led.LedPort &= ~(1 << order[s].Led.LedNumber);
					break;
			}
			for (uint16_t k = 0; k < order[s].DelayMs; k++)
			{
				_delay_ms(1);
				#ifdef WATCHDOG_ENABLE
					wdt_reset();
				#endif
			}
		}
	}
	
}
