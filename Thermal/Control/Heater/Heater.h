/*
 *Heater.h
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

#ifndef HEATER_H_
#define HEATER_H_

#include <avr/io.h>
#include <util/delay.h>

#define OPTOPAIR_HALF_DDR	(DDRD)
#define OPTOPAIR_HALF_PORT	(PORTD)
#define OPTOPAIR_HALF_NUM	7

#define OPTOPAIR_FULL_DDR	(DDRB)
#define OPTOPAIR_FULL_PORT	(PORTB)
#define OPTOPAIR_FULL_NUM	0

#define OPTOPAIRS_OFF()			do  { OPTOPAIR_HALF_PORT &= ~(1 << OPTOPAIR_HALF_NUM); OPTOPAIR_FULL_PORT &= ~(1 << OPTOPAIR_FULL_NUM); } while(0)
#define OPTOPAIRS_SET_HALF()	do { OPTOPAIR_HALF_PORT |= (1 << OPTOPAIR_HALF_NUM); } while (0)
#define OPTOPAIRS_SET_FULL()	do { OPTOPAIR_FULL_PORT |= (1 << OPTOPAIR_FULL_NUM); } while (0)

typedef enum
{
	HEATER_STATE_HALF,
	HEATER_STATE_FULL,
	HEATER_STATE_OFF
} HeaterStates_e;

void Heater_Init(void);
void Heater_SetState(HeaterStates_e state);

#endif /* HEATER_H_ */