#include "../../../Common/Bit_Math.h"
#include "../../../Common/Macro.h"
#include "../../../Common/STD_types.h"

#include "../../../MCAL/DIO/Header/DIO_Interface.h"
#include "../../../MCAL/EXTI/Header/EXTI_Interface.h"
#include "../../../MCAL/Timer0/Header/TI0_Interface.h"
#include "../../../MCAL/Timer2/Header/TIMER2_Interface.h"
#include "../../../HAL/IR/Header/IR_Interface.h"

#include "../Header/Clock_Interface.h"

static u16 clockPointCounter = 1;
static u16 currentSecondLocation = 1;
static u16 currentMinuteLocation = 1;
static u16 currentHourLocation = 1;
static u16 currentMinute = 300;
static u16 currentHour = 300;

static u8 hoursLeftNumber = 0;
static u8 hoursRightNumber = 0;
static u8 minutesLeftNumber = 0;
static u8 minutesRightNumber = 0;
static u8 secondsLeftNumber = 0;
static u8 secondsRightNumber = 0;
static u8 delayBreak = 0;
u8 clockOn = 0;
u8 updateTime = 0;
u32 IRsignal = 0;
u8 disableIR = 0;
u8 power = 0;
MODES_EN mode= ANALOG;

static u8 resetTimer = 1;
static u32 motorCycleTime = 0;
static u32 cycleTimeCounter = 0;
static u8 clockCycleDelays[3] = {20,0,20};
static u8 cycleDelay = 20;

static u8 PORTB_Values = 0;
static u8 PORTA_Values = 0;

static u8 miniDigitalMatrix[10][5] = {{MINI_ZERO},{MINI_ONE},{MINI_TWO},{MINI_THREE},{MINI_FOUR},
		{MINI_FIVE},{MINI_SIX},{MINI_SEVEN},{MINI_EIGHT},{MINI_NINE}};

static u8 digitalMatrix[10][11] = {{ZERO},{ONE},{TWO},{THREE},{FOUR},{FIVE},{SIX},{SEVEN},{EIGHT},{NINE}};

static u8 MINI_IMT[3][7] = {{LETTER_MINI_I},{LETTER_MINI_M},{LETTER_MINI_T}};

static u8 IMT[3][11] = {{LETTER_I},{LETTER_M},{LETTER_T}};

void Clock_InitializeClockPosition(){
	currentSecondLocation = TOTAL_CYCLE_POINTS + STARTING_SECONDS * MINUTES_POINT;
	if(currentSecondLocation > TOTAL_CYCLE_POINTS){
		currentSecondLocation-=TOTAL_CYCLE_POINTS;
	}

	currentMinuteLocation = TOTAL_CYCLE_POINTS + MINUTES_POINT * (STARTING_MINUTES + STARTING_SECONDS / 60);
	if(currentMinuteLocation > TOTAL_CYCLE_POINTS){
		currentMinuteLocation-=TOTAL_CYCLE_POINTS;
	}

	currentHourLocation = HOURS_POINT * (STARTING_HOURS + STARTING_MINUTES / 60);
	if(currentHourLocation > TOTAL_CYCLE_POINTS){
		currentHourLocation-=TOTAL_CYCLE_POINTS;
	}
	currentHour = STARTING_HOURS * HOURS_POINT;
	currentMinute = TOTAL_CYCLE_POINTS + STARTING_MINUTES * MINUTES_POINT;
	if(currentMinute > TOTAL_CYCLE_POINTS){
		currentMinute -= TOTAL_CYCLE_POINTS;
	}
}

void Clock_Setup(){
	//Set the LED ports as output
	DIO_u8SetPortDir(DIO_GroupB,DIO_GroupOutput);
	DIO_u8SetPortDir(DIO_GroupA,DIO_GroupOutput);
	//Initialize the IR
	IR_voidInit();
	//Set the timer callback
	TI0_CallBackFunctionCTC(Clock_UpdateTime);
	TI2_CallBackFunctionCTC(Clock_MotorSpeed);
	//Enable the timer
	TI0_voidInitCTC(249,TI0_OCdisconnect,TI0_Prescaler256);
	TI2_voidInit(249);
	//Set the EXTI callback
	EXTI_CallBackFunction(Clock_CycleDone);
	//Initialize the EXTI
	EXTI_voidInit0(EXTI_Rising);
}

