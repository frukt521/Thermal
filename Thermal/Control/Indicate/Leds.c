/*
 *Leds.c
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

#include "Leds.h"

uint8_t ledsState[4] = {0, 0, 0, 0};

void _Leds_StoreState(void)
{
	ledsState[0] = (LED_FAST_PORT & (1 << LED_FAST_NUM));
	ledsState[1] = (LED_NORM_PORT & (1 << LED_NORM_NUM));
	ledsState[2] = (LED_MAX_PORT & (1 << LED_MAX_NUM));
	ledsState[3] = (LED_WARM_PORT & (1 << LED_WARM_NUM));
}

void _Leds_RestoreState(void)
{
	LED_FAST_PORT ^= ledsState[0];
	LED_NORM_PORT ^= ledsState[1];
	LED_MAX_PORT ^= ledsState[2];
	LED_WARM_PORT ^= ledsState[3];
}

void Leds_Init(void)
{
	LED_FAST_DDR |= (1 << LED_FAST_NUM);
	LED_NORM_DDR |= (1 << LED_NORM_NUM);
	LED_MAX_DDR |= (1 << LED_MAX_NUM);
	LED_WARM_DDR |= (1 << LED_WARM_NUM);
}

void Leds_Switch(LedsList_e led, LedStates_e state)
{
	switch (state)
	{
		case LED_ON:
			switch (led)
			{
				case LED_FAST:
					LED_FAST_PORT |= (1 << LED_FAST_NUM);
					break;
				case LED_MAX:
					LED_MAX_PORT |= (1 << LED_MAX_NUM);
					break;
				case LED_NORM:
					LED_NORM_PORT |= (1 << LED_NORM_NUM);
					break;
				case LED_WARM:
					LED_WARM_PORT |= (1 << LED_WARM_NUM);
					break;
			}
			break;
		case LED_OFF:
			switch (led)
			{
				case LED_FAST:
					LED_FAST_PORT &= ~(1 << LED_FAST_NUM);
					break;
				case LED_MAX:
					LED_MAX_PORT &= ~(1 << LED_MAX_NUM);
					break;
				case LED_NORM:
					LED_NORM_PORT &= ~(1 << LED_NORM_NUM);
					break;
				case LED_WARM:
					LED_WARM_PORT &= ~(1 << LED_WARM_NUM);
					break;
			}
			break;
	}
}

void Leds_SwitchError(IndicateOrder_t* error, uint8_t stages, uint8_t cycles)
{
	_Leds_StoreState();
	Leds_Switch(LED_FAST, LED_OFF);
	Leds_Switch(LED_NORM, LED_OFF);
	Leds_Switch(LED_MAX, LED_OFF);
	Leds_Switch(LED_WARM, LED_OFF);
	SmartIndicate_IndicateProcess(error, stages, cycles);
	_Leds_RestoreState();
}