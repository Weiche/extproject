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
#include <stdint.h>
#include "CONFIG.h"
#include "SERIAL_HAL.h"

#pragma interrupt sci_dummy(vect = VECT(SCI6,TXI6))
void sci_dummy(void){
	nop();
}
static void SERIAL_HALDMAInit(void) {
	MSTP(DMAC0) = 0;
	ICU.DMRSR0 = VECT(SCI6, TXI6); /* CMI0割り込み要求をDMAC起動要因に設定 */
	DMAC0.DMAMD.WORD = 0x8000; /*----- 転送アドレスモードの設定 -----*/
	/*----- 転送モードの設定 -----*/
	/* Normal転送モード        */
	/* リピート領域は転送元      */
	/* データ転送サイズは8ビット */
	/* DMAC起動要因は周辺機能    */
	DMAC0.DMTMD.BIT.DCTG = 1;
	DMAC0.DMTMD.BIT.DTS = 1;
	DMAC0.DMTMD.BIT.MD = 0;
	DMAC0.DMTMD.BIT.SZ = 0;

}
static void SERIAL_HALSCIInit(uint32_t baud) {
	/***** 端子機能の初期化*****/
	IOPORT.PFFSCI.BIT.SCI6S = 0; /* P01を RXD6-A/P01端子として選択 */
	PORT0.ICR.BIT.B1 = 1; /* RXD6-A/P01端子の入力バッファを有効にする */

	/***** シリアルコミュニケーションインタフェースSCI6の初期化 *****/
	MSTP(SCI6) = 0; /* SCI6モジュールストップ解除 */
	/*----- 送受信制御と送受信クロックの選択 -----*/
	SCI6.SCR.BIT.TE = 0; /* 受信禁止 */
	SCI6.SCR.BIT.RE = 0; /* 送信禁止 */
	SCI6.SCR.BYTE = 0; /* RXI6、ERI6受信割り込み禁止 */
	/* TXI6送信割り込み禁止 */
	/* TEI6送信完了割り込み禁止 */
	/* 内蔵ボーレートジェネレータ選択 */

	SCI6.SMR.BIT.MP = 0; /*----- 送受信フォーマットの選択 -----*/
	SCI6.SMR.BIT.STOP = 0; /* 調歩同期式モード,データ長8ビット */
	SCI6.SMR.BIT.PE = 0; /* パリティなし, 1ストップビット */
	SCI6.SEMR.BIT.ABCS = 1; /* 転送クロック = PCLK */
	SCI6.SMR.BIT.CKS = 0;
	SCI6.BRR = (uint16_t) ( SYS_PCLK / ((float) baud * 8.0F * 2.0F) ); /* 転送速度の設定 */
	/***** SCI6関連の割り込みの初期化 *****/
	IR( SCI6, RXI6 )= 0;
	IR( SCI6, TXI6 )= 0;
	IR( SCI6, ERI6 )= 0;
	IPR( SCI6, RXI6 )= 3;
	IPR( SCI6, TXI6 )= 0;
	IPR( SCI6, ERI6 )= 4;
	IEN( SCI6, RXI6 )= 0;
	IEN( SCI6, TXI6 )= 1;
	IEN( SCI6, ERI6 )= 0;

	SCI6.SCR.BYTE = (1 << 4) | (1 << 5) | (1 << 7); /*----- 送受信制御と送受信クロックの選択 -----*/
}
/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * 関数名     : SERIAL_HALInit
 * 機能       : シリアル通信用周辺機能の初期化
 * 引数       : uint32_t baud : baudrate
 * 返却値     : なし
 * 使用関数   : なし
 * 注意事項   :
 * History    :
 *""FUNC COMMENT END""****************************************************************************/
void SERIAL_HALInit(uint32_t baud) {
	SERIAL_HALDMAInit();
	SERIAL_HALSCIInit(baud);
}

int32_t SERIAL_HALTrySend(uint8_t c) {
	/* Error */
	if ( SCI6.SSR.BIT.TDRE == 1) {
		SCI6.TDR = c;
		return ERROR_OK;
	}
	return ERROR_SERIAL_FAIL;
}

int32_t SERIAL_HALTryRead(void) {
	/* Error */
	if ( SCI6.SSR.BIT.RDRF == 1) {
		return (SCI6.RDR & 0xFF);
	}
	return ERROR_SERIAL_FAIL;
}

void SERIAL_HALSendDMA(const uint8_t *p, uint32_t num) {
	ASSERT(p);
	DMAC0.DMSAR = (void *) p;
	/* 転送元の開始アドレスを設定(配列pulseの先頭要素の先頭アドレス) */
	DMAC0.DMDAR = (void *) &(SCI6.TDR);
	/* 転送先の開始アドレスを設定(パルス出力ポートPORTB.DRのアドレス) */
	DMAC0.DMCRA = num & 0xFFFF;
	DMAC0.DMCRB = 0x03FF; /* リピート転送回数を設定(1024回) */
	DMAC0.DMINT.BIT.DTIE = 1; /* 転送終了割り込み要求の発生を許可 */
	DMAC.DMAST.BIT.DMST = 1; /* DMAC全チャネルの転送を許可 */
	DMAC0.DMCNT.BIT.DTE = 1;
	DMAC0.DMCSL.BIT.DISEL = 0;
	IR(SCI6,TXI6) = 1;
}
#define BIT_FER		(1<<4)
#define BIT_ORER	(1<<5)
int32_t SERIAL_HALErrorHandle(void) {
	int32_t ret = ERROR_OK;
	volatile uint8_t dummy;
	if( SCI6.SSR.BIT.ORER == 1){
		ret = ERROR_SERIAL_OVERRUN;
		dummy = SCI6.RDR;
		SCI6.SSR.BYTE &= ~(BIT_FER|BIT_ORER);
	}
	if( SCI6.SSR.BIT.FER == 1){
		ret = ERROR_SERIAL_FLAMING;
		SCI6.SSR.BYTE &= ~(BIT_FER|BIT_ORER);
	}
	return ret;
}
/**************************************************************************************************
 end of file
 **************************************************************************************************/
