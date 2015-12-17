/*
 *DS18B20.c
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

#include "DS18B20.h"

bool DS18B20_DeviceExist(void)
{
	return ( OneWire_ResetAndDetectPresence() == OneWire_DEVICEIS ? true : false);
}

void DS18B20_StartConversion(void)
{
	OneWire_SkipRom();
	OneWire_SendByte(DS18B20_START_CONVERSION);
}

int8_t DS18B20_ReadIntTemp(void)
{
	uint8_t tmpTemp[2] = {0,0};
	OneWire_SkipRom();
	OneWire_SendByte(DS18B20_READ_RAM);
	tmpTemp[0] = OneWire_ReceiveByte();
	tmpTemp[1] = OneWire_ReceiveByte();
	OneWire_ResetAndDetectPresence();
	return (tmpTemp[0] >> 4) | (tmpTemp[1] << 4);
}

int16_t DS18B20_ReadAllTemp(void)
{
	uint8_t tmpTemp[2] = {0,0};
	OneWire_SkipRom();
	OneWire_SendByte(DS18B20_READ_RAM);
	tmpTemp[0] = OneWire_ReceiveByte();
	tmpTemp[1] = OneWire_ReceiveByte();
	OneWire_ResetAndDetectPresence();
	return (uint32_t)tmpTemp[0] | ( (uint16_t)(tmpTemp[1] & 0b01111000) << 8);
}


void DS18B20_WriteConfig(int8_t tMax, int8_t tMin, uint8_t resolution)
{
	OneWire_SkipRom();
	OneWire_SendByte(DS18B20_WRITE_RAM);
	OneWire_SendByte(tMax);
	OneWire_SendByte(tMin);
	OneWire_SendByte(resolution);
}