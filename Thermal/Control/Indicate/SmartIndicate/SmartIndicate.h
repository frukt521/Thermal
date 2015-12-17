/*
 *SmartIndicate.h
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

#ifndef SMARTINDICATE_H_
#define SMARTINDICATE_H_

#include <avr/io.h>
#include <util/delay.h>

#define INDICATE_MAX_ORDER_STAGES	8
#define WATCHDOG_ENABLE

#ifdef WATCHDOG_ENABLE
	#include <avr/wdt.h>
#endif

typedef enum
{
	LED_ON,
	LED_OFF
} LedStates_e;

typedef struct
{
	LedStates_e LedState;
	volatile uint8_t* LedPort;
	uint8_t LedNumber;
} IndicateLed_t;

typedef struct 
{
	IndicateLed_t Led;
	uint16_t DelayMs;
} IndicateOrder_t;

void  SmartIndicate_IndicateProcess(IndicateOrder_t* order, uint8_t stages, uint8_t cycles);

#endif /* SMARTINDICATE_H_ */