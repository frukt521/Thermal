/*
 *Buttons.h
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

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <avr/io.h>
#include <stdbool.h>

#define BUTTON_PLUS_DDR		(DDRC)
#define BUTTON_PLUS_PORT	(PORTC)
#define BUTTON_PLUS_PIN		(PINC)
#define BUTTON_PLUS_NUM		3

#define BUTTON_MINUS_DDR	(DDRC)
#define BUTTON_MINUS_PORT	(PORTC)
#define BUTTON_MINUS_PIN	(PINC)
#define BUTTON_MINUS_NUM	0

#define BUTTON_MODE_DDR		(DDRD)
#define BUTTON_MODE_PORT	(PORTD)
#define BUTTON_MODE_PIN		(PIND)
#define BUTTON_MODE_NUM		6

#define BUTTON_FAST_DDR		(DDRB)
#define BUTTON_FAST_PORT	(PORTB)
#define BUTTON_FAST_PIN		(PINB)
#define BUTTON_FAST_NUM		2

#define BUTTON_IS_PLUS()	( ((BUTTON_PLUS_PIN & (1 << BUTTON_PLUS_NUM)) != (1 << BUTTON_PLUS_NUM)) ? true : false )
#define BUTTON_IS_MINUS()	( ((BUTTON_MINUS_PIN & (1 << BUTTON_MINUS_NUM)) != (1 << BUTTON_MINUS_NUM)) ? true : false )
#define BUTTON_IS_MODE()	( ((BUTTON_MODE_PIN & (1 << BUTTON_MODE_NUM)) != (1 << BUTTON_MODE_NUM)) ? true : false )
#define BUTTON_IS_FAST()	( ((BUTTON_FAST_PIN & (1 << BUTTON_FAST_NUM)) != (1 << BUTTON_FAST_NUM)) ? true : false )

typedef enum
{
	PUSHED_PLUS,
	PUSHED_MINUS,
	PUSHED_MODE,
	PUSHED_FAST,
	PUSHED_NONE
} ButtonPushed_e;

void Buttons_Init(void);
ButtonPushed_e Buttons_CheckButtons(void); 

#endif /* BUTTONS_H_ */