void Clock_UpdateTime(){//Call this function every 4k (for 16MHz) or 8k (for 8MHz) microseconds using timer0
	static u16 Local_Counter = 0;
	Local_Counter++;
	if(Local_Counter == DESIRED_COUNTER_VALUE){//Only enter every second
		updateTime = 1;
		Local_Counter = 0;
	}
}

void Clock_CycleDone(){//Call this function in the EXTI
	//Get the motor cycle time from timer2 in microseconds
	motorCycleTime = TI2_TCNT2 * 32 + cycleTimeCounter * TIMER2_CTC_VALUE;//Could potentially add 1 to accommodate for the timer counting from 0
	motorCycleTime /= (TOTAL_CYCLE_POINTS); //Divide the cycle time by 300
	//Reset timer2 and cycle time counter
	TI2_TCNT2 = 0;
	cycleTimeCounter = 0;
	resetTimer = 0; //This is set to 0 to stop resetting timer2 in the main function
	if(clockOn){
		delayBreak = 1;
	}

	clockOn = 1;
	//Reset the clock point counter to the first position
	clockPointCounter = STARTING_POINT;
	disableIR = 0;
}

void Clock_delayMicroseconds(u16 microseconds){
#if F_CPU >= 16000000L
	// for the 16 MHz clock

	// for a one-microsecond delay, simply return.  the overhead
	// of the function call takes 14 (16) cycles, which is 1us
	if (microseconds <= 1) return; //  = 3 cycles, (4 when true)

	// the following loop takes 1/4 of a microsecond (4 cycles)
	// per iteration, so execute it four times for each microsecond of
	// delay requested.
	microseconds <<= 2; // x4 us, = 4 cycles

	// account for the time taken in the preceeding commands.
	// we just burned 19 (21) cycles above, remove 5, (5*4=20)
	// us is at least 8 so we can subtract 5
	microseconds -= 5; // = 2 cycles,
#elif F_CPU >= 8000000L
	// for the 8 MHz clock

	// for a 1 and 2 microsecond delay, simply return.  the overhead
	// of the function call takes 14 (16) cycles, which is 2us
	if (microseconds <= 2) return; //  = 3 cycles, (4 when true)

	// the following loop takes 1/2 of a microsecond (4 cycles)
	// per iteration, so execute it twice for each microsecond of
	// delay requested.
	microseconds <<= 1; //x2 us, = 2 cycles

	// account for the time taken in the preceeding commands.
	// we just burned 17 (19) cycles above, remove 4, (4*4=16)
	// us is at least 6 so we can subtract 4
	microseconds -= 4; // = 2 cycles

#endif
	// busy wait
	__asm__ __volatile__ (
			"1: sbiw %0,1" "\n\t" // 2 cycles
			"brne 1b" : "=w" (microseconds) : "0" (microseconds) // 2 cycles
	);
	// return = 4 cycles
}

void Clock_delayMilliseconds(u16 milliseconds){
	for(u16 i = 0; i < milliseconds; i++)
	{
		Clock_delayMicroseconds(1000);
	}
}

