/*
 * LCD4_Private.h
 *
 *  Created on: Nov 6, 2022
 *      Author: aweso
 */

#ifndef HAL_LCD4_HEADER_LCD4_PRIVATE_H_
#define HAL_LCD4_HEADER_LCD4_PRIVATE_H_

#define LCD4_SlaveAddress	0x27
#define LCD4_RS				0
#define LCD4_RW				1
#define LCD4_EN				2
#define LCD4_Backlight		3
#define LCD4_Data1			4
#define LCD4_Data2			5
#define LCD4_Data3			6
#define LCD4_Data4			7

#define LCD4_SpecialFunctionSet		0x30
#define LCD4_FunctionSet			0x28
#define LCD4_DisplayOFF				0x08
#define LCD4_DisplayON				0x0C
#define LCD4_EntryMode				0x06
#define LCD4_ClearDisplay			0x01
#define LCD4_ReturnHome				0x02
#define LCD4_4BitMode				0x20
#define LCD4_ShiftDisplayRight	 	0x1C
#define LCD4_ShiftDisplayLeft  		0x18

#define FIRST_LINE_ADDRESS  		0x00
#define SECOND_LINE_ADDRESS 		0x40
#define INT_TO_STRING_ARR_SIZE  20

#endif /* HAL_LCD4_HEADER_LCD4_PRIVATE_H_ */
