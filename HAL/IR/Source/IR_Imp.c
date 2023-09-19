/*
 * IR_Imp.c
 *
 *  Created on: Dec 3, 2022
 *      Author: Hazim
 */
#include "../../../Common/Bit_Math.h"
#include "../../../Common/Macro.h"
#include "../../../Common/STD_types.h"

#include "../../../MCAL/Timer1/Header/TI1_Interface.h"
//#include "../../LCD4/Header/LCD4_Interface.h"
#include "../Header/IR_Interface.h"

//#include "../../../MCAL/GIE/Header/GIE_All.h"

static u32 number = 0;
extern u32 IRsignal;
extern u8 disableIR;
void IR_voidInit(){
	//LCD4_voidInit();
	ICU_CallBackFunction(IR_voidReadSignal);
	ICU_voidInit();
	//GIE_voidEN();
}

void IR_voidReadSignal(){
	if(!disableIR){
		u16 period = 0;
		static s8 Local_BitCounter = -1;
		if(Local_BitCounter == -1){
			Local_BitCounter++;
			TI1_TCNT1 = 0;
		}
		else{
#if F_CPU >= 16000000
			period = ICU_u16ReadTimer() * 2;
#elif F_CPU >= 8000000
			period = ICU_u16ReadTimer();
#endif
			ICU_voidResetTimer();

			if(period > 4000){
				//Start burst or repeat burst
			}

			else if(period < 2400 && period > 1800){
				//Logic 1
				number=(number<<1) | 1;
				Local_BitCounter++;
			}

			else if(period <1300 && period > 700){
				//Logic 0
				number<<=1;
				Local_BitCounter++;
			}

			if(Local_BitCounter == 32){
				Local_BitCounter = -1;
				IRsignal = number;
				//			LCD4_voidWriteCommand(LCD4_ClearDisplay);
				//			LCD4_voidWriteIntData(number);
			}
		}
	}
}
