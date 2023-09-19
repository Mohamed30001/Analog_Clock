
#ifndef MCAL_TIMER2_HEADER_TIMER2_REGISTER_H_
#define MCAL_TIMER2_HEADER_TIMER2_REGISTER_H_

#define TI2_TIMSK 		(*(volatile u8*)0x59)
#define TI2_OCR2		(*(volatile u8*)0x43)
#define TI2_TIFR		(*(volatile u8*)0x58)
#define TI2_TCNT2 		(*(volatile u8*)0x44)
#define TI2_TCCR2 		(*(volatile u8*)0x45)



/*Control enable timer and read flag for Normal mood*/
#define TI2_TOIE2		6 //TI0_TIMSK
#define TI2_TOV2		6 //TI0_TIFR
/*Control enable timer and read flag for CTC mood*/
#define TI2_OCIE2		7 //TI0_TIMSK
#define TI2_OCF2		7 //TI0_TIFR
/*select mood*/
#define TI2_WGM20 		6 // TI0_TCCR0
#define TI2_WGM21 		3 // TI0_TCCR0
/*select the output on OC0 pin*/
#define TI2_COM21 		5 //TI0_TCCR0
#define TI2_COM20 		4 //TI0_TCCR0
/*select prescaler*/
#define TI2_CS22 		2 //TI0_TCCR0
#define TI2_CS21 		1 //TI0_TCCR0
#define TI2_CS20 		0 //TI0_TCCR0

#endif /* MCAL_TIMER2_HEADER_TIMER2_REGISTER_H_ */
