/*
 * keypad_config.h
 *
 *  Created on: Nov 6, 2026
 *      Author: Kirolos
 *
 *  Wiring, size and key map of the keypad. Edit only this file when
 *  the wiring or the keypad layout changes.
 *
 *  Scan method: rows are outputs (driven LOW one at a time), columns are
 *  inputs with internal pull-ups. A pressed key reads LOW on its column.
 */

#ifndef HAL_KEYPAD_KEYPAD_CONFIG_H_
#define HAL_KEYPAD_KEYPAD_CONFIG_H_

/* ---------- Size ---------- */
#define KEYPAD_ROWS             4
#define KEYPAD_COLS             4

/* ---------- Wiring ---------- */
#define KEYPAD_ROW_PORT         DIO_u8_PORTD
#define KEYPAD_COL_PORT         DIO_u8_PORTD

/* One entry per row / column, in the same order as the key map below */
#define KEYPAD_ROW_PINS         { DIO_u8_PIN0, DIO_u8_PIN1, DIO_u8_PIN2, DIO_u8_PIN3 }
#define KEYPAD_COL_PINS         { DIO_u8_PIN4, DIO_u8_PIN5, DIO_u8_PIN6, DIO_u8_PIN7 }

/* ---------- Key map [row][column] ---------- */
#define KEYPAD_KEYMAP           { {'7','8','9','A'}, \
                                  {'4','5','6','B'}, \
                                  {'1','2','3','C'}, \
                                  {'c','0','=','D'} }

/* ---------- Timing ---------- */
#define KEYPAD_SETTLE_US        10      /* wait after driving a row before reading the columns */
#define KEYPAD_DEBOUNCE_MS      20      /* contact bounce time */

#endif /* HAL_KEYPAD_KEYPAD_CONFIG_H_ */
