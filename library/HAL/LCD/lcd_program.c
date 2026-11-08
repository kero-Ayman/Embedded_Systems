
/*
 * lcd_program.c
 *
 *  Created on: Nov 4, 2026
 *      Author: Kirolos
 */

#include "../../LIB/BITMATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "lcd_interface.h"
#include "lcd_config.h"

#include <util/delay.h>



/* ------------------------------------------------------------------ */
/* Private data                                                        */
/* ------------------------------------------------------------------ */

/* Software-tracked cursor position (needed for auto wrap). */
static u8 lcd_currentRow = 1;
static u8 lcd_currentCol = 1;

/* DDRAM start address of each row. */
static const u8 lcd_rowOffset[4] = {0x00, 0x40, 0x14, 0x54};

/* ------------------------------------------------------------------ */
/* Private functions                                                   */
/* ------------------------------------------------------------------ */

static void lcd_enable(void)
{
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_ENABLE_PIN, DIO_u8_HIGH);
    _delay_us(1);
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_ENABLE_PIN, DIO_u8_LOW);
    _delay_us(50);
}


static void lcd_write(u8 rs, u8 value)
{
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, rs);
    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_u8_LOW);
    DIO_u8SetPortValue(LCD_DATA_PORT, value);
    lcd_enable();
}

/* ------------------------------------------------------------------ */
/* Public functions                                                    */
/* ------------------------------------------------------------------ */

u8 lcd_sendcmd(u8 cmd)
{
    lcd_write(DIO_u8_LOW, cmd);

    /* Clear and Home need about 1.52 ms and reset the address counter. */
    if (cmd == LCD_CMD_CLEAR || cmd == LCD_CMD_HOME)
    {
        _delay_ms(2);
        lcd_currentRow = 1;
        lcd_currentCol = 1;
    }

    return LCD_OK;
}


u8 lcd_init(void)
{
    DIO_u8SetPortDirection(LCD_DATA_PORT, DIO_u8_OUTPUT);
    DIO_u8SetPinDirection(LCD_CONTROL_PORT, LCD_RS_PIN,     DIO_u8_OUTPUT);
    DIO_u8SetPinDirection(LCD_CONTROL_PORT, LCD_RW_PIN,     DIO_u8_OUTPUT);
    DIO_u8SetPinDirection(LCD_CONTROL_PORT, LCD_ENABLE_PIN, DIO_u8_OUTPUT);

    DIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_ENABLE_PIN, DIO_u8_LOW);

    _delay_ms(50);

    lcd_sendcmd(LCD_CMD_FUNCTION_RESET);
    _delay_ms(5);

    lcd_sendcmd(LCD_CMD_FUNCTION_RESET);
    _delay_us(150);

    lcd_sendcmd(LCD_CMD_FUNCTION_RESET);
    _delay_us(150);

    lcd_sendcmd(LCD_CMD_FUNCTION_8BIT);
    lcd_sendcmd(LCD_CMD_DISPLAY_ON);

    lcd_clearscreen();

    lcd_sendcmd(LCD_CMD_ENTRY_INC);

    return LCD_OK;
}


u8 lcd_movecursor(u8 row, u8 column)
{
    if (row == 0 || row > LCD_ROWS ||
        column == 0 || column > LCD_COLS)
    {
        return LCD_NOK;
    }

    lcd_currentRow = row;
    lcd_currentCol = column;

    lcd_write(DIO_u8_LOW,
        LCD_CMD_SET_DDRAM | (u8)(lcd_rowOffset[row - 1] + column - 1));

    return LCD_OK;
}


u8 lcd_sendchar(u8 data)
{
    /* Newline: go to the beginning of the next row */
    if (data == '\n')
    {
        return lcd_movecursor(
            (u8)((lcd_currentRow % LCD_ROWS) + 1), 1);
    }

    /* Row is full */
    if (lcd_currentCol > LCD_COLS)
    {
#if LCD_AUTO_WRAP
        lcd_movecursor(
            (u8)((lcd_currentRow % LCD_ROWS) + 1), 1);
#else
        return LCD_NOK;
#endif
    }

    lcd_write(DIO_u8_HIGH, data);
    lcd_currentCol++;

    return LCD_OK;
}


u8 lcd_sendstring(const u8* str)
{
    if (str == NULL)
    {
        return LCD_NOK;
    }

    while (*str)
    {
        if (lcd_sendchar(*str++) != LCD_OK)
        {
            return LCD_NOK;
        }
    }

    return LCD_OK;
}


u8 lcd_sendnumber(s32 num)
{
    u8  buffer[10];
    u8  i = 0;
    u32 n;

    if (num < 0)
    {
        lcd_sendchar('-');
        n = (u32)(-(num + 1)) + 1u;
    }
    else
    {
        n = (u32)num;
    }

    if (n == 0)
    {
        return lcd_sendchar('0');
    }

    while (n != 0)
    {
        buffer[i++] = (u8)('0' + (n % 10));
        n /= 10;
    }

    while (i > 0)
    {
        lcd_sendchar(buffer[--i]);
    }

    return LCD_OK;
}



void lcd_clearscreen(void)
{
    lcd_sendcmd(LCD_CMD_CLEAR);
}


void lcd_home(void)
{
    lcd_sendcmd(LCD_CMD_HOME);
}


void lcd_display(u8 state)
{
    lcd_sendcmd(state ? LCD_CMD_DISPLAY_ON : LCD_CMD_DISPLAY_OFF);
}


void lcd_cursor(u8 state)
{
    if (state == 0)
        lcd_sendcmd(LCD_CMD_DISPLAY_ON);
    else if (state == 1)
        lcd_sendcmd(LCD_CMD_CURSOR_ON);
    else
        lcd_sendcmd(LCD_CMD_CURSOR_BLINK);
}
