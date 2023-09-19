/*
 * main.c
 *
 *  Created on: Nov 30, 2022
 *      Author: Hazim & Mn3m
 */

#include "../Common/STD_types.h"

#include "../HAL/Clock/Header/Clock_Interface.h"

extern u8 disableIR;
extern u32 IRsignal;
extern u8 updateTime;
extern u8 clockOn;
extern u8 power;
extern u8 mode;

int main(){

	Clock_InitializeClockPosition();
	Clock_Setup();
	while(1){
		if(!disableIR && IRsignal){
			Clock_CheckIRInput();
			IRsignal = 0;
			disableIR = 1;
		}
		else if(updateTime){
			updateTime = 0;
			Clock_CalculateTime();
		}
		if(clockOn && power){//EXTI was triggered by the Hall Effect Sensor
			if(mode == ANALOG){
				Clock_AnalogMode();
			}
			else if(mode == DIGITAL){
				Clock_DigitalMode();
			}
			else{
				Clock_HybridMode();
			}

			Clock_POV();
		}
		else{
			Clock_Reset();
		}
	}
	return 0;
}
