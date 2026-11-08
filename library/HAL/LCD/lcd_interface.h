/*
 * lcd_interface.h
 *
 *  Created on: Nov 4, 2026
 *      Author: Kirolos
 *
 *  HD44780 character LCD driver (8-bit mode).
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_

#include "lcd_config.h"

/* ---------- Return codes ---------- */
#define LCD_OK              0
#define LCD_NOK             1

/* ---------- Commands ---------- */
#define LCD_CMD_CLEAR           0x01
#define LCD_CMD_HOME            0x02
#define LCD_CMD_ENTRY_INC       0x06
#define LCD_CMD_DISPLAY_OFF     0x08
#define LCD_CMD_DISPLAY_ON      0x0C    /* display on, cursor off          */
#define LCD_CMD_CURSOR_ON       0x0E    /* display on, cursor on           */
#define LCD_CMD_CURSOR_BLINK    0x0F    /* display on, cursor on, blinking */
#define LCD_CMD_FUNCTION_RESET  0x30    /* used in the init sequence       */
#define LCD_CMD_FUNCTION_8BIT   0x38    /* 8-bit, 2 lines, 5x8 font        */
#define LCD_CMD_SET_CGRAM       0x40
#define LCD_CMD_SET_DDRAM       0x80

/* ---------- API ---------- */
u8   lcd_init(void);
u8   lcd_sendcmd(u8 cmd);
u8   lcd_sendchar(u8 data);
u8   lcd_sendstring(const u8* str);
u8   lcd_sendnumber(s32 num);
u8   lcd_movecursor(u8 row, u8 column);

void lcd_clearscreen(void);
void lcd_home(void);
void lcd_display(u8 state);        /* 1 = on, 0 = off          */
void lcd_cursor(u8 state);         /* 0 = off, 1 = on, 2 = blink */

#endif /* HAL_LCD_LCD_INTERFACE_H_ */

