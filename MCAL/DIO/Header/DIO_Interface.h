#ifndef MCAL_DIO_HEADER_DIO_INTERFACE_H_
#define MCAL_DIO_HEADER_DIO_INTERFACE_H_
#include "DIO_Private.h"
#include "DIO_Config.h"

u8 DIO_u8SetPinDir(u8 Local_GroupName,u8 Local_PinNumber,u8 Local_PinState);
u8 DIO_u8SetPinValue(u8 Local_GroupName,u8 Local_PinNumber,u8 Local_PinValue);
u8 DIO_u8GetPinValue(u8 Local_GroupName,u8 Local_PinNumber,u8* Reference_Value);


u8 DIO_u8SetPortDir(u8 Local_GroupName,u8 Local_PortState);
u8 DIO_u8SetPortValue(u8 Local_GroupName,u8 Local_PortState);
u8 DIO_u8GetPortValue(u8 Local_GroupName,u8* Reference_Value);

u8 DIO_u8ControlPullUp(u8 Local_GroupName, u8 Local_ConnectionType, u8 Local_PinNumber, u8 Local_PullUpState);

#endif /* MCAL_DIO_HEADER_DIO_INTERFACE_H_ */
