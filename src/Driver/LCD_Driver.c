/*""FILE COMMENT""*********************************************************************************
 *  System Name : このプログラムは教育用です。(転用不可)
 *  File Name   : lcd.c
 *  Contents    : デバイスドライバ設計コース 演習1 I/Oポート
 *              : 課題F:LCD表示プログラムの作成
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
#include "LCD_HAL.h"
#include "LCD_Driver.h"
#define LCD_BUFFERSIZE	(32)
static uint8_t __LCD_Buffer[LCD_BUFFERSIZE];

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * 関数名     : LCD__Initial
 * 機能       : LCDの初期設定
 * 引数       : なし
 * 返却値     : なし
 * 使用関数   : LCD_HALWait,LCD_HALWriteNibbleCreg,LCD_DriverWriteCreg
 * 注意事項   : LCD制御は書き込み固定(CPU:出力,LCD:入力)で行います。
 *            : ビジーの解除待ちは指定時間のループ待ちで行います(ビジーフラグ読み出しでは行いません)。
 * History    : 
 *""FUNC COMMENT END""****************************************************************************/
void LCD_DriverInit(void) {

	LCD_HALInit();
	/***** LCDの初期化 *****/
	/*----- LCD 8ビットでコマンド受付 -----*/
	LCD_HALWait(15000); /* 15ms以上のウェイト */
	LCD_HALWriteNibbleCreg(0x03); /* ファンクションセット8bit(0x03) */

	LCD_HALWait(4100); /* 4.1ms以上のウェイト */
	LCD_HALWriteNibbleCreg(0x03); /* ファンクションセット8bit(0x03) */

	LCD_HALWait(100); /* 100μs以上のウェイト */
	LCD_HALWriteNibbleCreg(0x03); /* ファンクションセット8bit(0x03) */

	LCD_HALWait(100); /* 100μs以上のウェイト */
	LCD_HALWriteNibbleCreg(0x02); /* ファンクションセット4bit(0x02) */

	/*----- LCD 4ビットでコマンド受付 -----*/
	LCD_HALWait(100); /* 100μs以上のウェイト */
	LCD_DriverWriteCreg(0x28); /* ファンクションセット4bit */
	/* (2行､5×7ドット)(0x28) */

	LCD_HALWait(100); /* 100μs以上のウェイト */
	LCD_DriverWriteCreg(0x08); /* 表示オフ(0x08) */
	LCD_HALWait(40); /* ビジーの解除待ち(40μs以上のウェイト) */

	LCD_DriverWriteCreg(0x01); /* 表示クリア(0x01) */
	LCD_HALWait(1700); /* ビジーの解除待ち(1.64ms以上のウェイト) */

	LCD_DriverWriteCreg(0x06); /* エントリーモードセット(インクリメント)(0x06) */
	LCD_HALWait(40); /* ビジーの解除待ち(40μs以上のウェイト) */

	LCD_DriverWriteCreg(0x0c); /* 表示オン､カーソルオフ、ブリンクオフ(0x0c) */
	LCD_HALWait(40); /* ビジーの解除待ち(40μs以上のウェイト) */

	LCD_HALRefreshTimerInit();
}

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * 関数名     : LCD__SetCursor
 * 機能       : 表示位置を指定する(内部表示バッファへの位置)
 * 引数       : int x : X軸(左0x0から右0xf)
 *            : int y : Y軸(上0x0から下0x1)
 * 返却値     : なし
 * 使用関数   : LCD_DriverWriteCreg,LCD_HALWait
 * 注意事項   : DDRAMアドレスセット後(LCD_DriverWriteCreg呼び出し後)は、ビジーの解除待ちのため
 *            : 40μs以上のウェイトが必要です。
 * History    : 
 *""FUNC COMMENT END""****************************************************************************/
void LCD_DriverSetCursor(int32_t x, int32_t y) {
	ASSERT((x < 32) && (y < 2));
	LCD_DriverWriteCreg( 0x80 | y * 0x40 + x );
}

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * 関数名     : LCD_DriverWriteString
 * 機能       : 文字列をLCDに表示する
 * 引数       : uint8_t *str : 表示する文字列の先頭アドレス
 * 返却値     : なし
 * 使用関数   : LCD_DriverWriteDreg,LCD_HALWait
 * 注意事項   : 指定された文字列を'\0'まで表示します。終端に'\0'が格納されている文字列を指定する必要が
 *            : あります。
 *            : DDRAMデータ書き込み後(LCD_DriverWriteDreg呼び出し後)は、ビジーの解除待ちのため
 *            : 40μs以上のウェイトが必要です。
 * History    : 
 *""FUNC COMMENT END""****************************************************************************/