void Clock_CalculateTime(){
	//Increment the second's position
	currentSecondLocation += MINUTES_POINT;
	if(currentSecondLocation > TOTAL_CYCLE_POINTS){
		//Reset the second's position
		currentSecondLocation -= TOTAL_CYCLE_POINTS;
	}

	if(currentSecondLocation % TOTAL_CYCLE_POINTS == 0){
		currentMinute += MINUTES_POINT;
		if(currentMinute > TOTAL_CYCLE_POINTS){
			currentMinute -= TOTAL_CYCLE_POINTS;
		}
		currentMinuteLocation = currentMinute;
	}
	else{
		currentMinuteLocation = currentMinute + MINUTES_POINT * currentSecondLocation / TOTAL_CYCLE_POINTS;
	}

	if(currentMinuteLocation > TOTAL_CYCLE_POINTS){
		//Reset the minute's position
		currentMinuteLocation -= TOTAL_CYCLE_POINTS;
	}

	if(currentMinuteLocation % TOTAL_CYCLE_POINTS == 0){
		if(currentSecondLocation % TOTAL_CYCLE_POINTS == 0){
			currentHour += HOURS_POINT;
		}
		if(currentHour > TOTAL_CYCLE_POINTS){
			currentHour -= TOTAL_CYCLE_POINTS;
		}
		currentHourLocation = currentHour;
	}
	else{
		currentHourLocation = currentHour + HOURS_POINT * currentMinuteLocation / TOTAL_CYCLE_POINTS;
	}

	if(currentHourLocation > TOTAL_CYCLE_POINTS){
		//Reset the hour's position
		currentHourLocation -= TOTAL_CYCLE_POINTS;
	}

	hoursLeftNumber = (currentHour/ HOURS_POINT) / 10;
	hoursRightNumber = (currentHour/ HOURS_POINT) % 10;
	minutesLeftNumber = (currentMinute / MINUTES_POINT) / 10;
	if(minutesLeftNumber == 6){
		minutesLeftNumber = 0;
	}
	minutesRightNumber = (currentMinute / MINUTES_POINT) % 10;
	secondsLeftNumber = (currentSecondLocation / MINUTES_POINT) / 10;
	if(secondsLeftNumber == 6){
		secondsLeftNumber = 0;
	}
	secondsRightNumber = (currentSecondLocation / MINUTES_POINT) % 10;
}

void Clock_CheckIRInput(){
	switch(IRsignal){
	case IR_UP:
		currentHour += HOURS_POINT;
		if(currentHour > TOTAL_CYCLE_POINTS){
			currentHour -= TOTAL_CYCLE_POINTS;
		}
		break;
	case IR_DOWN:
		if(currentHour > HOURS_POINT){
			currentHour -= HOURS_POINT;
		}
		else{
			currentHour = TOTAL_CYCLE_POINTS;
		}
		break;
	case IR_SKIP_DASH:
		currentMinute += MINUTES_POINT;
		if(currentMinute > TOTAL_CYCLE_POINTS){
			currentMinute -= TOTAL_CYCLE_POINTS;
		}
		break;
	case IR_REWIND_DASH:
		if(currentMinute > MINUTES_POINT){
			currentMinute -= MINUTES_POINT;
		}
		else{
			currentMinute = TOTAL_CYCLE_POINTS;
		}
		break;
	case IR_MODE:
		mode++;
		if(mode>3) mode = ANALOG;
		cycleDelay = clockCycleDelays[mode];
		break;
	case IR_POWER:
		Toggle_Bit(power,0);
		break;
	}
}

