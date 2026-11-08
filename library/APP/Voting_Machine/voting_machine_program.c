/*
 * voting_machine_program.c
 *
 * Created on: Nov 6, 2026
 * Author: Kirolos
 */

#include "../../LIB/BITMATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/EEPROM/EEPROM_interface.h"

#include "../../HAL/LCD/lcd_interface.h"
#include "../../HAL/LCD/lcd_config.h"

#include "../../HAL/keypad/keypad_interface.h"
#include "../../HAL/keypad/keypad_config.h"

#include "voting_machine_interface.h"

#include <util/delay.h>


void voting_machine_printvotes(u8 a, u8 b, u8 c, u8 d)
{
    lcd_movecursor(1, 1);

    lcd_sendstring("A:");
    lcd_sendnumber(a);
    lcd_sendstring("    ");

    lcd_sendstring("B:");
    lcd_sendnumber(b);
    lcd_sendstring("    ");

    lcd_movecursor(2, 1);

    lcd_sendstring("C:");
    lcd_sendnumber(c);
    lcd_sendstring("    ");

    lcd_sendstring("D:");
    lcd_sendnumber(d);
    lcd_sendstring("    ");
}


u8 voting_machine_savevotes(u8 a, u8 b, u8 c, u8 d)
{
    EEPROM_U8_memwrite(a, FIRST_CELL);
    EEPROM_U8_memwrite(b, SECOND_CELL);
    EEPROM_U8_memwrite(c, THIRD_CELL);
    EEPROM_U8_memwrite(d, FOURTH_CELL);

    return 0;
}


u8 voting_machine_loadvotes(u8 *a, u8 *b, u8 *c, u8 *d)
{
    EEPROM_U8_memread(a, FIRST_CELL);
    EEPROM_U8_memread(b, SECOND_CELL);
    EEPROM_U8_memread(c, THIRD_CELL);
    EEPROM_U8_memread(d, FOURTH_CELL);

    return 0;
}


void Start_System(u8 *a, u8 *b, u8 *c, u8 *d)
{
    static u8 initialized = 0;

    /* Load saved votes only once after startup */
    if (initialized == 0)
    {
        voting_machine_loadvotes(a, b, c, d);

        voting_machine_printvotes(*a, *b, *c, *d);

        initialized = 1;
    }

    /* Read keypad */
    u8 x = keypad_read();

    if (x != KEYPAD_NOT_PRESSED)
    {
        switch (x)
        {
            case 'A':
                (*a)++;
                break;

            case 'B':
                (*b)++;
                break;

            case 'C':
                (*c)++;
                break;

            case 'D':
                (*d)++;
                break;
            case 'c':
            		EEPROM_U8_memwrite(0, FIRST_CELL);
            	    EEPROM_U8_memwrite(0, SECOND_CELL);
            	    EEPROM_U8_memwrite(0, THIRD_CELL);
            	    EEPROM_U8_memwrite(0, FOURTH_CELL);
            	    (*a)=0;(*b)=0;(*c)=0;(*d)=0;
            	    break;


            default:
                return;
        }

        /* Save updated votes in EEPROM */
        voting_machine_savevotes(*a, *b, *c, *d);

        /* Update LCD */
        voting_machine_printvotes(*a, *b, *c, *d);

        _delay_ms(200);
    }
}
