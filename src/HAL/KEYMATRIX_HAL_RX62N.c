#include <stdint.h>
#include "CONFIG.h"
#include "KEYMATRIX_HAL.h"


/******************************
 * function: void KEYMATRIX_HALInit(void)
 * @brief		Scan key array
 ******************************/
void KEYMATRIX_HALInit(void){
	
/*****4×4キーマトリクスの初期化*****/	
	PORT6.DDR.BYTE &= 0xF0;                      // P63-P60をリターンラインに設定
	PORT6.ICR.BYTE |= 0x0F;                      // P63-P60端子の入力バッファを有効に設定
	PORT6.DR.BYTE  &= 0x0F;                      //スキャンデータ設定
	PORT6.DDR.BYTE &= 0x0F;
	PORT6.DDR.BYTE |= 0x10;                      //P64のみスキャンライン設定
	
}

/******************************
 * function: void  KEYMATRIX_HALSetScanline(uint8_t scan_line)
 * @brief		Set scan line,
 * @param
 ******************************/
void KEYMATRIX_HALSetScanline( uint8_t scan_line){
/*****スキャンライン出力切り替え*****/
    PORT6.DDR.BYTE &= 0x0F;                      //一旦P67-P64端子すべてを入力方向に設定
    PORT6.DR.BYTE |= 0xF0;                       //一旦P67-P64端子すべてを1に設定
	//PORT6.DR.BYTE  &= 0x0F;                      //スキャンデータを設定
	/* Che 07/23*/
    PORT6.DR.BYTE  &= ~(scan_line);

    PORT6.DDR.BYTE |= (scan_line & 0xF0);                 //1端子のみスキャンライン出力
}

/******************************
 * function: void KEYMATRIX_HALGetData(uint8_t data_line)
 * @brief		get line data
 * @param
 ******************************/
void KEYMATRIX_HALGetData( uint8_t *data_line){

   (*data_line) = ((PORT6.PORT.BYTE & 0x0F) ^ 0x0F);    //1ライン分の状態を読み取り下位4bitに格納//
	                                            //アクティブを反転//
}
