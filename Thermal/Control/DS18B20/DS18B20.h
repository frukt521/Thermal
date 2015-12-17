/*
 *DS18B20.h
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

#ifndef DS18B20_H_
#define DS18B20_H_

#include <avr/io.h>
#include <stdbool.h>

#include "OneWire/OneWire.h"

#define DS18B20_START_CONVERSION	0x44
#define DS18B20_READ_RAM			0xBE
#define DS18B20_WRITE_RAM			0x4E

#define DS18B20_RESOLUTION_9		0x1F
#define DS18B20_RESOLUTION_10		0x3F
#define DS18B20_RESOLUTION_11		0x5F
#define DS18B20_RESOLUTION_12		0x7F

bool DS18B20_DeviceExist(void);
void DS18B20_StartConversion(void);
void DS18B20_WriteConfig(int8_t tMax, int8_t tMin, uint8_t resolution);
int8_t DS18B20_ReadIntTemp(void);	//Only integer part
int16_t DS18B20_ReadAllTemp(void);	//0..3 bytes - fractal, 4..10 bytes - integer part 

#endif /* DS18B20_H_ */