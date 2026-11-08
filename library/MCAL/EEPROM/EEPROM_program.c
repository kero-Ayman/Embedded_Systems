/*
 * EEPROM_program.c
 *
 *  Created on: Oct 29, 2026
 *      Author: Kirolos
 */
#include "../../LIB/BITMATH.h"
#include "../../LIB/STD_TYPES.h"

#include "EEPROM_private.h"
#include "EEPROM_interface.h"



u8 EEPROM_U8_memwrite(u8 data, u16 address)
{


    if (address >= EEPROM_SIZE)
    {
        return EEPROM_NOK;
    }

    /* Wait until any previous write finishes */
    while (GET_BIT(EEPROM_u8_EECR_REG, EEWE) == 1);

    EEPROM_u8_EEARL_REG = (u8)(address);
    EEPROM_u8_EEARH_REG = (u8)(address >> 8);
    EEPROM_u8_EEDR_REG  = data;



   SET_BIT(EEPROM_u8_EECR_REG,EEMWE);                  /* EEWE is 0 here, safe to overwrite */
   SET_BIT(EEPROM_u8_EECR_REG,EEWE);/* start the write */

    while (GET_BIT(EEPROM_u8_EECR_REG, EEWE) == 1);

    return EEPROM_OK;
}

u8 EEPROM_U8_memread(u8 *data, u16 address)
{
    if ((data == 0) || (address >= EEPROM_SIZE))
    {
        return EEPROM_NOK;
    }

    /* A read cannot start while a write is in progress */
    while (GET_BIT(EEPROM_u8_EECR_REG, EEWE) == 1);

    EEPROM_u8_EEARL_REG = (u8)(address);
    EEPROM_u8_EEARH_REG = (u8)(address >> 8);


    SET_BIT(EEPROM_u8_EECR_REG,EERE);

    *data = EEPROM_u8_EEDR_REG;

    return EEPROM_OK;
}

