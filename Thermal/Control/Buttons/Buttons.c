/*
 *Buttons.c
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

#include "Buttons.h"

void Buttons_Init(void)
{
	BUTTON_PLUS_PORT |= (1 << BUTTON_PLUS_NUM);
	BUTTON_PLUS_DDR &= ~(1 << BUTTON_PLUS_NUM);
	
	BUTTON_MINUS_PORT |= (1 << BUTTON_MINUS_NUM);
	BUTTON_MINUS_DDR &= ~(1 << BUTTON_MINUS_NUM);
	
	BUTTON_MODE_PORT |= (1 << BUTTON_MODE_NUM);
	BUTTON_MODE_DDR &= ~(1 << BUTTON_MODE_NUM);
	
	BUTTON_FAST_PORT |= (1 << BUTTON_FAST_NUM);
	BUTTON_FAST_DDR &= ~(1 << BUTTON_FAST_NUM);
}

ButtonPushed_e Buttons_CheckButtons(void)
{
	if (BUTTON_IS_PLUS()) return PUSHED_PLUS;
	if (BUTTON_IS_MINUS()) return PUSHED_MINUS; 
	if (BUTTON_IS_MODE()) return PUSHED_MODE;
	if (BUTTON_IS_FAST()) return PUSHED_FAST;
	return PUSHED_NONE;
}