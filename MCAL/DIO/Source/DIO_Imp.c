#include "../../../Common/STD_types.h"
#include "../../../Common/Bit_Math.h"
#include "../../../Common/Macro.h"

#include "../Header/DIO_Register.h"
#include "../Header/DIO_Interface.h"

u8 DIO_u8SetPinDir(u8 Local_GroupName,u8 Local_PinNumber,u8 Local_PinState){
	u8 Request;
	if(Local_GroupName <= DIO_GroupD && Local_GroupName >= DIO_GroupA){

		if(Local_PinNumber <= DIO_PIN7 && Local_PinNumber >= DIO_PIN0){

			if(Local_PinState == Output){
				Request = RequestHandled;
				switch(Local_GroupName){
				case DIO_GroupA:
					Set_Bit(DIO_DDRA,Local_PinNumber);
					break;
				case DIO_GroupB:
					Set_Bit(DIO_DDRB,Local_PinNumber);
					break;
				case DIO_GroupC:
					Set_Bit(DIO_DDRC,Local_PinNumber);
					break;
				case DIO_GroupD:
					Set_Bit(DIO_DDRD,Local_PinNumber);
					break;
				}
			}
			else if(Local_PinState == Input){
				Request = RequestHandled;
				switch(Local_GroupName){
				case DIO_GroupA:
					Clear_Bit(DIO_DDRA,Local_PinNumber);
					break;
				case DIO_GroupB:
					Clear_Bit(DIO_DDRB,Local_PinNumber);
					break;
				case DIO_GroupC:
					Clear_Bit(DIO_DDRC,Local_PinNumber);
					break;
				case DIO_GroupD:
					Clear_Bit(DIO_DDRD,Local_PinNumber);
					break;
				}

			}
			else{
				Request = RequestErrorNotValidState;
			}


		}
		else{
			Request = RequestErrorPinOutOfRange;
		}

	}
	else{
		Request = RequestErrorGroupOutOfRange;
	}
	return Request;
}


u8 DIO_u8SetPinValue(u8 Local_GroupName,u8 Local_PinNumber,u8 Local_PinValue){
	u8 Request;
	if(Local_GroupName <= DIO_GroupD && Local_GroupName >= DIO_GroupA){

		if(Local_PinNumber <= DIO_PIN7 && Local_PinNumber >= DIO_PIN0){

			if(Local_PinValue == High){
				Request = RequestHandled;
				switch(Local_GroupName){
				case DIO_GroupA:
					Set_Bit(DIO_PORTA,Local_PinNumber);
					break;
				case DIO_GroupB:
					Set_Bit(DIO_PORTB,Local_PinNumber);
					break;
				case DIO_GroupC:
					Set_Bit(DIO_PORTC,Local_PinNumber);
					break;
				case DIO_GroupD:
					Set_Bit(DIO_PORTD,Local_PinNumber);
					break;
				}
			}
			else if(Local_PinValue == Low){
				Request = RequestHandled;
				switch(Local_GroupName){
				case DIO_GroupA:
					Clear_Bit(DIO_PORTA,Local_PinNumber);
					break;
				case DIO_GroupB:
					Clear_Bit(DIO_PORTB,Local_PinNumber);
					break;
				case DIO_GroupC:
					Clear_Bit(DIO_PORTC,Local_PinNumber);
					break;
				case DIO_GroupD:
					Clear_Bit(DIO_PORTD,Local_PinNumber);
					break;
				}

			}
			else{
				Request = RequestErrorNotValidValue;
			}


		}
		else{
			Request = RequestErrorPinOutOfRange;
		}

	}
	else{
		Request = RequestErrorGroupOutOfRange;
	}
	return Request;
}

u8 DIO_u8GetPinValue(u8 Local_GroupName,u8 Local_PinNumber,u8* Reference_Value){
	u8 Request;
	if(Local_GroupName <= DIO_GroupD && Local_GroupName >= DIO_GroupA){

		if(Local_PinNumber <= DIO_PIN7 && Local_PinNumber >= DIO_PIN0){
			Request = RequestHandled;
			switch(Local_GroupName){
			case DIO_GroupA:
				*Reference_Value = Get_Bit(DIO_PINA,Local_PinNumber);
				break;
			case DIO_GroupB:
				*Reference_Value = Get_Bit(DIO_PINB,Local_PinNumber);
				break;
			case DIO_GroupC:
				*Reference_Value = Get_Bit(DIO_PINC,Local_PinNumber);
				break;
			case DIO_GroupD:
				*Reference_Value = Get_Bit(DIO_PIND,Local_PinNumber);
				break;
			}
		}
		else{
			Request = RequestErrorPinOutOfRange;
		}

	}
	else{
		Request = RequestErrorGroupOutOfRange;
	}
	return Request;
}

