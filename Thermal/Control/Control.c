/*
 *Control.c
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

#include "Control.h"

uint8_t normalTempEE EEMEM;
uint8_t maxTempEE EEMEM;
uint8_t currentTempModeEE EEMEM;
uint8_t currentHeaterModeEE EEMEM;

volatile uint8_t normalTemp;
volatile uint8_t maxTemp;
volatile TempModes_e currentTempMode;
volatile HeaterModes_e currentHeaterMode;

volatile bool showCurrentTemp = true;

IndicateOrder_t ErrorSensorEmpty[4] =
{
	{{LED_ON, &LED_NORM_PORT, LED_NORM_NUM}, 300},
	{{LED_OFF, &LED_NORM_PORT, LED_NORM_NUM}, 300},
	{{LED_ON, &LED_MAX_PORT, LED_MAX_NUM}, 300},
	{{LED_OFF, &LED_MAX_PORT, LED_MAX_NUM}, 300}
};

IndicateOrder_t ErrorTempUncorrect[4] =
{
	{{LED_ON, &LED_NORM_PORT, LED_NORM_NUM}, 300},
	{{LED_OFF, &LED_NORM_PORT, LED_NORM_NUM}, 300},
	{{LED_ON, &LED_FAST_PORT, LED_FAST_NUM}, 300},
	{{LED_OFF, &LED_FAST_PORT, LED_FAST_NUM}, 300}
};

void _Control_SwitchLeds(void)
{
	if (currentHeaterMode == HEATER_MODE_FULL)	
		Leds_Switch(LED_FAST, LED_ON);
	else
		Leds_Switch(LED_FAST, LED_OFF);
	if (currentTempMode == TEMP_MODE_NORM)
	{
		Leds_Switch(LED_NORM, LED_ON);
		Leds_Switch(LED_MAX, LED_OFF);
	}
	else
	{
		Leds_Switch(LED_MAX, LED_ON);
		Leds_Switch(LED_NORM, LED_OFF);
	}
}

void _Control_ShowTemp(uint8_t temp)
{
	SevenSeg_SetSegmentValue(1, temp/10);
	SevenSeg_SetSegmentValue(2, temp%10);
}

void _Control_SwapTempMode(void)
{
	if (currentTempMode == TEMP_MODE_NORM)
	{
		currentTempMode = TEMP_MODE_MAX;
		showCurrentTemp = false;
		_Control_ShowTemp(maxTemp);
	}
	else
	{
		currentTempMode = TEMP_MODE_NORM;
		showCurrentTemp = false;
		_Control_ShowTemp(normalTemp);
	}
	cli();
	eeprom_write_byte(&currentTempModeEE, currentTempMode);
	sei();
	_Control_SwitchLeds();
}

void _Control_SwapHeaterMode(void)
{
	if (currentHeaterMode == HEATER_MODE_HALF)
		currentHeaterMode = HEATER_MODE_FULL;
	else
		currentHeaterMode = HEATER_MODE_HALF;
	cli();
	eeprom_write_byte(&currentHeaterModeEE, currentHeaterMode);
	sei();
	_Control_SwitchLeds();
}

void _Control_ChangeTemp(ButtonPushed_e button)
{
	uint8_t tempSavedValue;

	if (currentTempMode == TEMP_MODE_NORM)
	{
		tempSavedValue = normalTemp;
		if (button == PUSHED_PLUS)	normalTemp++;
		else 
			if (button == PUSHED_MINUS)	normalTemp--;
				
		if (CHECK_TEMP_BORDER(normalTemp))
		{	
			cli();
			eeprom_write_byte(&normalTempEE, normalTemp);
			sei();
		}
		else
			normalTemp = tempSavedValue;
		showCurrentTemp = false;
		_Control_ShowTemp(normalTemp); 
		return;	
	}
	if (currentTempMode == TEMP_MODE_MAX)
	{
		tempSavedValue = maxTemp;
		if (button == PUSHED_PLUS)	maxTemp++;
		else
			if (button == PUSHED_MINUS)	maxTemp--;
		
		if (CHECK_TEMP_BORDER(maxTemp))
		{
			cli();
			eeprom_write_byte(&maxTempEE, maxTemp);
			sei();
		}
		else
			maxTemp = tempSavedValue;
		showCurrentTemp = false;
		_Control_ShowTemp(maxTemp); 	
	}
}

void _Control_ButtonsHandler(ButtonPushed_e button)
{
	if (button != PUSHED_NONE)
		Timer0_Delay(60); //500ms
	switch (button)
	{
		case PUSHED_NONE:
			return;
		case PUSHED_FAST:
			_Control_SwapHeaterMode();
			break;
		case PUSHED_MODE:
			_Control_SwapTempMode();
			break;
		default:
			_Control_ChangeTemp(button);
	}	
}

void _Control_LoadValues(void)
{
	maxTemp = eeprom_read_byte(&maxTempEE);
	normalTemp = eeprom_read_byte(&normalTempEE);
	if (!CHECK_TEMP_BORDER(maxTemp))		maxTemp = DEFAULT_MAX_TEMP;
	if (!CHECK_TEMP_BORDER(normalTemp))	normalTemp = DEFAULT_NORM_TEMP;
	
	currentHeaterMode = eeprom_read_byte(&currentHeaterModeEE);
	currentTempMode = eeprom_read_byte(&currentTempModeEE);
	if ( (currentHeaterMode != HEATER_MODE_FULL) && (currentHeaterMode != HEATER_MODE_HALF) )
		currentHeaterMode = HEATER_MODE_HALF;
	if ( (currentTempMode != TEMP_MODE_NORM) && (currentTempMode != TEMP_MODE_MAX) )
		currentTempMode = TEMP_MODE_NORM;
	
	_Control_SwitchLeds();
}

uint8_t _Control_GetCurrentTemp(void)
{
	if (DS18B20_DeviceExist())
		DS18B20_StartConversion();
	else
	{
		Heater_SetState(HEATER_STATE_OFF);
		Leds_SwitchError(ErrorSensorEmpty, 4, 3);
	}
	wdt_reset();	
	_delay_ms(120); //Conversion time = 98ms
	
	if (DS18B20_DeviceExist())
		return DS18B20_ReadIntTemp();
	else
	{
		Heater_SetState(HEATER_STATE_OFF);
		Leds_SwitchError(ErrorSensorEmpty, 4, 3);
	}
	return 0;
}

void Control_Init(void)
{
	wdt_enable(WDTO_2S);
	Buttons_Init();
	Leds_Init();
	Heater_Init();
	SevenSeg_Init();
	Timer0_Init();
	Timer1_Init();
	OneWire_Init();
	_Control_LoadValues();
	
	//Configure DS18B20
	if (DS18B20_DeviceExist())
		DS18B20_WriteConfig(127, 0, DS18B20_RESOLUTION_9);
	else
	{
		Heater_SetState(HEATER_STATE_OFF);
		Leds_SwitchError(ErrorSensorEmpty, 4, 3);
	}
		
	if (currentTempMode == TEMP_MODE_NORM)
		_Control_ShowTemp(normalTemp);
	else
		_Control_ShowTemp(maxTemp);
	
		
	Timer1_SetCycleMs(CHECK_TEMP_TIME_SEC * 1000);
	Timer1_Start();
}

void Timer0_EVENT_CycleButton(void)
{
	_Control_ButtonsHandler(Buttons_CheckButtons());
}

void Timer0_EVENT_Cycle120Hz(void)
{
	SevenSeg_GetNext();
}

void Timer1_EVENT_OnCycle(void)
{
	uint8_t currentTemp = _Control_GetCurrentTemp();
	uint8_t checkTemp;
	if (currentTempMode == TEMP_MODE_MAX)
		checkTemp = maxTemp;
	else
		checkTemp = normalTemp;
		
	if (CHECK_TEMP_BORDER(currentTemp))
	{
		if (currentTemp <= (checkTemp-TEMP_SENS_DEGREES))
		{
			Heater_SetState(currentHeaterMode);
			Leds_Switch(LED_WARM, LED_ON);
		}
		else
			if (currentTemp >= checkTemp)
			{
				Heater_SetState(HEATER_STATE_OFF);
				Leds_Switch(LED_WARM, LED_OFF);
			}
	}
	else
	{
		Heater_SetState(HEATER_STATE_OFF);
		Leds_SwitchError(ErrorTempUncorrect, 4, 3);
	}
	
	if (showCurrentTemp)
	{
		showCurrentTemp = false;
		_Control_ShowTemp(currentTemp);
	}	
	else
	{
		showCurrentTemp = true;
		_Control_ShowTemp(checkTemp);
	}
}