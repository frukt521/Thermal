/*
 *SPI.c
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

#include "SPI.h"

void SPI_Init(void)
{
	/*
	------SPCR - SPI Control Register------
	
	SPIE - SPI Interrupt Enable
	SPE - SPI Enable
	DORD - Data Order
		1 - LSB transmitted first
		0 - MSB transmitted first
	MSTR - Master/Slave select
	CPOL - Clock Polarity
		1 - Falling edge
		0 - Rising edge
	CPHA - Clock Phase
		1 - End of impulse edge
		0 - Start of impulse edge
	SPR1	SPR0
	0		0		f/4
	0		1		f/16
	1		0		f/64
	1		1		f/128
	*/		
	/*
	-----SPSR - SPI Status Register------
	SPIF - SPI Interrupt flag
	WCOL - Write colision flag
	SPI2X - Double speed f/[SPR1,SPR0]/2
	*/
	/*
	-----SPDR - SPI Data Register-----
	7bit - MSB
	0bit - LSB
	*/

	//Configure Master and Ports {
	#ifdef SPI_MASTER
		SPCR |= (1 << MSTR);	//Set as master
		SPI_DDR |= (1 << SPI_MOSI) | (1 << SPI_SCK);
		SPI_DDR &= ~(1 << SPI_MISO);
	#endif
	//Configure Master and Ports }
	
	//Configure Slave and Ports {
	#ifdef SPI_SLAVE
		SPCR &= ~(1 << MSTR);	//Set as slave
		SPI_DDR &= ~(1 << SPI_MOSI) & ~(1 << SPI_SCK) & ~(1 << SPI_SS);
		SPI_DDR |= (1 << SPI_MISO);
	#endif
	//Configure Slave and Ports }
	
	//Select prescaler {
	#ifdef SPI_PRESCALER_2
		SPSR |= (1 << SPI2X);
		SPCR &= ~(1 << SPR1) & ~(1 << SPR0);
	#endif
	#ifdef SPI_PRESCALER_4
		SPSR &= ~(1 << SPI2X);
		SPCR &= ~(1 << SPR1) & ~(1 << SPR0);
	#endif
	#ifdef SPI_PRESCALER_8
		SPSR |= (1 << SPI2X);
		SPCR &= ~(1 << SPR1);
		SPCR |= (1 << SPR0);
	#endif
	#ifdef SPI_PRESCALER_16
		SPSR &= ~(1 << SPI2X);
		SPCR &= ~(1 << SPR1);
		SPCR |= (1 << SPR0);
	#endif
	#ifdef SPI_PRESCALER_32
		SPSR |= (1 << SPI2X);
		SPCR |= (1 << SPR1);
		SPCR &= ~(1 << SPR0);
	#endif
	#ifdef SPI_PRESCALER_64
		SPSR |= (1 << SPI2X);
		SPCR |= (1 << SPR1);
		SPCR |= (1 << SPR0);
	#endif
	#ifdef SPI_PRESCALER_128
		SPSR &= ~(1 << SPI2X);
		SPCR |= (1 << SPR1) | (1 << SPR0);
	#endif
	//Select prescaler }
	
	//Select DataOrder {
	#ifdef SPI_FIRST_MSB
		SPCR &= ~(1 << DORD);
	#endif
	#ifdef SPI_FIRST_LSB
		SPCR |= (1 << DORD);
	#endif
	//Select DataOrder }
	
	//Select SPI mode {
	#ifdef SPI_MODE_0
		SPCR &= ~(1 << CPHA) & ~(1 << CPOL);
	#endif
	#ifdef SPI_MODE_1
		SPCR |= (1 << CPHA);
		SPCR &= ~(1 << CPOL);
	#endif
	#ifdef SPI_MODE_2
		SPCR &= ~(1 << CPHA);
		SPCR |= (1 << CPOL);
	#endif
	#ifdef SPI_MODE_3
		SPCR |= (1 << CPHA) |(1 << CPOL);
	#endif
	//Select SPI mode }
	
	#ifdef SPI_INTERRUPT_ENABLE
		SPCR |= (1 << SPIE);
	#endif
	
	//SPI enable
	SPCR |= (1 << SPE);
}

#ifdef SPI_MASTER

void SPI_CheckMaster(void)
{
	if ( (SPCR & (1 << MSTR)) != (1 << MSTR) )
		SPCR |= (1 << MSTR);
}

#ifdef SPI_INTERRUPT_ENABLE

void SPI_LoadByte(uint8_t transcieveByte)
{
	SPDR = transcieveByte;
}

uint8_t SPI_ReadRecievedByte(void)
{
	return SPDR;
}

ISR (SPI_STC_vect)
{
	SPI_EVENT_OnTransmit();
}

#else

void _SPI_WaitTransmit(uint8_t transcieveByte)
{
	SPDR = transcieveByte;
	while ( (SPSR & (1 << SPIF) ) == 0);
}

uint8_t SPI_ByteProcess(uint8_t transcieveByte)
{
	_SPI_WaitTransmit(transcieveByte);
	return SPDR;
}

void SPI_WriteByteArray(uint8_t* data, uint8_t length)
{
	for (int i = 0; i < length; i++)
	_SPI_WaitTransmit(data[i]);
}

#endif //SPI_INTERRUPT_ENABLE

#endif //SPI_MASTER

#ifdef SPI_SLAVE



void SPI_ByteSendNext(uint8_t data)
{
	SPDR = data;
}

#ifndef SPI_INTERRUPT_ENABLE

void SPI_StartListen(void)
{
	while(1)
	{
		while ((SPSR & (1 << SPIF)) != 1);
		SPI_EVENT_ByteReaded(SPDR);
	}
}

#else

ISR (SPI_STC_vect)
{
	SPI_EVENT_ByteReaded(SPDR);
}

#endif //SPI_INTERRUPT_ENABLE

#endif //SPI_SLAVE