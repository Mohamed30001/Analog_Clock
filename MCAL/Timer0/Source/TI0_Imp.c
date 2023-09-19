/*
 * TI0_Program.c
 *
 *  Created on: Oct 15, 2022
 *      Author: hisha
 */
#include "../../../Common/STD_types.h"
#include "../../../Common/Bit_Math.h"
#include "../../../Common/Macro.h"

#include "../../DIO/Header/DIO_Interface.h"
#include "../Header/TI0_Interface.h"

u8 CompareValue = 0;

void TI0_voidInitCTC(u8 Local_CompareValue, u8 Local_ActionState , u8 Local_Prescaler ){
	//
	// * select the type (GWM01 -> 1 /GWM00 -> 0 ) CTC mode
	Set_Bit(TI0_TCCR0,TI0_WGM01);
	Clear_Bit(TI0_TCCR0,TI0_WGM00);
	// * Set The Compare value Value In the Register :
	TI0_OCR0= Local_CompareValue;
	// * Select for the action on the OC pin :
	switch(Local_ActionState){
	default:
	case TI0_OCdisconnect:
		Clear_Bit(TI0_TCCR0,TI0_COM00);
		Clear_Bit(TI0_TCCR0,TI0_COM01);
		break;
	case TI0_OCToggle:
		Clear_Bit(TI0_TCCR0,TI0_COM01);
		Set_Bit(TI0_TCCR0,TI0_COM00);
		break;
	case TI0_OCclear:
		Clear_Bit(TI0_TCCR0,TI0_COM00);
		Set_Bit(TI0_TCCR0,TI0_COM01);
		break;
	case TI0_OCset:
		Set_Bit(TI0_TCCR0,TI0_COM00);
		Set_Bit(TI0_TCCR0,TI0_COM01);
		break;
	}
	// * Set the preScaller
	switch (Local_Prescaler){
	case TI0_NoPrescale:
		Set_Bit(TI0_TCCR0,TI0_CS00);
		Clear_Bit(TI0_TCCR0,TI0_CS01);
		Clear_Bit(TI0_TCCR0,TI0_CS02);
		break;
	default:
	case TI0_Prescaler8:
		Clear_Bit(TI0_TCCR0,TI0_CS00);
		Set_Bit(TI0_TCCR0,TI0_CS01);
		Clear_Bit(TI0_TCCR0,TI0_CS02);
		break;
	case TI0_Prescaler64:
		Set_Bit(TI0_TCCR0,TI0_CS00);
		Set_Bit(TI0_TCCR0,TI0_CS01);
		Clear_Bit(TI0_TCCR0,TI0_CS02);
		break;
	case TI0_Prescaler256:
		Clear_Bit(TI0_TCCR0,TI0_CS01);
		Clear_Bit(TI0_TCCR0,TI0_CS00);
		Set_Bit(TI0_TCCR0,TI0_CS02);
		break;
	case TI0_Prescaler1024:
	case TI0_ExternalClkFalling:
	case TI0_ExternalClkRising:
		break;
	}
	// * Enable the Interrupt
	Set_Bit(TI0_TIMSK,TI0_OCIE0);
}

void TI0_voidInitDelay(u8 Local_CompareValue, u8 Local_ActionState , u8 Local_Prescaler ){
	//
	// * select the type (GWM01 -> 1 /GWM00 -> 0 ) CTC mode
	Set_Bit(TI0_TCCR0,TI0_WGM01);
	Clear_Bit(TI0_TCCR0,TI0_WGM00);
	// * Set The Compare value Value In the Register :
	TI0_OCR0= Local_CompareValue;
	CompareValue = Local_CompareValue;
	// * Select for the action on the OC pin :
	switch(Local_ActionState){
	default:
	case TI0_OCdisconnect:
		Clear_Bit(TI0_TCCR0,TI0_COM00);
		Clear_Bit(TI0_TCCR0,TI0_COM01);
		break;
	case TI0_OCToggle:
		Clear_Bit(TI0_TCCR0,TI0_COM01);
		Set_Bit(TI0_TCCR0,TI0_COM00);
		break;
	case TI0_OCclear:
		Clear_Bit(TI0_TCCR0,TI0_COM00);
		Set_Bit(TI0_TCCR0,TI0_COM01);
		break;
	case TI0_OCset:
		Set_Bit(TI0_TCCR0,TI0_COM00);
		Set_Bit(TI0_TCCR0,TI0_COM01);
		break;
	}
	// * Set the preScaller
	switch (Local_Prescaler){
	case TI0_NoPrescale:
		Set_Bit(TI0_TCCR0,TI0_CS00);
		Clear_Bit(TI0_TCCR0,TI0_CS01);
		Clear_Bit(TI0_TCCR0,TI0_CS02);
		break;
	default:
	case TI0_Prescaler8:
		Clear_Bit(TI0_TCCR0,TI0_CS00);
		Set_Bit(TI0_TCCR0,TI0_CS01);
		Clear_Bit(TI0_TCCR0,TI0_CS02);
		break;
	case TI0_Prescaler64:
		Set_Bit(TI0_TCCR0,TI0_CS00);
		Set_Bit(TI0_TCCR0,TI0_CS01);
		Clear_Bit(TI0_TCCR0,TI0_CS02);
		break;
	case TI0_Prescaler256:
		Clear_Bit(TI0_TCCR0,TI0_CS01);
		Clear_Bit(TI0_TCCR0,TI0_CS00);
		Set_Bit(TI0_TCCR0,TI0_CS02);
		break;
	case TI0_Prescaler1024:
	case TI0_ExternalClkFalling:
	case TI0_ExternalClkRising:
		break;
	}
	// * Enable the Interrupt
	Set_Bit(TI0_TIFR,TI0_OCF0);
}

void TI0_voidDeinit(){
	//No prescaler clock
	Clear_Bit(TI0_TCCR0,TI0_CS01);
	Clear_Bit(TI0_TCCR0,TI0_CS00);
	Clear_Bit(TI0_TCCR0,TI0_CS02);
}

static void (*GPTF_CTC) (void) = NULL;

void TI0_CallBackFunctionCTC(void (*PTF)(void)){
	if (PTF != NULL){
		GPTF_CTC = PTF ;
	}
}
//
////CTC Mode Interrupt

void __vector_10(void){
	if(GPTF_CTC != NULL){
		GPTF_CTC();
	}
}

void TI0_voidSetBusyWait(u32 Copy_u32WaitTimeInMicros, u8* delayBreak){
	u32 Local_u32Counter = 0;
	while(Local_u32Counter < Copy_u32WaitTimeInMicros){
		if(GET_BIT(TI0_TIFR,TI0_OCF0)){
			Local_u32Counter += CompareValue;
			SET_BIT(TI0_TIFR,TI0_OCF0);
		}
		if(*delayBreak){
			return;
		}
	}
}
