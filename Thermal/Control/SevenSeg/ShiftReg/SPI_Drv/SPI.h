/*
 *SPI.h
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

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "SPI_Config.h"

void SPI_Init(void);

#ifdef SPI_MASTER
	#ifdef SPI_INTERRUPT_ENABLE
		void SPI_LoadByte(uint8_t transcieveByte);
		uint8_t SPI_ReadRecievedByte(void);
		void SPI_EVENT_OnTransmit(void);				//Implement in your code
		void SPI_CheckMaster(void);		//Fix for SS pin is input
	#else
		uint8_t SPI_ByteProcess(uint8_t transcieveByte);
		void SPI_WriteByteArray(uint8_t* data, uint8_t length);
	#endif
#endif

#ifdef SPI_SLAVE
	#ifndef SPI_INTERRUPT_ENABLE
		void SPI_StartListen(void);
	#endif
		void SPI_EVENT_ByteReaded(uint8_t readedByte);	//Implement in your code
		void SPI_ByteSendNext(uint8_t data);
#endif

#endif /* SPI_H_ */