#include "../../../Common/STD_types.h"
#include "../../../Common/Bit_Math.h"
#include "../../../Common/Macro.h"

#include "../Header/TIMER2_Interface.h"

void TI2_voidInit(u8 Local_CompareValue){
	CLR_BIT(TI2_TCCR2, TI2_WGM20);
	SET_BIT(TI2_TCCR2, TI2_WGM21);


	/*Set compare match value to 200*/
	TI2_OCR2=Local_CompareValue;

	/*Set PRESCALAR 256*/
	CLR_BIT(TI2_TCCR2, TI2_CS20);
	SET_BIT(TI2_TCCR2, TI2_CS21);
	SET_BIT(TI2_TCCR2, TI2_CS22);

	/*OUTPUT COMPARE MATCH INTERRUPT ENABLE*/
	SET_BIT(TI2_TIMSK,TI2_OCIE2);
}

void TI2_voidDeInit(){
	CLR_BIT(TI2_TCCR2, TI2_CS20);
	CLR_BIT(TI2_TCCR2, TI2_CS21);
	CLR_BIT(TI2_TCCR2, TI2_CS22);
	/*OUTPUT COMPARE MATCH INTERRUPT DISABLE*/
	CLR_BIT(TI2_TIMSK,TI2_OCIE2);
	TI2_TCNT2 = 0;
}


void TI2_voidSetBusyWait(u16 Copy_u8WaitTime){
	u16 Local_u8Counter = 0;
	u8 counter = 0;
	while(Local_u8Counter != Copy_u8WaitTime){
		if(GET_BIT(TI2_TIFR,TI2_OCF2)){
			counter++;
			SET_BIT(TI2_TIFR,TI2_OCF2);
		}
		if(counter == 4){
			Local_u8Counter++;
			counter = 0;
		}
	}
}

static void (*GPTF_CTC) (void) = NULL;

void TI2_CallBackFunctionCTC(void (*PTF)(void)){
	if (PTF != NULL){
		GPTF_CTC = PTF ;
	}
}

//CTC Mode Interrupt

void __vector_4(void){
	if(GPTF_CTC != NULL){
		GPTF_CTC();
	}
}
