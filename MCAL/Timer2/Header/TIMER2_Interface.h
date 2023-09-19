
#ifndef MCAL_TIMER2_HEADER_TIMER2_INTERFACE_H_
#define MCAL_TIMER2_HEADER_TIMER2_INTERFACE_H_

#include "TIMER2_Private.h"
#include "TIMER2_Config.h"
#include "TIMER2_Register.h"


void TI2_voidInit(u8 Local_CompareValue);
void TI2_voidDeInit();
void TI2_voidSetBusyWait(u16 Copy_u8WaitTime);

void TI2_CallBackFunctionCTC(void (*PTF)(void));

void __vector_4(void) __attribute__((signal));

#endif /* MCAL_TIMER2_HEADER_TIMER2_INTERFACE_H_ */
