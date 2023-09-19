/*
 * TI1_Interface.h
 *
 *  Created on: Oct 21, 2022
 *      Author: MoMenBak
 *	   Lecture: Interfacing_Lec
 */

#ifndef MCAL_TIMER1_HEADER_TI1_INTERFACE_H_
#define MCAL_TIMER1_HEADER_TI1_INTERFACE_H_

#include "../../../Common/STD_Types.h"
#include "TI1_Config.h"

#include "TI1_Register.h"
#include "TI1_Private.h"

void ICU_voidInit();

void ICU_voidSelectEdge(u8 Local_Edge);
void ICU_CallBackFunction(void (*PTF) (void));

void ICU_voidResetTimer();
u16 ICU_u16ReadTimer();

void TI1_voidDelayInit(u8 Local_Prescaler);
void TI1_voidSetBusyWait(u32 Copy_u32WaitTimeInMicros);
void TI1_CallBackFunctionCTC(void (*PTF)(void));
void TI1_voidCTCInit(u16 Local_CompareValue, u8 Local_Prescaler);

void __vector_6() __attribute__((signal));
void __vector_7() __attribute__((signal));

#endif /* MCAL_TIMER1_HEADER_TI1_INTERFACE_H_ */
