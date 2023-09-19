#ifndef HAL_CLOCK_HEADER_CLOCK_INTERFACE_H_
#define HAL_CLOCK_HEADER_CLOCK_INTERFACE_H_

#include "Clock_Private.h"

typedef enum{
	ANALOG,
	DIGITAL,
	HYBRID
}MODES_EN;

#define STARTING_SECONDS 	0
#define STARTING_MINUTES  	0
#define STARTING_HOURS 	  	12
#define STARTING_POINT	  	175

#define LED_DELAY			180

void Clock_InitializeClockPosition();
void Clock_Setup();
void Clock_UpdateTime();
void Clock_CycleDone();
void Clock_delayMicroseconds(u16 microseconds);
void Clock_delayMilliseconds(u16 milliseconds);
void Clock_IRcooldown();
void Clock_CalculateTime();
void Clock_CheckIRInput();
void Clock_DisplayAnalogHourNumber();
void Clock_DisplayArrow(u16 position,u8 A_Tipvalue, u8 A_Armvalue,u8 B_Tipvalue, u8 B_Armvalue);
void Clock_DisplayMiniDigits();
void Clock_AnalogMode();
void Clock_DigitalMode();
void Clock_HybridMode();
void Clock_POV();
void Clock_MotorSpeed();
void Clock_Reset();

#endif /* HAL_CLOCK_HEADER_CLOCK_INTERFACE_H_ */
