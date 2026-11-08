/*
 *  Created on: Nov 6, 2026
 *      Author: Kirolos
 *
 * keypad driver
 */

#ifndef HAL_KEYPAD_KEYPAD_INTERFACE_H_
#define HAL_KEYPAD_KEYPAD_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"
#include "keypad_config.h"

/* ---------- Return codes ---------- */
#define KEYPAD_OK               0
#define KEYPAD_NOK              1

/* Value returned when no key is pressed (must not be used in the key map) */
#define KEYPAD_NOT_PRESSED           0xFF

/* ---------- API ---------- */

/* Configure the pins. */
u8 keypad_init(void);

/* Raw scan, no debounce: returns the key currently held down,
 * or KEYPAD_NOT_PRESSED. Returns the same key again on every call
 * while it is held. If several keys are down, the first found
 * (lowest row, then lowest column) is returned.               */
u8 keypad_scan(void);

/* Non-blocking, debounced, one event per press: returns the key
 * once when it is pressed, then KEYPAD_NOT_PRESSED until it is released
 * and pressed again. Call it often (main loop).                   */
u8 keypad_read(void);

/* Blocking: waits until a key is pressed and returns it. */
u8 keypad_waitkey(void);

#endif /* HAL_KEYPAD_KEYPAD_INTERFACE_H_ */
