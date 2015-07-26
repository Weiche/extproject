#include <stdint.h>
#include <machine.h>
#include "iodefine.h"
#include "CONFIG.h"
#include "ERROR.h"
#include "KEYMATRIX_HAL.h"
#include "KEYMATRIX_Driver.h"

/******************************
 * function: void KEYMATRIX_DriverInit(void)
 * @brief		Scan key array
 * @author
 ******************************/
void KEYMATRIX_DriverInit(void) {
	KEYMATRIX_HALInit();                     //HAL初期化呼び出し

}
/*********************************************
 * function: int32_t KEYMATRIX_DriverScan( void )
 * @brief	Scan key array, callback in function
 ********************************************/
void KEYMATRIX_DriverScan(void) {
	static uint8_t temp_sw = 0x00;
	static uint16_t sw = 0;

	static uint8_t line = 0x10;
	uint32_t i;
	static uint16_t old_sw = 0x0000;                   //前回のスイッチの状態
	static uint32_t c_agree = 0;
	static uint8_t reset_flag = 1;

	/* scan */
	line = 0x10;
	sw = 0;
	for (i = 0; i < 4; i++) {
		KEYMATRIX_HALSetScanline(line);
		KEYMATRIX_HALGetData(&temp_sw);
		sw <<= 4;
		sw |= (temp_sw&0x0F);
		line <<= 1;
	}
	
	
	if(2 <= BIT_Count16Bit(sw)){
		c_agree = 5;
		reset_flag = 1;
	}
	else if ( !sw ) reset_flag = 0;
	/* chattering and edge sensing */
	if (sw != old_sw) {
		c_agree = 0;
		old_sw = sw;
	}
	else if(sw && reset_flag == 0){
		c_agree++;
		c_agree = (c_agree > 100) ? 100 : c_agree;
		if (4 == c_agree) {
			KEYMATRIX_Callback((uint32_t) sw);
			old_sw = sw;
		}
	}
	sw = 0x00;
	
}
