/*
 * TWI_Register.h
 *
 *  Created on: Oct 30, 2022
 *      Author: hisha
 */

#ifndef MCAL_TWI_HEADER_TWI_REGISTER_H_
#define MCAL_TWI_HEADER_TWI_REGISTER_H_
#include "../../../Common/STD_types.h"

#define TWI_TWBR  (*(volatile u8*)0x20)
#define TWI_TWCR  (*(volatile u8*)0x56)
#define TWI_TWSR  (*(volatile u8*)0x21)
#define TWI_TWDR  (*(volatile u8*)0x23)
#define TWI_TWAR  (*(volatile u8*)0x22)

/*TWCR*/
#define TWI_TWINT       7
#define TWI_TWEA        6
#define TWI_TWSTA       5
#define TWI_TWSTO       4
#define TWI_TWWC        3
#define TWI_TWEN        2
#define TWI_TWIE        0
/*TWSR*/
/*5 bit for Status */
#define TWI_TWS7        7
#define TWI_TWS6        6
#define TWI_TWS5        5
#define TWI_TWS4        4
#define TWI_TWS3       	3
/*PerScaller*/
#define TWI_TWPS1       1
#define TWI_TWPS0       0
/**/



#endif /* MCAL_TWI_HEADER_TWI_REGISTER_H_ */
