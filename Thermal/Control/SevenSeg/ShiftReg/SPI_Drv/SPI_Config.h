/*
 *SPI_Config.h
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

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#include <avr/io.h>

#define SPI_DDR		(DDRB)
#define SPI_PORT	(PORTB)
#define SPI_MOSI	3
#define SPI_MISO	4
#define SPI_SCK		5
//#define SPI_SS		7

#define SPI_INTERRUPT_ENABLE

#define SPI_MASTER
//#define SPI_SLAVE

#define SPI_PRESCALER_2
//#define SPI_PRESCALER_4
//#define SPI_PRESCALER_8
//#define SPI_PRESCALER_16
//#define SPI_PRESCALER_32
//#define SPI_PRESCALER_64
//#define SPI_PRESCALER_128

#define SPI_MODE_0		//First Rise
//#define SPI_MODE_1	//LAst Fall
//#define SPI_MODE_2	//First Fall
//#define SPI_MODE_3	//Last Rise

#define SPI_FIRST_MSB
//#define SPI_FIRST_LSB

#endif /* SPI_CONFIG_H_ */