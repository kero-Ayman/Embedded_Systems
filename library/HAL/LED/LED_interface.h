/*
 * LED_interface.h
 *
 *  Created on: Oct 12, 2026
 *      Author: Kirolos
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

u8 LED_u8_LED_ON(u8 Port,u8 pin_number);
u8 LED_u8_LED_Off(u8 Port,u8 pin_number);
u8 LED_u8_LED_toggle(u8 Port,u8 pin_number);

#endif /* HAL_LED_LED_INTERFACE_H_ */
