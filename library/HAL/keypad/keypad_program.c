/*
 * keypad_program.c
 *
 *  Created on: Nov 6, 2026
 *      Author: Kirolos
 */

#include "../../LIB/BITMATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "keypad_interface.h"

#include <util/delay.h>

/* ------------------------------------------------------------------ */
/* Private data                                                        */
/* ------------------------------------------------------------------ */

static const u8 keypad_rowPins[KEYPAD_ROWS] = KEYPAD_ROW_PINS;
static const u8 keypad_colPins[KEYPAD_COLS] = KEYPAD_COL_PINS;

static const u8 keypad_keys[KEYPAD_ROWS][KEYPAD_COLS] = KEYPAD_KEYMAP;

/* Last key reported by keypad_read(); used to report each press only once. */
static u8 keypad_lastKey = KEYPAD_NOT_PRESSED;

/* ------------------------------------------------------------------ */
/* Public functions                                                    */
/* ------------------------------------------------------------------ */

u8 keypad_init(void)
{
	u8 i;

	/* Rows: outputs, idle HIGH */
	for (i = 0; i < KEYPAD_ROWS; i++)
	{
		DIO_u8SetPinDirection(KEYPAD_ROW_PORT, keypad_rowPins[i], DIO_u8_OUTPUT);
		DIO_u8SetPinValue    (KEYPAD_ROW_PORT, keypad_rowPins[i], DIO_u8_HIGH);
	}

	/* Columns: inputs with internal pull-up */
	for (i = 0; i < KEYPAD_COLS; i++)
	{
		DIO_u8SetPinDirection(KEYPAD_COL_PORT, keypad_colPins[i], DIO_u8_INPUT);
		DIO_u8SetPinValue    (KEYPAD_COL_PORT, keypad_colPins[i], DIO_u8_HIGH);
	}

	keypad_lastKey = KEYPAD_NOT_PRESSED;
	return KEYPAD_OK;
}

u8 keypad_scan(void)
{
	u8 row, col;
	u8 pinValue = DIO_u8_HIGH;
	u8 key = KEYPAD_NOT_PRESSED;

	for (row = 0; row < KEYPAD_ROWS && key == KEYPAD_NOT_PRESSED; row++)
	{

		DIO_u8SetPinValue(KEYPAD_ROW_PORT, keypad_rowPins[row], DIO_u8_LOW);
		_delay_us(KEYPAD_SETTLE_US);

		for (col = 0; col < KEYPAD_COLS; col++)
		{
			DIO_u8GetPinValue(KEYPAD_COL_PORT, keypad_colPins[col], &pinValue);
			if (pinValue == DIO_u8_LOW)
			{
				key = keypad_keys[row][col];
				break;
			}
		}

		/* Always release the row before leaving, so rows never stay LOW */
		DIO_u8SetPinValue(KEYPAD_ROW_PORT, keypad_rowPins[row], DIO_u8_HIGH);
	}

	return key;
}

u8 keypad_read(void)
{
	u8 key = keypad_scan();

	/* Nothing pressed: forget the last key so the next press is a new event */
	if (key == KEYPAD_NOT_PRESSED)
	{
		keypad_lastKey = KEYPAD_NOT_PRESSED;
		return KEYPAD_NOT_PRESSED;
	}

	/* Still the same key held down: already reported */
	if (key == keypad_lastKey)
	{
		return KEYPAD_NOT_PRESSED;
	}

	/* New key: wait for the contacts to settle and confirm it */
	_delay_ms(KEYPAD_DEBOUNCE_MS);
	if (keypad_scan() != key)
	{
		return KEYPAD_NOT_PRESSED;       /* it was only bounce / noise */
	}

	keypad_lastKey = key;
	return key;
}

u8 keypad_waitkey(void)
{
	u8 key;

	do
	{
		key = keypad_read();
	}
	while (key == KEYPAD_NOT_PRESSED);

	return key;
}
