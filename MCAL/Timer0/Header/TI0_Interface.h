/*
 * TI0_Interface.h
 *
 *  Created on: Oct 15, 2022
 *      Author: hisha
 */

#ifndef MCAL_TIMER0_HEADER_TI0_INTERFACE_H_
#define MCAL_TIMER0_HEADER_TI0_INTERFACE_H_
#include "TI0_Register.h"
#include "TI0_Private.h"
#include "TI0_Config.h"

void TI0_voidInitCTC(u8 Local_CompareValue, u8 Local_ActionState, u8 Local_Prescaler);

void TI0_voidDeinit();

void TI0_CallBackFunctionCTC(void (*PTF)(void));
void TI0_voidSetBusyWait(u32 Copy_u32WaitTimeInMicros, u8* delayBreak);
void TI0_voidInitDelay(u8 Local_CompareValue, u8 Local_ActionState, u8 Local_Prescaler);

void __vector_10(void)		__attribute__((signal));

#endif /* MCAL_TIMER0_HEADER_TI0_INTERFACE_H_ */
