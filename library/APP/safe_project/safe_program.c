/*
 * safe_project_program.c
 *
 *  Created on: Nov 7, 2026
 *      Author: Kirolos
 */

#include "../../LIB/BITMATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/EEPROM/EEPROM_interface.h"

#include "../../HAL/LCD/lcd_interface.h"
#include "../../HAL/LCD/lcd_config.h"

#include "../../HAL/keypad/keypad_interface.h"
#include "../../HAL/keypad/keypad_config.h"
#include "safe_interface.h"

#include <util/delay.h>

/* ------------------------------------------------------------------ */
/*                         Private helpers                             */
/* ------------------------------------------------------------------ */

/* Block until a key is pressed  */
static u8 safe_WaitKey(void)
{
	u8 key;
	do
	{
		key = keypad_read();
	} while (key == KEYPAD_NOT_PRESSED);
	return key;
}

/* Read PASS_LENGTH keys into buf, showing '*' on the second LCD line. */
static void safe_ReadPassword(u8 *buf)
{
	u8 i;
	lcd_movecursor(2, 1);
	for (i = 0; i < PASS_LENGTH; i++)
	{
		buf[i] = safe_WaitKey();
		lcd_sendchar('*');
	}
}

/* Wrong-attempt counter stored in EEPROM so a reset does not give new tries. */
static u8 safe_GetTries(void)
{
	u8 tries;
	EEPROM_U8_memread(&tries, MEM_CELL_TRIES);
	if (tries == 0xFF)				/* erased cell = no failed attempts */
	{
		tries = 0;
	}
	if (tries > WRONG_INPUT)		/* corrupted value: treat as locked */
	{
		tries = WRONG_INPUT;
	}
	return tries;
}

/* Write only when the value changed, to save EEPROM write cycles. */
static void safe_SetTries(u8 tries)
{
	u8 old;
	EEPROM_U8_memread(&old, MEM_CELL_TRIES);
	if (old != tries)
	{
		EEPROM_U8_memwrite(tries, MEM_CELL_TRIES);
	}
}

/* Compare the entered password with the stored one.
 * All digits are always compared (no early exit). */
static u8 safe_CheckPassword(const u8 *entered)
{
	u8 i;
	u8 stored;

	for (i = 0; i < PASS_LENGTH; i++)
	{
		EEPROM_U8_memread(&stored, MEM_CELL + i);
		if (stored != entered[i])
		{
			return WRONG_PASS;
		}
	}
	return CORRECT_PASS;
}

/* Timed lockout with a countdown. Because the counter lives in EEPROM,
 * resetting the board during lockout just starts the lockout again. */
static void safe_Lockout(void)
{
	u8 s;
	lcd_clearscreen();
	lcd_sendstring("SAFE LOCKED");
	for (s = LOCKOUT_SECONDS; s > 0; s--)
	{
		lcd_movecursor(2, 1);
		lcd_sendstring("Wait ");
		lcd_sendnumber(s);
		lcd_sendstring("s  ");		/* trailing spaces erase old digits */
		_delay_ms(1000);
	}
	safe_SetTries(0);
	lcd_clearscreen();
}

/* ------------------------------------------------------------------ */
/*                           Public API                                */
/* ------------------------------------------------------------------ */

void safe_NewPassword(void)
{
	u8 buf[PASS_LENGTH];
	u8 i;

	lcd_clearscreen();
	lcd_sendstring("New password:");
	safe_ReadPassword(buf);

	/* Invalidate first, write the digits, and set the flag LAST.
	 * If power is lost in the middle, the flag is not set, so the next
	 * boot simply asks for a new password again. */
	EEPROM_U8_memwrite(0xFF, MEM_CELL_FLAG);
	for (i = 0; i < PASS_LENGTH; i++)
	{
		EEPROM_U8_memwrite(buf[i], MEM_CELL + i);
	}
	EEPROM_U8_memwrite(PASS_IS_SET, MEM_CELL_FLAG);
	safe_SetTries(0);

	lcd_clearscreen();
	lcd_sendstring("Saved!");
	_delay_ms(1000);
	lcd_clearscreen();
}

void safe_EnterPassword(void)
{
	u8 entered[PASS_LENGTH];
	u8 tries = safe_GetTries();

	/* Reset during a lockout: lock again instead of granting new tries. */
	if (tries >= WRONG_INPUT)
	{
		safe_Lockout();
		tries = 0;
	}

	lcd_clearscreen();
	lcd_sendstring("Enter password:");
	safe_ReadPassword(entered);

	if (safe_CheckPassword(entered) == CORRECT_PASS)
	{
		safe_SetTries(0);
		lcd_clearscreen();
		lcd_sendstring("OPEN :)");
		while (keypad_read() != LOCK_KEY);		/* wait for the lock key */
		lcd_clearscreen();
	}
	else
	{
		tries++;
		safe_SetTries(tries);

		lcd_clearscreen();
		lcd_sendstring("WRONG!!!");
		_delay_ms(1000);

		if (tries >= WRONG_INPUT)
		{
			safe_Lockout();
		}
		else
		{
			lcd_clearscreen();
			lcd_sendnumber(WRONG_INPUT - tries);
			lcd_sendstring(" tries left");
			_delay_ms(1000);
		}
		lcd_clearscreen();
	}
}

void safe_System_start(void)
{
	u8 flag;
	EEPROM_U8_memread(&flag, MEM_CELL_FLAG);

	if (flag != PASS_IS_SET)
	{
		safe_NewPassword();
	}
	safe_EnterPassword();
}
