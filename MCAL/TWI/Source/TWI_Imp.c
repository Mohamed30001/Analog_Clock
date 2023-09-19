/*
 * TWI_Program.c
 *
 *  Created on: Oct 30, 2022
 *      Author: hisha
 */
#include "../../../Common/STD_types.h"
#include "../../../Common/Bit_Math.h"
#include "../../../Common/Macro.h"

#include "../Header/TWI_Interface.h"


void TWI_VoidMasterInit(void){
	/*Set Prescaler Values*/

	Clear_Bit(TWI_TWSR, TWI_TWPS0);
	Clear_Bit(TWI_TWSR, TWI_TWPS1);

	/*Set TWBR with the Value =>100KHZ*/
	TWI_TWBR = 32;

	/*Enable  I2C*/
	Set_Bit(TWI_TWCR,TWI_TWEN);
}

TWI_ErrorList TWI_u32StartCondition(void){
	TWI_ErrorList state = NoError;

	/*Clear flags + start condition*/
	TWI_TWCR = (1<<TWI_TWINT)| (1<<TWI_TWSTA) |(1<<TWI_TWEN);
	/*Wait for the flag*/
	while(Get_Bit(TWI_TWCR,TWI_TWINT) == 0);

	/*Check Status*/
	while((TWI_TWSR & 0xF8) != TWI_MTXCheckStart);

	if((TWI_TWSR & 0xF8) != TWI_MTXCheckStart){
		state = ErrorStartCondition;
	}

	return state;
}

TWI_ErrorList TWI_VoidReStartCondition(void){
	TWI_ErrorList state = NoError;

	/*Clear flags + start condition*/
	TWI_TWCR = (1<<TWI_TWINT)| (1<<TWI_TWSTA) |(1<<TWI_TWEN);

	/*Wait for the flag*/
	while(Get_Bit(TWI_TWCR,TWI_TWINT) == 0);

	/*Check Status*/
	while((TWI_TWSR & 0xF8) != TWI_MTXCheckReStart);

	if((TWI_TWSR & 0xF8) != TWI_MTXCheckReStart){
		state = ErrorRestartCondition;
	}
	return state;
}

/*Send the SlaveAdd Write*/
/*this Slave Address You want Connect it */
TWI_ErrorList TWI_VoidSendSlaveAddressWithWriteACK(u8 Local_SlaveAddress){
	TWI_ErrorList state = NoError;
	/*Load the slave address*/
	TWI_TWDR = Local_SlaveAddress << 1;

	/*Select the write mode*/
	Clear_Bit(TWI_TWDR, 0);

	TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWEN);

	/*Wait for the flag*/
	while(Get_Bit(TWI_TWCR,TWI_TWINT) == 0);

	/*Check Status*/
	if((TWI_TWSR & 0xF8) != TWI_MTXCheckSLA_W_WithAck){
		state = ErrorSlaveAddressWriteWithAck;
	}

	return state;
}

TWI_ErrorList TWI_VoidSendSlaveAddressWithWriteNACK(u8 Local_SlaveAddress){
	TWI_ErrorList state = NoError;

	/*Disable  ACK*/
	Clear_Bit(TWI_TWCR,TWI_TWEA);

	/*Load the slave address*/
	TWI_TWDR = Local_SlaveAddress << 1;

	/*Select the write mode*/
	Clear_Bit(TWI_TWDR, 0);

	/*Clear flag*/
	TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWEN);

	/*Wait for the flag*/
	while(Get_Bit(TWI_TWCR,TWI_TWINT) == 0);

	/*Check Status*/
	if((TWI_TWSR & 0xF8) != TWI_MTXCheckSLA_W_WithOutAck){
		state = ErrorSlaveAddressWriteWithoutAck;
	}
	return state;
}

/*Send the SlaveAdd Read*/
TWI_ErrorList TWI_VoidSendSlaveAddressWithReadACK(u8 Local_SlaveAddress){
	TWI_ErrorList state = NoError;

	/*Enable  ACK*/
	Set_Bit(TWI_TWCR,TWI_TWEA);

	/*Load the slave address*/
	TWI_TWDR = Local_SlaveAddress << 1;

	/*Select the read mode*/
	Set_Bit(TWI_TWDR, 0);

	/*Clear flag*/
	TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWEN);

	/*Wait for the flag*/
	while(Get_Bit(TWI_TWCR,TWI_TWINT) == 0);

	/*Check Status*/
	if((TWI_TWSR & 0xF8) != TWI_MRXCheckSLA_R_WithAck){
		state = ErrorSlaveAddressReadWithAck;
	}
	return state;
}