void LCD_DriverWriteString(const uint8_t *str) {
	while (*str) {
		LCD_DriverWriteDreg(*str++);
		LCD_HALWait(40);
	}
}

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * 関数名     : LCD_DriverWriteCreg
 * 機能       : コマンドレジスタへの書き込み(4ビット×2)
 * 引数       : unsigned uint8_t data : 書き込む値
 * 返却値     : なし
 * 使用関数   : LCD_HALWriteNibbleCreg
 * 注意事項   : 書き込みは上位4ビット、下位4ビットの順番で行います。
 *            : 本関数の呼び出し後、ビジーの解除待ちをしてください。
 * History    : 
 *""FUNC COMMENT END""****************************************************************************/
void LCD_DriverWriteCreg(uint8_t data) {
	LCD_HALWriteNibbleCreg(data >> 4 & 0x0f);
	LCD_HALWriteNibbleCreg(data & 0x0f);
}

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * 関数名     : LCD_DriverWriteDreg
 * 機能       : データレジスタへの書き込み(4ビット×2)
 * 引数       : unsigned uint8_t data : 書き込む値
 * 返却値     : なし
 * 使用関数   : LCD_HALWriteNibbleDreg
 * 注意事項   : 書き込みは上位4ビット、下位4ビットの順番で行います。
 *            : 本関数の呼び出し後、ビジーの解除待ちをしてください。
 * History    : 
 *""FUNC COMMENT END""****************************************************************************/
void LCD_DriverWriteDreg(uint8_t data) {
	LCD_HALWriteNibbleDreg(data >> 4 & 0x0f);
	LCD_HALWriteNibbleDreg(data & 0x0f);
}

void LCD_DriverAddCGRAM(uint8_t addr, const uint8_t *pdot) {
	register uint8_t cgram_addr;
	cgram_addr = ((addr & 0x07) << 3) | (1 << 6);
	LCD_HALWait(40);
	LCD_DriverWriteCreg(cgram_addr);
	LCD_HALWait(40);

	LCD_DriverWriteDreg(pdot[0]);
	LCD_HALWait(40);
	LCD_DriverWriteDreg(pdot[1]);
	LCD_HALWait(40);
	LCD_DriverWriteDreg(pdot[2]);
	LCD_HALWait(40);
	LCD_DriverWriteDreg(pdot[3]);
	LCD_HALWait(40);
	LCD_DriverWriteDreg(pdot[4]);
	LCD_HALWait(40);
	LCD_DriverWriteDreg(pdot[5]);
	LCD_HALWait(40);
	LCD_DriverWriteDreg(pdot[6]);
	LCD_HALWait(40);
	LCD_DriverWriteDreg(pdot[7]);
	LCD_HALWait(40);
	LCD_DriverWriteCreg(0x80);
	LCD_HALWait(40);
}

void LCD_DriverRefresh(void) {
	static int i = 0, f_cursor = 0;
	if (i == 16 && f_cursor == 0) {
		LCD_DriverSetCursor(0, 1);
		f_cursor = 1;
	} else if (i == 0 && f_cursor == 0) {
		LCD_DriverSetCursor(0, 0);
		f_cursor = 1;
	} else {
		f_cursor = 0;
		LCD_DriverWriteDreg(__LCD_Buffer[i]);
		i++;
		i &= 0x20 - 1;
	}
}

void LCD_DriverBufferWrite(uint8_t pos, uint8_t c) {
	ASSERT( pos < LCD_BUFFERSIZE );
	__LCD_Buffer[pos] = c;

}

void LCD_DriverBufferWriten(uint8_t pos, const uint8_t *buf, uint8_t num ) {
	ASSERT( pos < LCD_BUFFERSIZE );
	while( num-- ){
		__LCD_Buffer[pos++] = *buf++;
	}
}

void LCD_DriverBufferClear(void) {
	register uint32_t* p =  (void*)__LCD_Buffer;
#if (LCD_BUFFERSIZE >= 32)
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
#endif
#if (LCD_BUFFERSIZE >= 64)
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
#endif
#if (LCD_BUFFERSIZE == 96)
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
	*p++ = 0x20202020;
#endif
#if (LCD_BUFFERSIZE > 96 )
#error "Not supported LCD device"
#endif
}

/**************************************************************************************************
 end of file
 **************************************************************************************************/
