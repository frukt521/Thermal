/*
 *Leds.h
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

#ifndef LEDS_H_
#define LEDS_H_

#include <avr/io.h>
#include "SmartIndicate/SmartIndicate.h"

#define LED_FAST_DDR	(DDRC)
#define LED_FAST_PORT	(PORTC)
#define LED_FAST_NUM	1

#define LED_NORM_DDR	(DDRD)
#define LED_NORM_PORT	(PORTD)
#define LED_NORM_NUM	3

#define LED_MAX_DDR		(DDRD)
#define LED_MAX_PORT	(PORTD)
#define LED_MAX_NUM		0

#define LED_WARM_DDR	(DDRD)
#define LED_WARM_PORT	(PORTD)
#define LED_WARM_NUM	4

typedef enum
{
	LED_FAST,
	LED_NORM,
	LED_MAX,
	LED_WARM
} LedsList_e;


void Leds_Init(void);
void Leds_Switch(LedsList_e led, LedStates_e state);
void Leds_SwitchError(IndicateOrder_t* error, uint8_t stages, uint8_t cycles);

#endif /* LEDS_H_ */