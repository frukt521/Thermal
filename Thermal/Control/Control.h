/*
 *Control.h
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

#ifndef CONTROL_H_
#define CONTROL_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "Buttons/Buttons.h"
#include "Indicate/Leds.h"
#include "Heater/Heater.h"
#include "SevenSeg/SevenSeg.h"
#include "Timer0/Timer0.h"
#include "Timer1/Timer1.h"
#include "DS18B20/DS18B20.h"

#define TEMP_SENS_DEGREES		2
#define CHECK_TEMP_TIME_SEC		5
#define TEMP_SENSOR_SHIFT		0
#define MAX_TEMP_BORDER			78
#define MIN_TEMP_BORDER			2
#define DEFAULT_NORM_TEMP		35
#define DEFAULT_MAX_TEMP		75

#define CHECK_TEMP_BORDER(temp)	( ((temp < MIN_TEMP_BORDER) || (temp > MAX_TEMP_BORDER)) ? false : true )

typedef enum
{
	TEMP_MODE_NORM,
	TEMP_MODE_MAX
} TempModes_e;

typedef enum
{
	HEATER_MODE_HALF,
	HEATER_MODE_FULL,
} HeaterModes_e;

void Control_Init(void);

#endif /* CONTROL_H_ */