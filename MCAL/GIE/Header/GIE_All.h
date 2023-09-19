
#ifndef MCAL_GIE_HEADER_GIE_ALL_H_
#define MCAL_GIE_HEADER_GIE_ALL_H_

#define GIE_SREG	*((volatile u8*) 0x5F)
#define GIE_I		7

void GIE_voidEN();
void GIE_voidDis();


#endif /* MCAL_GIE_HEADER_GIE_ALL_H_ */
