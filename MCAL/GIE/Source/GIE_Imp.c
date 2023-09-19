#include "../../../Common/Bit_Math.h"
#include "../../../Common/STD_types.h"
#include "../../../Common/Macro.h"

#include "../Header/GIE_All.h"

void GIE_voidEN(){
	Set_Bit(GIE_SREG,GIE_I);
}

void GIE_voidDis(){
	Clear_Bit(GIE_SREG,GIE_I);
}
