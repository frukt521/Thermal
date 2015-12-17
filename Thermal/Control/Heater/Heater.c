/*
 *Heater.c
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

#include "Heater.h"

void Heater_Init(void)
{
	OPTOPAIR_FULL_DDR |= (1 << OPTOPAIR_FULL_NUM);
	OPTOPAIR_HALF_DDR |= (1 << OPTOPAIR_HALF_NUM);
}

void Heater_SetState(HeaterStates_e state)
{
	OPTOPAIRS_OFF();
	_delay_ms(1);
	switch (state)
	{
		case HEATER_STATE_OFF:
			break;
		case HEATER_STATE_FULL:
			OPTOPAIRS_SET_FULL();
			break;
		case HEATER_STATE_HALF:
			OPTOPAIRS_SET_HALF();
			break;
	}
}