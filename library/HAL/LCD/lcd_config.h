/*
 * lcd_config.h
 *
 *  Created on: Nov 4, 2026
 *      Author: Kirolos
 *
 *  Hardware wiring and display size. Edit only this file when
 *  the wiring or the LCD type changes.
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_

/* ---------- Wiring (8-bit mode) ---------- */
#define LCD_DATA_PORT       DIO_u8_PORTA
#define LCD_CONTROL_PORT    DIO_u8_PORTB

#define LCD_RS_PIN          DIO_u8_PIN0
#define LCD_ENABLE_PIN      DIO_u8_PIN1
#define LCD_RW_PIN          DIO_u8_PIN2

/* ---------- Display size ---------- */
#define LCD_ROWS            2
#define LCD_COLS            16

/* ---------- Behaviour ---------- */
/* 1: when a row is full, continue on the next row (after the last row
 *    it wraps back to row 0).
 * 0: characters beyond the last column are rejected (LCD_NOK).        */
#define LCD_AUTO_WRAP       1

#endif /* HAL_LCD_LCD_CONFIG_H_ */

