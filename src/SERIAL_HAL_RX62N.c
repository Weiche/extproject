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
#include "iodefine.h"
#include "CONFIG.h"
#include <stdint.h>
#include "SERIAL_HAL.h"

void SERIAL_HALInit(uint32_t baud) {
}

void SERIAL_HALDMAInit(void) {
}

int32_t SERIAL_HALTrySend(uint8_t c) {

	return 0;
}

int32_t SERIAL_HALTryRead(void) {
	return 0;
}

void SERIAL_HALSendDMA(const uint8_t *p, uint32_t num) {

}
/**************************************************************************************************
 end of file
 **************************************************************************************************/
