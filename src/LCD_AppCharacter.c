#include "LCD_CustomChar.h"
#include <stdint.h>

const uint8_t LCD_ModelLevelHOR1[] = {
	X____,
	X____,
	X____,
	X____,
	X____,
	X____,
	X____,
	X____
};

const uint8_t LCD_ModelLevelHOR2[] = {
	XX___,
	XX___,
	XX___,
	XX___,
	XX___,
	XX___,
	XX___,
	XX___	
};

const uint8_t LCD_ModelLevelHOR3[] = {
	XXX__,
	XXX__,
	XXX__,
	XXX__,
	XXX__,
	XXX__,
	XXX__,
	XXX__	
};

const uint8_t LCD_ModelLevelHOR4[] = {
	XXXX_,
	XXXX_,
	XXXX_,
	XXXX_,
	XXXX_,
	XXXX_,
	XXXX_,
	XXXX_	
};

void LCD_CustomCharacterInit(void){
	LCD_DriverAddCGRAM(0x01,LCD_ModelLevelHOR1);
	LCD_DriverAddCGRAM(0x02,LCD_ModelLevelHOR2);
	LCD_DriverAddCGRAM(0x03,LCD_ModelLevelHOR3);
	LCD_DriverAddCGRAM(0x04,LCD_ModelLevelHOR4);
}


/* End of file */
