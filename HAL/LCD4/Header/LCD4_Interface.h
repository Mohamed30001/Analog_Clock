/*
 * LCD4_Interface.h
 *
 *  Created on: Nov 6, 2022
 *      Author: aweso
 */

#ifndef HAL_LCD4_HEADER_LCD4_INTERFACE_H_
#define HAL_LCD4_HEADER_LCD4_INTERFACE_H_

#include "LCD4_Private.h"


void LCD4_voidInit();
void LCD4_voidWriteCommand(u8 Local_Command);
void LCD4_voidWriteChar(u8 Local_Data);
void LCD4_voidWriteString(u8* Local_Data);
void LCD4_voidStartCommunication();
void LCD4_voidRestartCommunication();
void LCD4_voidStopCommunication();
void LCD4_voidSendInitCommands(u8 data);
void LCD4_voidWriteIntData(s32 Data);
void LCD4_voidWriteFloatData(f32 Data);
u8* LCD4_ptrIntToString(s32 anInteger,u8 *str);
void LCD4_voidGoToPosition(u8 X_Position, u8 Y_Position);
void LCD4_voidDisplaySpecialChar(u8 *char_ptr,u8 CGRam_index,u8 row,u8 column);

#endif /* HAL_LCD4_HEADER_LCD4_INTERFACE_H_ */