void Clock_DisplayAnalogHourNumber(){
	switch(clockPointCounter){
	case 296: //Display 1 0x3E
	case 152: //Display fifth 6 column 0x3E
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN5,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN4,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN3,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN2,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN1,High);
		PORTB_Values |= 0x3E;
		break;
	case 1: //Display first 2 column 0x2E
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN5,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN3,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN2,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN1,High);
		PORTB_Values |= 0x2E;
		break;
	case 2:  //Display Second 2 column 0x2A
	case 3:  //Display third 2 column 0x2A
	case 149: //Display second 6 column 0x2A
	case 150: //Display third 6 column 0x2A
	case 151: //Display fourth 6 column 0x2A
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN5,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN3,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN1,High);
		PORTB_Values |= 0x2A;
		break;
	case 4: //Display fourth 2 column 0x3A
	case 148: //Display first 6 column 0x3A
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN5,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN4,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN3,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN1,High);
		PORTB_Values |=0x3A;
		break;
	case 70: //Display first 3 row 0x38
	case 75: //Display sixth 3 row 0x38
	case 80: //Display eleventh 3 column 0x38
	case 220://Display first 9 row 0x38
	case 225://Display sixth 9 row 0x38
	case 230://Display eleventh 9 row 0x38
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN5,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN4,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN3,High);
		PORTB_Values |=0x38;
		break;
	case 71: //Display second 3 row 0x20
	case 72: //Display third 3 row 0x20
	case 73: //Display fourth 3 row 0x20
	case 74: //Display fifth 3 row 0x20
	case 76: //Display seventh 3 row 0x20
	case 77: //Display eighth 3 row 0x20
	case 78: //Display ninth 3 row 0x20
	case 79: //Display tenth 3 row 0x20
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN5,High);
		PORTB_Values |=0x20;
		break;
	case 221://Display second 9 row 0x08
	case 222://Display third 9 row 0x08
	case 223://Display fourth 9 row 0x08
	case 224://Display fifth 9 row 0x08
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN3,High);
		PORTB_Values |=0x08;
		break;
	case 226://Display seventh 9 row 0x28
	case 227://Display eighth 9 row 0x28
	case 228://Display ninth 9 row 0x28
	case 229://Display tenth 9 row 0x28
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN5,High);
		//				DIO_u8SetPinValue(DIO_GroupB,DIO_PIN3,High);
		PORTB_Values |=0x28;
		break;
	}
}

void Clock_DisplayArrow(u16 position,u8 A_Tipvalue, u8 A_Armvalue,u8 B_Tipvalue, u8 B_Armvalue){
	if(clockPointCounter == (position - 1) || clockPointCounter == (position + 1) || (clockPointCounter + 299) == position || (clockPointCounter - 299) == position
			|| clockPointCounter == (position - 2) || clockPointCounter == (position + 2) || (clockPointCounter + 298) == position || (clockPointCounter - 298) == position){
		PORTA_Values |= A_Tipvalue;
		PORTB_Values |= B_Tipvalue;
	}
	else if(clockPointCounter == position){
		PORTA_Values |= A_Armvalue;
		PORTB_Values |= B_Armvalue;
	}
}

void Clock_DisplayMiniDigits(){
	switch(clockPointCounter){
	//Hours left number
	case 274: case 275: case 276: case 277: case 278:
		PORTB_Values |= miniDigitalMatrix[hoursLeftNumber][clockPointCounter-274];
		break;
		//Hours right number
	case 282: case 283: case 284: case 285: case 286:
		PORTB_Values |= miniDigitalMatrix[hoursRightNumber][clockPointCounter-282];
		break;
		//Colons
	case 290: case 10:
		PORTB_Values |= 0x50;
		break;
		//Minutes left number
	case 294: case 295: case 296: case 297: case 298:
		PORTB_Values |= miniDigitalMatrix[minutesLeftNumber][clockPointCounter-294];
		break;
		//Minutes right number
	case 2: case 3: case 4: case 5: case 6:
		PORTB_Values |= miniDigitalMatrix[minutesRightNumber][clockPointCounter-2];
		break;
		//Seconds left number
	case 14: case 15: case 16: case 17: case 18:
		PORTB_Values |= miniDigitalMatrix[secondsLeftNumber][clockPointCounter-14];
		break;
		//Seconds right number
	case 22: case 23: case 24: case 25: case 26:
		PORTB_Values |= miniDigitalMatrix[secondsRightNumber][clockPointCounter-22];
		break;
		//Letter T
	case 137: case 138: case 139: case 140: case 141: case 142: case 143:
		PORTB_Values |= MINI_IMT[2][clockPointCounter - 137];
		break;
		//Letter M
	case 147: case 148: case 149: case 150: case 151: case 152: case 153:
		PORTB_Values |= MINI_IMT[1][clockPointCounter - 147];
		break;
		//Letter I
	case 157: case 158: case 159: case 160: case 161: case 162: case 163:
		PORTB_Values |= MINI_IMT[0][clockPointCounter - 157];
		break;
	}
}

