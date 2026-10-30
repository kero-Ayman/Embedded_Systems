/*
 * EEPROM_interface.h
 *
 *  Created on: Oct 29, 2026
 *      Author: Kirolos
 */

#ifndef MCAL_EEPROM_EEPROM_INTERFACE_H_
#define MCAL_EEPROM_EEPROM_INTERFACE_H_

#define EEPROM_OK 1
#define EEPROM_NOK 0


u8 EEPROM_U8_memwrite(u8 data, u16 address);
u8 EEPROM_U8_memread(u8 *data, u16 address);


#endif /* MCAL_EEPROM_EEPROM_INTERFACE_H_ */
