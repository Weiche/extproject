/*""FILE COMMENT""*********************************************************************************
 *  System Name : このプログラムは教育用です。(転用不可)
 *  File Name   : SERIAL.c
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
#include "CONFIG.h"
#include <stdint.h>
#include "SERIAL_Driver.h"
#include "SERIAL_Protocol.h"
void	SERIAL_ProtocolInit(SERIAL_Protocol_t *this){

}
void	SERIAL_ProtocolReset(void){

}

#ifndef SERIAL_ProtocolGetConnectionState
int32_t SERIAL_ProtocolGetConnectionState(void){
	return SERIAL_STATE_CONNONLINE;
}
int32_t SERIAL_ProtocolGetPacketState(void){
	return SERIAL_STATE_CONNOFFLINE;
}
#endif

int32_t SERIAL_ProtocolRecv(data_t *buff){
	return 0;
}/* return receive packet number */
int32_t SERIAL_ProtocolSend(const data_t *buff){
	return 0;
}
/**************************************************************************************************
    end of file
**************************************************************************************************/
