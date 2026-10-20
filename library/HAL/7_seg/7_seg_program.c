#include "../../LIB/BITMATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "7_seg_interface.h"

u8 s_seg_port;

void s_seg_init(u8 Copy_u8PortId)
{
    u8 i;
    s_seg_port = Copy_u8PortId;

    for(i = 0; i < 7; i++)
    {
        DIO_u8SetPinDirection(Copy_u8PortId, i, DIO_u8_OUTPUT);
    }
}

void s_seg_print_num(u8 num)
{
    u8 i;

    /* Turn off all segments to clear the previous number */
    for(i = 0; i < 7; i++)
    {
        DIO_u8SetPinValue(s_seg_port, i, DIO_u8_LOW);
    }

    switch (num)
    {
    case 0:
        DIO_u8SetPinValue(s_seg_port, 0, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 1, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 2, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 3, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 4, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 5, DIO_u8_HIGH);
        break;

    case 1:
        DIO_u8SetPinValue(s_seg_port, 1, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 2, DIO_u8_HIGH);
        break;

    case 2:
        DIO_u8SetPinValue(s_seg_port, 0, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 1, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 3, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 4, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 6, DIO_u8_HIGH);
        break;

    case 3:
        DIO_u8SetPinValue(s_seg_port, 0, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 1, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 2, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 3, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 6, DIO_u8_HIGH);
        break;

    case 4:
        DIO_u8SetPinValue(s_seg_port, 1, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 2, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 5, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 6, DIO_u8_HIGH);
        break;

    case 5:
        DIO_u8SetPinValue(s_seg_port, 0, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 2, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 3, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 5, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 6, DIO_u8_HIGH);
        break;

    case 6:
        DIO_u8SetPinValue(s_seg_port, 2, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 3, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 4, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 5, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 6, DIO_u8_HIGH);
        break;

    case 7:
        DIO_u8SetPinValue(s_seg_port, 0, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 1, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 2, DIO_u8_HIGH);
        break;

    case 8:
        DIO_u8SetPinValue(s_seg_port, 0, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 1, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 2, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 3, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 4, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 5, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 6, DIO_u8_HIGH);
        break;

    case 9:
        DIO_u8SetPinValue(s_seg_port, 0, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 1, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 2, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 5, DIO_u8_HIGH);
        DIO_u8SetPinValue(s_seg_port, 6, DIO_u8_HIGH);
        break;
    }
}
