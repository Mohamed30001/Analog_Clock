/*
 * TI0_Register.h
 *
 *  Created on: Oct 15, 2022
 *      Author: hisha
 */

#ifndef MCAL_TIMER0_HEADER_TI0_REGISTER_H_
#define MCAL_TIMER0_HEADER_TI0_REGISTER_H_

#define TI0_TIMSK 		(*(volatile u8*)0x59)
#define TI0_OCR0		(*(volatile u8*)0x5C)
#define TI0_TIFR		(*(volatile u8*)0x58)
#define TI0_TCNT0 		(*(volatile u8*)0x52)
#define TI0_TCCR0 		(*(volatile u8*)0x53)



/*Control enable timer and read flag for Normal mood*/
#define TI0_TOIE0		0 //TI0_TIMSK
#define TI0_TOV0		0 //TI0_TIFR
/*Control enable timer and read flag for CTC mood*/
#define TI0_OCIE0		1 //TI0_TIMSK
#define TI0_OCF0		1 //TI0_TIFR
/*select mood*/
#define TI0_WGM00 		6 // TI0_TCCR0
#define TI0_WGM01 		3 // TI0_TCCR0
/*select the output on OC0 pin*/
#define TI0_COM01 		5 //TI0_TCCR0
#define TI0_COM00 		4 //TI0_TCCR0
/*select prescaler*/
#define TI0_CS02 		2 //TI0_TCCR0
#define TI0_CS01 		1 //TI0_TCCR0
#define TI0_CS00 		0 //TI0_TCCR0
#endif /* MCAL_TIMER0_HEADER_TI0_REGISTER_H_ */
