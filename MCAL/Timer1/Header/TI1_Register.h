/*
 * TI1_Register.h
 *
 *  Created on: Oct 21, 2022
 *      Author: MoMenBak
 *	   Lecture: Interfacing_Lec
 */

#ifndef MCAL_TIMER1_HEADER_TI1_REGISTER_H_
#define MCAL_TIMER1_HEADER_TI1_REGISTER_H_

/*************************************** REGISTERS ***************************************/

/*TI1_TCCR1A: Timer/Counter1 Control Register A*/
#define TI1_TCCR1A           (*(volatile u8*)0x4F)

/*TI1_TCCR1B: Timer/Counter1 Control Register B*/
#define TI1_TCCR1B           (*(volatile u8*)0x4E)

/*TI1_TCNT1H: Timer/Counter1 Register High*/
#define TI1_TCNT1H           (*(volatile u8*)0x4D)

/*TI1_TCNT1L: Timer/Counter1 Register Low*/
#define TI1_TCNT1L           (*(volatile u8*)0x4C)
#define TI1_TCNT1            (*(volatile u16*)0x4C)

/*TI1_OCR1AH: Output Compare Register 1 A High*/
#define TI1_OCR1AH           (*(volatile u8*)0x4B)

/*TI1_OCR1AL: Output Compare Register 1 A Low*/
#define TI1_OCR1AL           (*(volatile u8*)0x4A)

/*TI1_OCR1A: Output Compare Register 1 A */
#define TI1_OCR1A           (*(volatile u16*)0x4A)

/*TI1_OCR1BH: Output Compare Register 1 B High*/
#define TI1_OCR1BH           (*(volatile u8*)0x49)

/*TI1_OCR1BL: Output Compare Register 1 B Low*/
#define TI1_OCR1BL           (*(volatile u8*)0x48)

/*TI1_ICR1H: Input Capture Register High*/
#define TI1_ICR1H            (*(volatile u8*)0x47)

/*TI1_ICR1L: Input Capture Register Low*/
#define TI1_ICR1L            (*(volatile u8*)0x46)

/*TI1_ICR1: Input Capture Register */
#define TI1_ICR1            (*(volatile u16*)0x46)

/*TI1_TIMSK: Timer/Counter Interrupt Mask  Register*/
#define TI1_TIMSK            (*(volatile u8*)0x59)

/*TI1_TIFR: Timer/Counter Interrupt Flag Register */
#define TI1_TIFR			 (*(volatile u8*)0x58)


/*************************************** PINS ***************************************/

/**************************** (TI1_TCCR1A) Register Pins ****************************/

/* TI1_COM1: Compare Output Mode for Compare unit A and B.
 * This Pins Select The Output behavior on OC1A and OC1B Pins, as shown at Table 44,45,46 at ATMEGA32 DataSheet.
 * */
#define TI1_COM1A1		7
#define TI1_COM1A0      6
#define TI1_COM1B1      5
#define TI1_COM1B0      4
/* TI1_FOC1: Force Output Compare for Compare unit A and B.
 * This Pins Force A Compare Match on The Waveform generation Unit.
 * */
#define TI1_FOC1A       3
#define TI1_FOC1B       2
/* TI1_WGM1: Waveform Generation Mode.
 * This Pins Select Timer Mode With WGM13 And WGM12 Pins In (TI1_TCCR1B) Register, As shown at Table47 At ATMEGA32 DataSheet.
 * */
#define TI1_WGM11       1
#define TI1_WGM10       0
/**************************** (TI1_TCCR1B) Register Pins ****************************/

/* TI1_ICNC1: Input Capture Noise Canceler
 * Still Not Explained*/
#define TI1_ICNC1		7
/* TI1_ICES1: Input Capture Edge Select
 * Still Not Explained*/
#define TI1_ICES1		6
/* TI1_WGM1: Waveform Generation Mode.
 * This Pins Select Timer Mode With WGM10 And WGM11 Pins In (TI1_TCCR1A) Register, As shown at Table47 At ATMEGA32 DataSheet.
 * */
#define TI1_WGM13		4
#define TI1_WGM12		3
/* TI1_CS1: Clock Select.
 * This Pins Select Timer PreScaller(Clock), As shown at Table48 At ATMEGA32 DataSheet.
 * */
#define TI1_CS12		2
#define TI1_CS11		1
#define TI1_CS10		0
/**************************** (TI1_TIMASK) Register Pins ****************************/
/* TI1_TICIE1: Timer/Counter1, Input Capture Interrupt Enable.
 * Still Not Explained*/
#define TI1_TICIE1		5
/* TI1_OCIE1: Timer/Counter1, Output Compare A Match Interrupt Enable pin A and B.
 * This Pin Enable Output Compare Match Interrupt.
 * */
#define TI1_OCIE1A		4
#define TI1_OCIE1B		3
/* TI1_TOIE1: Timer/Counter1, Overflow Interrupt Enable.
 * This pin Enable OverFlow Interrupt.
 * */
#define TI1_TOIE1		2
/**************************** (TI1_TIFR) Register Pins ****************************/
/* TI1_ICF1: Timer/Counter1, Input Capture Flag.
 * Still Not Explained.
 * */
#define TI1_ICF1		5
/*TI1_OCF1A: Timer/Counter1, Output Compare A And B Match Flag.
 * this pins raise a flag when The Counter value Match the (Compared Value)Desired Value in Register A And B.
 * */
#define TI1_OCF1A		4
#define TI1_OCF1B		3
/*TI1_TOV1: Timer/Counter1, Overflow Flag
 * This Pin Raise A flag when The Counter Match The Overflow
 * */
#define TI1_TOV1		2

#endif /* MCAL_TIMER1_HEADER_TI1_REGISTER_H_ */