TWI_ErrorList TWI_VoidSendSlaveAddressWithReadNACK(u8 Local_SlaveAddress){
	TWI_ErrorList state = NoError;

	/*Disable  ACK*/
	Clear_Bit(TWI_TWCR,TWI_TWEA);

	/*Load the slave address*/
	TWI_TWDR = Local_SlaveAddress << 1;

	/*Select the read mode*/
	Set_Bit(TWI_TWDR, 0);

	/*Clear flag*/
	TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWEN);

	/*Wait for the flag*/
	while(Get_Bit(TWI_TWCR,TWI_TWINT) == 0);

	/*Check Status*/
	if((TWI_TWSR & 0xF8) != TWI_MRXCheckSLA_R_WithOutAck){
		state = ErrorSlaveAddressReadWithoutAck;
	}
	return state;
}

/* Master Send the Data*/
TWI_ErrorList TWI_VoidMasterWriteDataACK(u8 Local_Data){
	TWI_ErrorList state = NoError;

	/*Load the data*/
	TWI_TWDR = Local_Data;

	/*Clear flag*/
	TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWEN);

	/*Wait for the flag*/
	while(Get_Bit(TWI_TWCR,TWI_TWINT) == 0);

	/*Check Status*/
	if((TWI_TWSR & 0xF8) != TWI_MTXCheckData_WithAck){
		state = ErrorWriteDataWithAck;
	}
	return state;
}

TWI_ErrorList TWI_VoidMasterWriteDataNACK(u8 Local_Data){
	TWI_ErrorList state = NoError;

	/*Load the data*/
	TWI_TWDR = Local_Data;

	/*Clear flag*/
	TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWEN);

	/*Wait for the flag*/
	while(Get_Bit(TWI_TWCR,TWI_TWINT) == 0);

	/*Check Status*/
	if((TWI_TWSR & 0xF8) != TWI_MTXCheckData_WithOutAck){
		state = ErrorWriteDataWithoutAck;
	}
	return state;
}

/*Master Rx the Data*/
TWI_ErrorList  TWI_u8MasterReadDataACK(u8* ReceiveData){

	if(ReceiveData != NULL){
		TWI_ErrorList state = NoError;

		/*Clear flag*/
		TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWEN);

		/*Wait for the flag*/
		while(Get_Bit(TWI_TWCR,TWI_TWINT) == 0);

		/*Check Status*/
		if((TWI_TWSR & 0xF8) != TWI_MRXCheckData_WithAck){
			state = ErrorReadDataWithoutAck;
		}

		*ReceiveData = TWI_TWDR;
		return state;
	}
	return -1;
}

TWI_ErrorList  TWI_u8MasterReadDataNACK(u8* ReceiveData){
	if(ReceiveData != NULL){
		TWI_ErrorList state = NoError;

		/*Clear flag*/
		TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWEN);

		/*Wait for the flag*/
		while(Get_Bit(TWI_TWCR,TWI_TWINT) == 0);

		/*Check Status*/
		if((TWI_TWSR & 0xF8) != TWI_MRXCheckData_WithOutAck){
			state = ErrorReadDataWithoutAck;
		}

		*ReceiveData = TWI_TWDR;
		return state;
	}

	return -1;
}

/*Stop*/
void TWI_VoidStopCondition(void){
	/*Clear flag*/
	TWI_TWCR = (1<<TWI_TWINT)| (1<<TWI_TWSTO) |(1<<TWI_TWEN);
}

/*Slave*/
void TWI_VoidSlaveInit(u8 Local_SlaveAddress){
	/*Set Slave Address iN TWAR*/
	TWI_TWAR = (Local_SlaveAddress <<1);
	/*Enable ACK*/
	//Set_Bit(TWI_TWCR , TWI_TWEA);
	/*Enable I2C*/
	Set_Bit(TWI_TWCR , TWI_TWEN);
}

//void TWI_VoidSlaveSendData(u8 Local_Data){
//
//}
//
//u8   TWI_u8SlaveReciveData(void){
//
//}
