/*
 * interrupt_private.h
 *
 *  Created on: Oct 31, 2026
 *      Author: Kirolos
 */

#ifndef MCAL_INTERRUPT_INTERRUPT_PRIVATE_H_
#define MCAL_INTERRUPT_INTERRUPT_PRIVATE_H_

/* ---------------- Registers (ATmega32) ---------------- */
#define SREG        (*((volatile u8 *)0x5F))
#define GICR        (*((volatile u8 *)0x5B))
#define GIFR        (*((volatile u8 *)0x5A))
#define MCUCR       (*((volatile u8 *)0x55))
#define MCUCSR      (*((volatile u8 *)0x54))

/* ---------------- SREG ---------------- */
#define SREG_I      7

/* ---------------- MCUCR: sense control for INT0 / INT1 ---------------- */
#define ISC00       0
#define ISC01       1
#define ISC10       2
#define ISC11       3

/* ---------------- MCUCSR: sense control for INT2 ---------------- */
#define ISC2        6

/* ---------------- GICR: interrupt enable bits ---------------- */
#define GICR_INT0   6
#define GICR_INT1   7
#define GICR_INT2   5

/* ---------------- GIFR: interrupt flag bits ---------------- */
#define GIFR_INTF0  6
#define GIFR_INTF1  7
#define GIFR_INTF2  5

/* Sense mode mask (2 bits for INT0/INT1) */
#define SENSE_MASK  0x03

#endif /* MCAL_INTERRUPT_INTERRUPT_PRIVATE_H_ */