void Clock_AnalogMode(){
	if(clockPointCounter % MINUTES_POINT == 0){
		//Turn on the minute's marker LEDs
		PORTB_Values |= 0x80;//B: 0x80
		//DIO_u8SetPinValue(DIO_GroupB,DIO_PIN7,High);
		if(clockPointCounter % HOURS_POINT == 0){
			//Turn on the hour's marker LEDs
			PORTB_Values |= 0x40;//B: 0x40
			//DIO_u8SetPinValue(DIO_GroupB,DIO_PIN6,High);
		}
	}

	Clock_DisplayAnalogHourNumber();
	/*Turn on the second's LEDs A: 0x00  B: 0x10
								DIO_u8SetPinValue(DIO_GroupB,DIO_PIN4,High);
				Turn on the second's LEDs A: 0x7F  B: 0x3F
								DIO_u8SetPinValue(DIO_GroupB,DIO_PIN5,High);
								DIO_u8SetPinValue(DIO_GroupB,DIO_PIN4,High);
								DIO_u8SetPinValue(DIO_GroupB,DIO_PIN3,High);
								DIO_u8SetPinValue(DIO_GroupB,DIO_PIN2,High);
								DIO_u8SetPinValue(DIO_GroupB,DIO_PIN1,High);
								DIO_u8SetPinValue(DIO_GroupB,DIO_PIN0,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN0,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN1,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN2,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN3,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN4,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN5,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN6,High);*/
	Clock_DisplayArrow(currentSecondLocation, 0, 0x7F, 0x10, 0x3F);
	/*Turn on the second's LEDs A: 0x00  B: 0x02
								DIO_u8SetPinValue(DIO_GroupB,DIO_PIN1,High);
				Turn on the minute's LEDs A: 0x7F  B: 0x07
								DIO_u8SetPinValue(DIO_GroupB,DIO_PIN2,High);
								DIO_u8SetPinValue(DIO_GroupB,DIO_PIN1,High);
								DIO_u8SetPinValue(DIO_GroupB,DIO_PIN0,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN0,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN1,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN2,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN3,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN4,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN5,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN6,High);*/
	Clock_DisplayArrow(currentMinuteLocation, 0, 0x7F, 0x02, 0x07);
	/*Turn on the second's LEDs A: 0x02  B: 0x00
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN1,High);
				Turn on the hour's LEDs LEDs A: 0x7F  B: 0x00
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN0,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN1,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN2,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN3,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN4,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN5,High);
								DIO_u8SetPinValue(DIO_GroupA,DIO_PIN6,High);*/
	Clock_DisplayArrow(currentHourLocation, 0x02, 0x7F, 0, 0);
}

void Clock_DigitalMode(){
	switch(clockPointCounter){
	//Hours left number
	case 248: case 249: case 250: case 251: case 252: case 253: case 254: case 255: case 256: case 257: case 258:
		PORTB_Values |= digitalMatrix[hoursLeftNumber][clockPointCounter - 248];
		break;
	case 264: case 265: case 266: case 267: case 268: case 269: case 270: case 271: case 272: case 273: case 274:
		//Hours right number
		PORTB_Values |= digitalMatrix[hoursRightNumber][clockPointCounter - 264];
		break;
	case 280: case 281: case 19: case 20:
		//Colons
		PORTB_Values |= 0x24;
		break;
	case 287: case 288: case 289: case 290: case 291: case 292: case 293: case 294: case 295: case 296: case 297:
		//Minutes left number
		PORTB_Values |= digitalMatrix[minutesLeftNumber][clockPointCounter - 287];
		break;
	case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13:
		//Minutes right number
		PORTB_Values |= digitalMatrix[minutesRightNumber][clockPointCounter - 3];
		break;
	case 26: case 27: case 28: case 29: case 30: case 31: case 32: case 33: case 34: case 35: case 36:
		//Seconds left number
		PORTB_Values |= digitalMatrix[secondsLeftNumber][clockPointCounter - 26];
		break;
	case 42: case 43: case 44: case 45: case 46: case 47: case 48: case 49: case 50: case 51: case 52:
		//Seconds right number
		PORTB_Values |= digitalMatrix[secondsRightNumber][clockPointCounter - 42];
		break;
	case 129: case 130: case 131: case 132: case 133: case 134: case 135: case 136: case 137: case 138: case 139:
		//Letter T
		PORTB_Values |= IMT[2][clockPointCounter - 129];
		break;
	case 145: case 146: case 147: case 148: case 149: case 150: case 151: case 152: case 153: case 154: case 155:
		//Letter M
		PORTB_Values |= IMT[1][clockPointCounter - 145];
		break;
	case 161: case 162: case 163: case 164: case 165: case 166: case 167: case 168: case 169: case 170: case 171:
		//Letter I
		PORTB_Values |= IMT[0][clockPointCounter - 161];
		break;
	}
}

