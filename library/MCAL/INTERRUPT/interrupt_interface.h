/*
 * interrupt_interface.h
 *
 *  Created on: Oct 31, 2026
 *      Author: Kirolos
 */

#ifndef MCAL_INTERRUPT_INTERRUPT_INTERFACE_H_
#define MCAL_INTERRUPT_INTERRUPT_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

/* External interrupt lines */
#define EXTI_0          0
#define EXTI_1          1
#define EXTI_2          2

/* Sense control modes (values match the datasheet ISCx1:ISCx0 encoding) */
#define INT_LOW_LEVEL   0
#define INT_TOGGLE      1
#define INT_FALLING     2
#define INT_RISING      3

/* Return states */
#define INT_OK          0
#define INT_NOK         1

/* Global interrupt (SREG I-bit) */
void INT_voidEnableGlobal(void);
void INT_voidDisableGlobal(void);

/* Configure the trigger mode and enable one external interrupt line.*/
u8 INT_u8Enable(u8 Copy_u8Line, u8 Copy_u8Mode);

/* Disable one external interrupt line */
u8 INT_u8Disable(u8 Copy_u8Line);

/* Register the function to be called when the line fires */
u8 INT_u8SetCallBack(u8 Copy_u8Line, void (*Copy_pvFunc)(void));

#endif /* MCAL_INTERRUPT_INTERRUPT_INTERFACE_H_ */
