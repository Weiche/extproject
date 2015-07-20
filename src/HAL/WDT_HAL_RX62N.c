/***** ファイルの取り込み *****/
#include <stdint.h>
#include <machine.h>                        /* 組み込み関数用ヘッダファイル<machine.h>の取り込み */
#include "iodefine.h"
#include "WDT.h"
static uint8_t __WDT_FeedValue;

void WDT_Init(int32_t div, uint8_t ticks, uint8_t reset) {
	WDT.WRITE.WINB = 0x5ADF; /* カウンタオーバフロー時にリセット */
	WDT.WRITE.WINA = 0xA5F8 | (div & 0x07); /* ウォッチドッグタイマモード,カウント開始,PCLK/131072 */
	__WDT_FeedValue = 0x100 - ticks;
}

void WDT_Feed(void) {
	WDT.WRITE.WINA = 0x5A00 | (__WDT_FeedValue & 0xFF);
}


/** End of file */