void Clock_HybridMode(){
	if(clockPointCounter % MINUTES_POINT == 0){
		//Turn on the minute's marker LEDs
		PORTB_Values |= 0x02;//B: 0x02
		//DIO_u8SetPinValue(DIO_GroupB,DIO_PIN1,High);
		if(clockPointCounter % HOURS_POINT == 0){
			//Turn on the hour's marker LEDs
			PORTB_Values |= 0x01;//B: 0x01
			//DIO_u8SetPinValue(DIO_GroupB,DIO_PIN0,High);
		}
	}
	/*Turn on the second's LEDs A: 0x02  B: 0x00
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN1,High);
					  Turn on the second's LEDs A: 0x7F  B: 0x00
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN0,High);
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN1,High);
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN2,High);
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN3,High);
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN4,High);
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN5,High);
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN6,High);*/
	Clock_DisplayArrow(currentSecondLocation, 0x02, 0x7F, 0, 0x00);
	/*Turn on the second's LEDs A: 0x08  B: 0x00
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN3,High);
					  Turn on the minute's LEDs A: 0x7C  B: 0x00
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN2,High);
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN3,High);
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN4,High);
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN5,High);
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN6,High);*/
	Clock_DisplayArrow(currentMinuteLocation, 0x08, 0x7C, 0, 0);
	/*Turn on the second's LEDs A: 0x10  B: 0x00
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN4,High);
					  Turn on the hour's LEDs LEDs A: 0x78  B: 0x00
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN3,High);
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN4,High);
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN5,High);
												DIO_u8SetPinValue(DIO_GroupA,DIO_PIN6,High);*/
	Clock_DisplayArrow(currentHourLocation, 0x10, 0x78, 0, 0);

	Clock_DisplayMiniDigits();
}

void Clock_POV(){
	//Enable the LEDs
	DIO_u8SetPortValue(DIO_GroupB,PORTB_Values);
	DIO_u8SetPortValue(DIO_GroupA,PORTA_Values);

	Clock_delayMicroseconds(LED_DELAY);

	//Disable the LEDs
	PORTB_Values = 0;
	PORTA_Values = 0;
	DIO_u8SetPortValue(DIO_GroupB,PORTB_Values);
	DIO_u8SetPortValue(DIO_GroupA,PORTA_Values);

	Clock_delayMicroseconds(motorCycleTime - LED_DELAY - cycleDelay);
	//Increment the clock point counter to move to the next point in the cycle
	clockPointCounter++;
	if(clockPointCounter == STARTING_POINT){
		clockOn = 0;
	}
	else if(clockPointCounter > TOTAL_CYCLE_POINTS){
		clockPointCounter -=TOTAL_CYCLE_POINTS;
	}
	if(delayBreak){
		clockOn = 1;
		clockPointCounter = STARTING_POINT;
		delayBreak = 0;
	}
}

void Clock_MotorSpeed(){//Call this function in the timer2 CTC interrupt
	//Increment the cycle time counter by the CTC times
	cycleTimeCounter++;
}

void Clock_Reset(){
	if(cycleTimeCounter >= RESET_TIMER_TOLERANCE && !resetTimer){
		resetTimer = 1;
	}
	else if(resetTimer){
		//Keep resetting the timer2 because the motor is not spinning anymore
		TI2_TCNT2 = 0;
		cycleTimeCounter = 0;
	}
}
