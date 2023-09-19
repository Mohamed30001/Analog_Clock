/*
 * TI1_Program.c
 *
 *  Created on: Oct 21, 2022
 *      Author: MoMenBak
 *	   Lecture: Interfacing_Lec
 */

#include "../../../Common/STD_Types.h"
#include "../../../Common/Bit_Math.h"
#include "../../../Common/Macro.h"

#include "../Header/TI1_Interface.h"
#include "../../DIO/Header/DIO_Interface.h"

void ICU_voidSelectEdge(u8 Local_Edge){
	switch(Local_Edge){
	case TI1_Falling:
		Clear_Bit(TI1_TCCR1B,TI1_ICES1);
		break;
	case TI1_Rising:
		Set_Bit(TI1_TCCR1B,TI1_ICES1);
		break;
	}
}

void ICU_voidInit(){

	DIO_u8SetPinDir(DIO_GroupD,DIO_PIN6,Input);
	//Normal Mode
	Clear_Bit(TI1_TCCR1A,TI1_WGM10);
	Clear_Bit(TI1_TCCR1A,TI1_WGM11);
	Clear_Bit(TI1_TCCR1B,TI1_WGM12);
	Clear_Bit(TI1_TCCR1B,TI1_WGM13);

	Set_Bit(TI1_TIMSK,TI1_TICIE1);
	ICU_voidSelectEdge(TI1_Rising);

	//Prescaler 8
	Clear_Bit(TI1_TCCR1B,TI1_CS10);
	Set_Bit(TI1_TCCR1B,TI1_CS11);
	Clear_Bit(TI1_TCCR1B,TI1_CS12);
}

static void (*GPTF_ICU) (void) = NULL;

void ICU_CallBackFunction(void (*PTF) (void)){
	if (PTF!=NULL){
		GPTF_ICU = PTF ;
	}
}

void __vector_6(){

	if(GPTF_ICU != NULL){
		GPTF_ICU();
	}
}

void ICU_voidResetTimer(){
	TI1_TCNT1 = 0;
}

u16 ICU_u16ReadTimer(){
	return TI1_ICR1;
}

void TI1_voidDelayInit(u8 Local_Prescaler){

	//Select the Mode -> CTC:
	Clear_Bit(TI1_TCCR1A,TI1_WGM10);
	Clear_Bit(TI1_TCCR1A,TI1_WGM11);
	Set_Bit(TI1_TCCR1B,TI1_WGM12);
	Clear_Bit(TI1_TCCR1B,TI1_WGM13);

	TI1_OCR1A = 50000;

	//Select the Prescaler
	switch (Local_Prescaler)
	{
	case TI1_NoPrescale:
		Set_Bit(TI1_TCCR1B,TI1_CS10);
		Clear_Bit(TI1_TCCR1B,TI1_CS11);
		Clear_Bit(TI1_TCCR1B,TI1_CS12);
		break;
	default:
	case TI1_Prescaler8:
		Clear_Bit(TI1_TCCR1B,TI1_CS10);
		Set_Bit(TI1_TCCR1B,TI1_CS11);
		Clear_Bit(TI1_TCCR1B,TI1_CS12);
		break;
	case TI1_Prescaler64:
		Set_Bit(TI1_TCCR1B,TI1_CS10);
		Set_Bit(TI1_TCCR1B,TI1_CS11);
		Clear_Bit(TI1_TCCR1B,TI1_CS12);
		break;
	case TI1_Prescaler256:
		Clear_Bit(TI1_TCCR1B,TI1_CS10);
		Clear_Bit(TI1_TCCR1B,TI1_CS11);
		Set_Bit(TI1_TCCR1B,TI1_CS12);
		break;
	case TI1_Prescaler1024:
		Set_Bit(TI1_TCCR1B,TI1_CS10);
		Clear_Bit(TI1_TCCR1B,TI1_CS11);
		Set_Bit(TI1_TCCR1B,TI1_CS12);
		break;
	case TI1_ExternalClkFalling:
	case TI1_ExternalClkRising:
		break;

	}
	SET_BIT(TI1_TIFR,TI1_OCF1A); //Interrupt Enable
}

void TI1_voidCTCInit(u16 Local_CompareValue, u8 Local_Prescaler){

	//Select the Mode -> CTC:
	Clear_Bit(TI1_TCCR1A,TI1_WGM10);
	Clear_Bit(TI1_TCCR1A,TI1_WGM11);
	Set_Bit(TI1_TCCR1B,TI1_WGM12);
	Clear_Bit(TI1_TCCR1B,TI1_WGM13);

	TI1_OCR1A = Local_CompareValue;

	//Select the Prescaler
	switch (Local_Prescaler)
	{
	case TI1_NoPrescale:
		Set_Bit(TI1_TCCR1B,TI1_CS10);
		Clear_Bit(TI1_TCCR1B,TI1_CS11);
		Clear_Bit(TI1_TCCR1B,TI1_CS12);
		break;
	default:
	case TI1_Prescaler8:
		Clear_Bit(TI1_TCCR1B,TI1_CS10);
		Set_Bit(TI1_TCCR1B,TI1_CS11);
		Clear_Bit(TI1_TCCR1B,TI1_CS12);
		break;
	case TI1_Prescaler64:
		Set_Bit(TI1_TCCR1B,TI1_CS10);
		Set_Bit(TI1_TCCR1B,TI1_CS11);
		Clear_Bit(TI1_TCCR1B,TI1_CS12);
		break;
	case TI1_Prescaler256:
		Clear_Bit(TI1_TCCR1B,TI1_CS10);
		Clear_Bit(TI1_TCCR1B,TI1_CS11);
		Set_Bit(TI1_TCCR1B,TI1_CS12);
		break;
	case TI1_Prescaler1024:
		Set_Bit(TI1_TCCR1B,TI1_CS10);
		Clear_Bit(TI1_TCCR1B,TI1_CS11);
		Set_Bit(TI1_TCCR1B,TI1_CS12);
		break;
	case TI1_ExternalClkFalling:
	case TI1_ExternalClkRising:
		break;

	}
	SET_BIT(TI1_TIMSK,TI1_OCIE1A); //Interrupt Enable
}

void TI1_voidSetBusyWait(u32 Copy_u32WaitTimeInMicros){
	u32 Local_u32Counter = 0;
	while(Local_u32Counter < Copy_u32WaitTimeInMicros){
		if(GET_BIT(TI1_TIFR,TI1_OCF1A)){
			Local_u32Counter += 50;
			SET_BIT(TI1_TIFR,TI1_OCF1A);
		}
	}
}

static void (*GPTF_CTC) (void) = NULL;
void TI1_CallBackFunctionCTC(void (*PTF)(void))
{
	if (PTF != NULL)
	{
		GPTF_CTC = PTF ;
	}
}

void __vector_7(void)
{
	if(GPTF_CTC != NULL){
		GPTF_CTC();
	}
}