u8 DIO_u8SetPortDir(u8 Local_GroupName,u8 Local_PortState){
	u8 Request;
	if(Local_GroupName <= DIO_GroupD && Local_GroupName >= DIO_GroupA){
		if(Local_PortState <= DIO_GroupOutput){
			Request = RequestHandled;
			switch(Local_GroupName){
			case DIO_GroupA:
				DIO_DDRA = Local_PortState;
				break;
			case DIO_GroupB:
				DIO_DDRB = Local_PortState;
				break;
			case DIO_GroupC:
				DIO_DDRC = Local_PortState;
				break;
			case DIO_GroupD:
				DIO_DDRD = Local_PortState;
				break;
			}
		}
		else{
			Request = RequestErrorNotValidState;
		}


	}
	else{
		Request = RequestErrorGroupOutOfRange;
	}
	return Request;
}

u8 DIO_u8SetPortValue(u8 Local_GroupName,u8 Local_PortState){
	u8 Request;
	if(Local_GroupName <= DIO_GroupD && Local_GroupName >= DIO_GroupA){
		if(Local_PortState <= DIO_GroupHigh){
			Request = RequestHandled;
			switch(Local_GroupName){
			case DIO_GroupA:
				DIO_PORTA = Local_PortState;
				break;
			case DIO_GroupB:
				DIO_PORTB = Local_PortState;
				break;
			case DIO_GroupC:
				DIO_PORTC = Local_PortState;
				break;
			case DIO_GroupD:
				DIO_PORTD = Local_PortState;
				break;
			}
		}
		else{
			Request = RequestErrorNotValidValue;
		}


	}
	else{
		Request = RequestErrorGroupOutOfRange;
	}
	return Request;
}

u8 DIO_u8GetPortValue(u8 Local_GroupName,u8* Reference_Value){
	u8 Request;
	if(Local_GroupName <= DIO_GroupD && Local_GroupName >= DIO_GroupA){
		Request = RequestHandled;
		switch(Local_GroupName){
		case DIO_GroupA:
			*Reference_Value = DIO_PORTA;
			break;
		case DIO_GroupB:
			*Reference_Value = DIO_PORTB;
			break;
		case DIO_GroupC:
			*Reference_Value = DIO_PORTC;
			break;
		case DIO_GroupD:
			*Reference_Value = DIO_PORTD;
			break;
		}
	}
	else{
		Request = RequestErrorGroupOutOfRange;
	}
	return Request;
}

u8 DIO_u8ControlPullUp(u8 Local_GroupName, u8 Local_ConnectionType, u8 Local_PinNumber, u8 Local_PullUpState){
	u8 Request;
	if(Local_GroupName <= DIO_GroupD && Local_GroupName >= DIO_GroupA){
		if(Local_ConnectionType == DIO_PortConnection){
			if(Local_PullUpState == En){
				Request = RequestHandled;
				switch(Local_GroupName){
				case DIO_GroupA:
					DIO_PORTA = DIO_GroupHigh;
					break;
				case DIO_GroupB:
					DIO_PORTB = DIO_GroupHigh;
					break;
				case DIO_GroupC:
					DIO_PORTC = DIO_GroupHigh;
					break;
				case DIO_GroupD:
					DIO_PORTD = DIO_GroupHigh;
					break;
				}
			}
			else if(Local_PullUpState == Dis){
				Request = RequestHandled;
				switch(Local_GroupName){
				case DIO_GroupA:
					DIO_PORTA = DIO_GroupLow;
					break;
				case DIO_GroupB:
					DIO_PORTB = DIO_GroupLow;
					break;
				case DIO_GroupC:
					DIO_PORTC = DIO_GroupLow;
					break;
				case DIO_GroupD:
					DIO_PORTD = DIO_GroupLow;
					break;
				}
			}
			else{
				Request = RequestErrorNotValidPullUpState;
			}

		}
		else if(Local_ConnectionType == DIO_PinConnection){

			if(Local_PinNumber <= DIO_PIN7 && Local_PinNumber >= DIO_PIN0){
				if(Local_PullUpState == En){
					Request = RequestHandled;
					switch(Local_GroupName){
					case DIO_GroupA:
						Set_Bit(DIO_PORTA,Local_PinNumber);
						break;
					case DIO_GroupB:
						Set_Bit(DIO_PORTB,Local_PinNumber);
						break;
					case DIO_GroupC:
						Set_Bit(DIO_PORTC,Local_PinNumber);
						break;
					case DIO_GroupD:
						Set_Bit(DIO_PORTD,Local_PinNumber);
						break;
					}
				}
				else if(Local_PullUpState == Dis){
					Request = RequestHandled;
					switch(Local_GroupName){
					case DIO_GroupA:
						Clear_Bit(DIO_PORTA,Local_PinNumber);
						break;
					case DIO_GroupB:
						Clear_Bit(DIO_PORTB,Local_PinNumber);
						break;
					case DIO_GroupC:
						Clear_Bit(DIO_PORTC,Local_PinNumber);
						break;
					case DIO_GroupD:
						Clear_Bit(DIO_PORTD,Local_PinNumber);
						break;
					}
				}
				else{
					Request = RequestErrorNotValidPullUpState;
				}
			}
			else{
				Request = RequestErrorPinOutOfRange;
			}

		}
		else{
			Request = RequestErrorNotValidConnectionType;
		}

	}
	else{
		Request = RequestErrorGroupOutOfRange;
	}
	return Request;
}



