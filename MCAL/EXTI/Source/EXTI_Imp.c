#include "../../../Common/Bit_Math.h"
#include "../../../Common/Macro.h"
#include "../../../Common/STD_types.h"

#include "../../DIO/Header/DIO_Interface.h"

#include "../Header/EXTI_Interface.h"
#include "../../GIE/Header/GIE_All.h"


void EXTI_voidInit0(u8 Local_Sense){
	DIO_u8SetPinDir(EXTI_GROUP1,EXTI_PinINT0,Input);
	DIO_u8SetPinValue(EXTI_GROUP1,EXTI_PinINT0,High);

	switch(Local_Sense){
	case EXTI_LowLevel:
		Clear_Bit(EXTI_MCUCR,EXTI_ISC00);
		Clear_Bit(EXTI_MCUCR,EXTI_ISC01);
		break;
	case EXTI_AnyChange:
		Set_Bit(EXTI_MCUCR,EXTI_ISC00);
		Clear_Bit(EXTI_MCUCR,EXTI_ISC01);
		break;
	case EXTI_Falling:
		Clear_Bit(EXTI_MCUCR,EXTI_ISC00);
		Set_Bit(EXTI_MCUCR,EXTI_ISC01);
		break;
	case EXTI_Rising:
		Set_Bit(EXTI_MCUCR,EXTI_ISC00);
		Set_Bit(EXTI_MCUCR,EXTI_ISC01);
		break;
	}

	GIE_voidEN();
	Set_Bit(EXTI_GICR,EXTI_INT0);
}

void EXTI_voidDeinit0(){
	Clear_Bit(EXTI_GICR,EXTI_INT0);
}
void EXTI_voidInit1(u8 Local_Sense){
	DIO_u8SetPinDir(EXTI_GROUP1,EXTI_PinINT1,Input);

	switch(Local_Sense){
	case EXTI_LowLevel:
		Clear_Bit(EXTI_MCUCR,EXTI_ISC10);
		Clear_Bit(EXTI_MCUCR,EXTI_ISC11);
		break;
	case EXTI_AnyChange:
		Set_Bit(EXTI_MCUCR,EXTI_ISC10);
		Clear_Bit(EXTI_MCUCR,EXTI_ISC11);
		break;
	case EXTI_Falling:
		Clear_Bit(EXTI_MCUCR,EXTI_ISC10);
		Set_Bit(EXTI_MCUCR,EXTI_ISC11);
		break;
	case EXTI_Rising:
		Set_Bit(EXTI_MCUCR,EXTI_ISC10);
		Set_Bit(EXTI_MCUCR,EXTI_ISC11);
		break;
	}

	GIE_voidEN();
	Set_Bit(EXTI_GICR,EXTI_INT1);
}

void EXTI_voidInit2(u8 Local_Sense){
	DIO_u8SetPinDir(EXTI_GROUP2,EXTI_PinINT2,Input);

	switch(Local_Sense){
	case EXTI_Falling:
		Clear_Bit(EXTI_MCUCSR,EXTI_ISC2);
		break;
	case EXTI_Rising:
		Set_Bit(EXTI_MCUCSR,EXTI_ISC2);
		break;
	}

	GIE_voidEN();
	Set_Bit(EXTI_GICR,EXTI_INT2);
}

static void (*GPTF_INT0) (void) = NULL;
void EXTI_CallBackFunction(void (*PTF) (void)){
	if (PTF!=NULL){
		GPTF_INT0 = PTF ;
	}
}

void __vector_1(void) __attribute__((signal));
void __vector_1(void){
	if(GPTF_INT0 != NULL){
		GPTF_INT0();
	}
}

