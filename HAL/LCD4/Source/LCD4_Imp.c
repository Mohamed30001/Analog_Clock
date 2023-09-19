#include "../../../Common/Bit_Math.h"
#include "../../../Common/Macro.h"
#include "../../../Common/STD_types.h"

#include "../../../MCAL/DIO/Header/DIO_Interface.h"
#include "../../../MCAL/TWI/Header/TWI_Interface.h"
#include "../Header/LCD4_Interface.h"

#include "util/delay.h"

void LCD4_voidInit(){
	DIO_u8SetPinDir(DIO_GroupC,DIO_PIN0,Output);
	DIO_u8SetPinDir(DIO_GroupC,DIO_PIN1,Output);

	TWI_VoidMasterInit();
	LCD4_voidStartCommunication();
	_delay_ms(100);
	LCD4_voidSendInitCommands(LCD4_SpecialFunctionSet);
	_delay_ms(5);
	LCD4_voidSendInitCommands(LCD4_SpecialFunctionSet);
	_delay_ms(1);
	LCD4_voidSendInitCommands(LCD4_SpecialFunctionSet);
	_delay_ms(1);
	LCD4_voidSendInitCommands(LCD4_4BitMode);//4-bit mode
	_delay_ms(1);
	LCD4_voidWriteCommand(LCD4_FunctionSet);//Function Set
	_delay_ms(1);
	LCD4_voidWriteCommand(LCD4_DisplayOFF);//Display ON/OFF
	_delay_ms(1);
	LCD4_voidWriteCommand(LCD4_ClearDisplay);//Clear Display
	_delay_ms(5);
	LCD4_voidWriteCommand(LCD4_EntryMode);//Entry Mode Set
	_delay_ms(1);
	LCD4_voidWriteCommand(LCD4_DisplayON);//Turn Display ON
	_delay_ms(1);
}


void LCD4_voidWriteCommand(u8 Local_Command){
	u8 data = 0x00; //RS = 0 , RW = 0
	data |= (1<<LCD4_Backlight) | (Local_Command & 0xF0); //Send the upper 4 bits

	Set_Bit(data,LCD4_EN);
	TWI_VoidMasterWriteDataACK(data);
	Clear_Bit(data,LCD4_EN); //EN = 0
	TWI_VoidMasterWriteDataACK(data);

	_delay_ms(5);

	data = 0x00;//RS = 0 , RW = 0
	data |= (1<<LCD4_Backlight) | ((Local_Command & 0x0F) << LCD4_Data1); //Send the Lower 4 bits

	Set_Bit(data,LCD4_EN); //EN = 1
	TWI_VoidMasterWriteDataACK(data);
	Clear_Bit(data,LCD4_EN); //EN = 0
	TWI_VoidMasterWriteDataACK(data);
	_delay_ms(5);
}

void LCD4_voidWriteChar(u8 Local_Data){
	u8 data = 0x00; //RW = 0
	data |= (1<<LCD4_Backlight) | (1 << LCD4_RS) | (Local_Data & 0xF0) ; //Send the upper 4 bits and RS = 1

	Set_Bit(data,LCD4_EN); //EN = 1
	TWI_VoidMasterWriteDataACK(data);
	Clear_Bit(data,LCD4_EN); //EN = 0
	TWI_VoidMasterWriteDataACK(data);
	_delay_ms(5);

	data = 0x00; //RW = 0
	data |= (1<<LCD4_Backlight) | (1 << LCD4_RS) | ((Local_Data & 0x0F) << LCD4_Data1); //Send the Lower 4 bits and RS = 1

	Set_Bit(data,LCD4_EN); //EN = 1
	TWI_VoidMasterWriteDataACK(data);
	Clear_Bit(data,LCD4_EN); //EN = 0
	TWI_VoidMasterWriteDataACK(data);
	_delay_ms(5);
}

void LCD4_voidStartCommunication(){
	TWI_u32StartCondition();
	TWI_VoidSendSlaveAddressWithWriteACK(LCD4_SlaveAddress);
}

void LCD4_voidStopCommunication(){
	TWI_VoidStopCondition();
}

void LCD4_voidRestartCommunication(){
	TWI_VoidReStartCondition();
	TWI_VoidSendSlaveAddressWithWriteACK(LCD4_SlaveAddress);
}

void LCD4_voidSendInitCommands(u8 data){
	data |= (1<<LCD4_Backlight);
	Set_Bit(data,LCD4_EN);
	TWI_VoidMasterWriteDataACK(data);
	Clear_Bit(data,LCD4_EN); //EN = 0
	TWI_VoidMasterWriteDataACK(data);
}

void LCD4_voidWriteString(u8* Local_Data){
	u32 counter=0;
	while(Local_Data[counter] != '\0'){
		LCD4_voidWriteChar(Local_Data[counter]);
		counter++;
	}
}

u8* LCD4_ptrIntToString(s32 anInteger,u8 *str){
	u32 flag = 0;
	u32 i = INT_TO_STRING_ARR_SIZE - 1;
	str[i--] = '\0';
	if (anInteger < 0) {
		flag = 1;
		anInteger = -anInteger;
	}
	while (anInteger != 0) {
		str[i--] = (anInteger % 10) + '0';
		anInteger /= 10;
	}
	if (flag){
		str[i--] = '-';
	}
	i++;
	return str + i;

}

void LCD4_voidWriteIntData(s32 Data){
	if(Data){
		u8 arr[INT_TO_STRING_ARR_SIZE];
		//sprintf(str,"%d",Data);
		u8 *str = LCD4_ptrIntToString(Data,arr);
		LCD4_voidWriteString(str);
	}
	else{
		LCD4_voidWriteChar('0');
	}
}

void LCD4_voidWriteFloatData(f32 Data){
	u8 arr[INT_TO_STRING_ARR_SIZE];
	s32 number = (s32) (Data * 100);
	//sprintf(str,"%d",number);
	u8 *str = LCD4_ptrIntToString(number,arr);
	u32 counter=0;
	u32 counter2=0;
	while(str[counter] != '\0'){
		counter++;
	}
	counter -= 2;
	if(!counter){
		LCD4_voidWriteChar('0');
	}
	while(str[counter2] != '\0'){
		if(counter2 == counter){
			LCD4_voidWriteChar('.');
		}
		LCD4_voidWriteChar(str[counter2]);
		counter2++;
	}
}

void LCD4_voidDisplaySpecialChar(u8 *char_ptr,u8 CGRam_index,u8 row,u8 column){
	LCD4_voidGoToPosition(row,column);
	LCD4_voidWriteChar(CGRam_index);
	u8 address = 0;
	u8 index = 0;
	if(CGRam_index < 8){
		address = CGRam_index * 8;
		SET_BIT(address,6);
		CLR_BIT(address,7);
		LCD4_voidWriteCommand(address);
		for(index = 0; index < 8; index++){
			LCD4_voidWriteChar(char_ptr[index]);
		}
	}
	LCD4_voidWriteCommand(LCD4_ReturnHome);
}

void LCD4_voidGoToPosition(u8 X_Position, u8 Y_Position){
	u8 Local_Address = FIRST_LINE_ADDRESS;

	if(X_Position == 0){
		Local_Address = FIRST_LINE_ADDRESS + Y_Position;
	}
	else if(X_Position == 1){
		Local_Address = SECOND_LINE_ADDRESS + Y_Position;
	}

	SET_BIT(Local_Address,7); /*You can also just OR / add with 0x80 (128) to set the the MSB*/
	LCD4_voidWriteCommand(Local_Address);
}
