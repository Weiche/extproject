/*""FILE COMMENT""*********************************************************************************
 *  System Name : このプログラムは教育用です。(転用不可)
 *  File Name   : serial.c
 *  Contents    : デバイスドライバ設計コース 総合演習 プログラム作成
 *              : 課題C:パソコンからのコマンド指示に応じたパルスモータの制御
 *  Model       : 
 *  CPU         : RXファミリ/RX600シリーズ/RX62Nグループ
 *  Compiler    : RXファミリ C/C++コンパイラ
 *  OS          : 使用せず
 *  Programmer  : ルネサス半導体トレーニングセンター
 *  Note        : コンパイラオブジェクトオプション-nostuff指定
 *              : コンパイラオブジェクトオプション-section=L=C指定
 *              : コンパイラ最適化オプション-noschedule指定
 *              : コンパイラ最適化オプション-case=ifthen指定
 **************************************************************************************************
 * Copyright (C) 2011(2012) Renesas Electronics Corporation
 *  and Renesas Solutions Corp. All rights reserved.
 **************************************************************************************************
 *  History     : 
 *""FILE COMMENT END""****************************************************************************/

/***** ファイルの取り込み *****/
#include "CONFIG.h"
#include <stdint.h>
#include "SERIAL_HAL.h"
#include "SERIAL_Driver.h"

/***** 関数原型(プロトタイプ)宣言 *****/
void SERIAL_DriverInit(SERIAL_Driver_t *this) {
	register int32_t ret;
	ASSERT(this);

	/* Initialize Hardware abstract layer */
	SERIAL_HALInit(SERIAL_HAL_BAUD);

	/* Initialize RX circular buffer */
	ret = DATA_CircularBufferInit(&(this->RX_Buffer), this->RX_Memory,
			sizeof(this->RX_Memory));
	ASSERT(ret == ERROR_OK);

	/* Initialize RX TX State */
	(void)ret;
}

void SERIAL_DriverReset(SERIAL_Driver_t *this) {
	ASSERT(this);

}

int32_t SERIAL_DriverSend(SERIAL_Driver_t *this, const uint8_t *buff,
		uint8_t num) {
	/* Assert non-null pointer */
	ASSERT(this);
	/* Assert non-null pointer */
	ASSERT(buff);
	this->TX_State = 1;
	SERIAL_HALSendDMA(buff, num);
	return num;
}

int32_t SERIAL_DriverRecv(SERIAL_Driver_t *this, uint8_t *buff, uint8_t max_num) {
	ASSERT(this);

	ASSERT(buff);
	return 0;
}

void SERIAL_DriverBackground( SERIAL_Driver_t *this ){
	int32_t ret;
	/* Handler Serial hardware errors */
	ret = SERIAL_HALErrorHandle();
	/* Polling Receive */

	/* Polling Transmit */
	(void)ret;
}

int32_t SERIAL_DriverCallback(int32_t SERIAL_Event, void* param){
	return ERROR_OK;
}
/**************************************************************************************************
 end of file
 **************************************************************************************************/
