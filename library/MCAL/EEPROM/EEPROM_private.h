/*
 * EEPROM_private.h
 *
 *  Created on: Oct 29, 2026
 *      Author: Kirolos
 */

#ifndef MCAL_EEPROM_EEPROM_PRIVATE_H_
#define MCAL_EEPROM_EEPROM_PRIVATE_H_

/* EEPROM registers (ATmega32), data-space addresses */
#define EEPROM_u8_EEARH_REG     (*((volatile u8 *)0x3F))
#define EEPROM_u8_EEARL_REG     (*((volatile u8 *)0x3E))
#define EEPROM_u8_EEDR_REG      (*((volatile u8 *)0x3D))
#define EEPROM_u8_EECR_REG      (*((volatile u8 *)0x3C))

/* Memory size in bytes (ATmega32 = 1024) */
#define EEPROM_SIZE             1024U

#define EERE                         0
#define EEWE                         1
#define EEMWE                        2
#define EERIE                        3

#endif /* MCAL_EEPROM_EEPROM_PRIVATE_H_ */
