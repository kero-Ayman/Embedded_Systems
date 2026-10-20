#include "../../LIB/BITMATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "LED_interface.h"

u8 LED_u8_LED_ON(u8 Port, u8 pin_number)
{
    DIO_u8SetPinDirection(Port, pin_number, DIO_u8_OUTPUT);
    DIO_u8SetPinValue(Port, pin_number, DIO_u8_HIGH);

    return 1;
}

u8 LED_u8_LED_Off(u8 Port, u8 pin_number)
{
    DIO_u8SetPinDirection(Port, pin_number, DIO_u8_OUTPUT);
    DIO_u8SetPinValue(Port, pin_number, DIO_u8_LOW);

    return 1;
}

u8 LED_u8_LED_toggle(u8 Port, u8 pin_number)
{
    u8 LED_value = DIO_u8_LOW;

    DIO_u8SetPinDirection(Port, pin_number, DIO_u8_OUTPUT);
    DIO_u8GetPinValue(Port, pin_number, &LED_value);

    if (LED_value == DIO_u8_HIGH)
    {
        DIO_u8SetPinValue(Port, pin_number, DIO_u8_LOW);
    }
    else
    {
        DIO_u8SetPinValue(Port, pin_number, DIO_u8_HIGH);
    }

    return 1;
}
