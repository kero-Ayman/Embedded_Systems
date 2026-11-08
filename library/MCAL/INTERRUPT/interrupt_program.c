/*
 * interrupt_program.c
 *
 *  Created on: Oct 31, 2026
 *      Author: Kirolos
 */


#include "../../LIB/BITMATH.h"
#include "../../LIB/STD_TYPES.h"

#include "interrupt_private.h"
#include "interrupt_interface.h"



#define INT_LINES_NUM   3

/* One callback per external interrupt line */
static void (*INT_pvCallBack[INT_LINES_NUM])(void) = {NULL, NULL, NULL};

/* ------------------------------------------------------------------ */

void INT_voidEnableGlobal(void)
{
	SET_BIT(SREG, SREG_I);
}

void INT_voidDisableGlobal(void)
{
	CLR_BIT(SREG, SREG_I);
}

/* ------------------------------------------------------------------ */

u8 INT_u8Enable(u8 Copy_u8Line, u8 Copy_u8Mode)
{
	u8 Local_u8ErrorState = INT_OK;

	switch (Copy_u8Line)
	{
	case EXTI_0:
		if (Copy_u8Mode <= INT_RISING)
		{
			CLR_BIT(GICR, GICR_INT0);                       /* disable while changing mode */
			MCUCR = (MCUCR & ~(SENSE_MASK << ISC00)) | (Copy_u8Mode << ISC00);
			SET_BIT(GIFR, GIFR_INTF0);                      /* clear stale flag (write 1)  */
			SET_BIT(GICR, GICR_INT0);                       /* enable                      */
		}
		else
		{
			Local_u8ErrorState = INT_NOK;
		}
		break;

	case EXTI_1:
		if (Copy_u8Mode <= INT_RISING)
		{
			CLR_BIT(GICR, GICR_INT1);
			MCUCR = (MCUCR & ~(SENSE_MASK << ISC10)) | (Copy_u8Mode << ISC10);
			SET_BIT(GIFR, GIFR_INTF1);
			SET_BIT(GICR, GICR_INT1);
		}
		else
		{
			Local_u8ErrorState = INT_NOK;
		}
		break;

	case EXTI_2:
		/* ISC2: 0 = falling edge, 1 = rising edge */
		if ((Copy_u8Mode == INT_FALLING) || (Copy_u8Mode == INT_RISING))
		{
			CLR_BIT(GICR, GICR_INT2);
			if (Copy_u8Mode == INT_RISING)
			{
				SET_BIT(MCUCSR, ISC2);
			}
			else
			{
				CLR_BIT(MCUCSR, ISC2);
			}
			SET_BIT(GIFR, GIFR_INTF2);
			SET_BIT(GICR, GICR_INT2);
		}
		else
		{
			Local_u8ErrorState = INT_NOK;
		}
		break;

	default:
		Local_u8ErrorState = INT_NOK;
		break;
	}

	return Local_u8ErrorState;
}

/* ------------------------------------------------------------------ */

u8 INT_u8Disable(u8 Copy_u8Line)
{
	u8 Local_u8ErrorState = INT_OK;

	switch (Copy_u8Line)
	{
	case EXTI_0: CLR_BIT(GICR, GICR_INT0); break;
	case EXTI_1: CLR_BIT(GICR, GICR_INT1); break;
	case EXTI_2: CLR_BIT(GICR, GICR_INT2); break;
	default:     Local_u8ErrorState = INT_NOK; break;
	}

	return Local_u8ErrorState;
}

/* ------------------------------------------------------------------ */

u8 INT_u8SetCallBack(u8 Copy_u8Line, void (*Copy_pvFunc)(void))
{
	u8 Local_u8ErrorState = INT_OK;

	if ((Copy_u8Line < INT_LINES_NUM) && (Copy_pvFunc != NULL))
	{
		INT_pvCallBack[Copy_u8Line] = Copy_pvFunc;
	}
	else
	{
		Local_u8ErrorState = INT_NOK;
	}

	return Local_u8ErrorState;
}

/* ------------------------------------------------------------------ */
/* ISRs - ATmega32 vector numbers: INT0 = 1, INT1 = 2, INT2 = 3        */

void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	if (INT_pvCallBack[EXTI_0] != NULL)
	{
		INT_pvCallBack[EXTI_0]();
	}
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if (INT_pvCallBack[EXTI_1] != NULL)
	{
		INT_pvCallBack[EXTI_1]();
	}
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if (INT_pvCallBack[EXTI_2] != NULL)
	{
		INT_pvCallBack[EXTI_2]();
	}
}
