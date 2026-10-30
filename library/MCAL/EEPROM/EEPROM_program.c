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

#include <avr/io.h>          /* EECR, SREG, EERE, EEWE, EEMWE (I/O-address versions) */
#include <avr/interrupt.h>   /* cli() */

u8 EEPROM_U8_memwrite(u8 data, u16 address)
{
    u8 Local_u8Sreg;

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

    EECR |= (1 << EERE);                  /* start read */

    *data = EEPROM_u8_EEDR_REG;

    return EEPROM_OK;
}

u8 EEPROM_U8_memwriteBlock(const u8 *data, u16 address, u16 length)
{
    u16 Local_u16Counter;

    if ((data == 0) || (length == 0) ||
        (address >= EEPROM_SIZE) || (length > (EEPROM_SIZE - address)))
    {
        return EEPROM_NOK;
    }

    for (Local_u16Counter = 0; Local_u16Counter < length; Local_u16Counter++)
    {
        EEPROM_U8_memwrite(data[Local_u16Counter], address + Local_u16Counter);
    }

    return EEPROM_OK;
}

u8 EEPROM_U8_memreadBlock(u8 *data, u16 address, u16 length)
{
    u16 Local_u16Counter;

    if ((data == 0) || (length == 0) ||
        (address >= EEPROM_SIZE) || (length > (EEPROM_SIZE - address)))
    {
        return EEPROM_NOK;
    }

    for (Local_u16Counter = 0; Local_u16Counter < length; Local_u16Counter++)
    {
        EEPROM_U8_memread(&data[Local_u16Counter], address + Local_u16Counter);
    }

    return EEPROM_OK;
}
