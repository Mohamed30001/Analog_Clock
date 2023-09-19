/*
 * EXTI_Interface.h
 *
 *  Created on: Oct 7, 2022
 *      Author: aweso
 */

#ifndef MCAL_EXTI_HEADER_EXTI_INTERFACE_H_
#define MCAL_EXTI_HEADER_EXTI_INTERFACE_H_

#include "EXTI_Private.h"
#include "EXTI_Register.h"

void EXTI_voidInit0(u8 Local_Sense);
void EXTI_voidInit1(u8 Local_Sense);
void EXTI_voidInit2(u8 Local_Sense);
void EXTI_CallBackFunction(void (*PTF) (void));
void EXTI_voidDeinit0();


#endif /* MCAL_EXTI_HEADER_EXTI_INTERFACE_H_ */
