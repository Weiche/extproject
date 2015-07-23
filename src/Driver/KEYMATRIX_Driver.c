#include <stdint.h>
#include "CONFIG.h"
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
	/* chattering and edge sensing */
	if (sw != old_sw) {
		c_agree = 0;
		old_sw = sw;
	} else {
		c_agree++;
		c_agree = (c_agree > 100) ? 100 : c_agree;
		if (4 == c_agree) {

			if (sw) {
				KEYMATRIX_Callback((uint32_t) sw);
			}
		}
	}
	sw = 0x00;
	/* multi-key */
	if (2 <= BIT_Count16Bit(sw)) {          //渡り押し時にデータを返す
		return;
	}

}
