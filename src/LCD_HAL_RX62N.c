#include "iodefine.h"
#include "machine.h"
#include <stdint.h>
#define USE_CMT			(0)
#define DELAY_50ns()	nop()
#define DELAY_250ns()	nop();nop();nop()
#define DELAY_500ns()	DELAY_250ns();DELAY_250ns()
#define DELAY_1us()		DELAY_500ns();DELAY_500ns()

void LCD_HALInit( void ){
#if USE_CMT
    /***** CMT2チャネルの初期化 *****/
    MSTP(CMT2) = 0;                        /* CMTユニット1(CMT2チャネル)モジュールストップを解除 */
    CMT2.CMCOR = 60 - 1;                           /* CMT2.CMCORにコンペアマッチ周期を設定(1μ秒) */
    CMT2.CMCR.WORD = 0x00C0;             /* 周辺クロックPCLK=48MHzの8分周を設定 CMT2割り込み許可 */
#endif
    /***** LCD用ポートの初期化 *****/
    PORT5.DR.BYTE  &= 0xf8;                              /* 初期データE="L",R/W="L",RS="L"を設定 */
    PORT5.DDR.BYTE |= 0x07;                       /* E,R/W,RS端子に接続されたP52-P50を出力に設定 */
    PORT9.DDR.BYTE |= 0x0f;                        /* DB7-DB4端子に接続されたP93-P90を出力に設定 */
}

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * 関数名     : LCD_HALWait
 * 機能       : 1μs単位のウェイト
 * 引数       : int time : 待ち時間(1μs×time)
 * 返却値     : なし
 * 使用関数   : なし
 * 注意事項   : なし
 * History    : 
 *""FUNC COMMENT END""****************************************************************************/
void LCD_HALWait(uint32_t time)
{
#if USE_CMT
    CMT.CMSTR1.BIT.STR2 = 1;
    while(time--){
        while(!IR(CMT2, CMI2));
        IR(CMT2, CMI2) = 0;
    }
    CMT.CMSTR1.BIT.STR2 = 0;
    CMT2.CMCNT = 0;
#else
    while( time-- ){
    	DELAY_1us();
    }
#endif
}

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * 関数名     : LCD_HALWriteNibbleCreg
 * 機能       : コマンドレジスタへの書き込み(4ビット)
 * 引数       : uint8_t data : 書き込む値(下位4ビットのみ有効)
 * 返却値     : なし
 * 使用関数   : なし
 * 注意事項   : 1.LCD制御を書き込み固定(CPU:出力,LCD:入力)で行うための初期設定済みです。
 *            :   ・E,R/W,RS端子に接続されたP52-P50の出力方向設定
 *            :   ・DB7-DB4端子に接続されたP93-P90の出力方向設定
 *            :   ・R/W端子の"L"設定(書き込み)
 *            : 2.LCD制御のためのタイミングを確保する必要があります。
 *            :   ・RSセットアップタイム:40ns以上(E端子が立ち上がる前のRS端子"L"の期間)
 *            :   ・イネーブルパルス幅:220ns以上(E端子が"H"の期間)
 *            :   ・イネーブルサイクルタイム:500ns以上(E端子が立ち上がる周期)
 *            : 3.ICLK=96MHzのためnop関数呼び出しのソフトウェアウェイトは約10.4nsです。
 * History    : 
 *""FUNC COMMENT END""****************************************************************************/
void LCD_HALWriteNibbleCreg(uint8_t data)
{
    PORT9.DR.BYTE = data;              /* 書き込む値を出力 */
    PORT5.DR.BIT.B0 = 0;               /* コマンドを選択(RS端子="L") */
    DELAY_50ns();
    PORT5.DR.BIT.B2 = 1;               /* E端子="H" */
    DELAY_250ns();
    PORT5.DR.BIT.B2 = 0;               /* E端子="L" */
    DELAY_250ns();
}

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * 関数名     : LCD_HALWriteNibbleDreg
 * 機能       : データレジスタへの書き込み(4ビット)
 * 引数       : uint8_t data : 書き込む値(下位4ビットのみ有効)
 * 返却値     : なし
 * 使用関数   : なし
 * 注意事項   : 1.LCD制御を書き込み固定(CPU:出力,LCD:入力)で行うための初期設定済みです。
 *            :   ・E,R/W,RS端子に接続されたP52-P50の出力方向設定
 *            :   ・DB7-DB4端子に接続されたP93-P90の出力方向設定
 *            :   ・R/W端子の"L"設定(書き込み)
 *            : 2.LCD制御のためのタイミングを確保する必要があります。
 *            :   ・RSセットアップタイム:40ns以上(E端子が立ち上がる前のRS端子"L"の期間)
 *            :   ・イネーブルパルス幅:220ns以上(E端子が"H"の期間)
 *            :   ・イネーブルサイクルタイム:500ns以上(E端子が立ち上がる周期)
 *            : 3.ICLK=96MHzのためnop関数呼び出しのソフトウェアウェイトは約10.4nsです。
 * History    : 
 *""FUNC COMMENT END""****************************************************************************/
void LCD_HALWriteNibbleDreg(uint8_t data)
{
    PORT9.DR.BYTE = data;              /* 書き込む値を出力 */
    PORT5.DR.BIT.B0 = 1;               /* データを選択(RS端子="H") */
    DELAY_50ns();
    PORT5.DR.BIT.B2 = 1;               /* E端子="H" */
    DELAY_250ns();
    PORT5.DR.BIT.B2 = 0;               /* E端子="L" */
    DELAY_250ns();
}

void LCD_HALRefreshTimerInit(void){
    /***** CMT2チャネルの初期化 *****/
    MSTP(CMT2) = 0;                        /* CMTユニット1(CMT2チャネル)モジュールストップを解除 */
    CMT2.CMCOR = 60 - 1;                           /* CMT2.CMCORにコンペアマッチ周期を設定(1μ秒) */
    CMT2.CMCR.WORD = 0x00C0;             /* 周辺クロックPCLK=48MHzの8分周を設定 CMT2割り込み許可 */
    IR( CMT2,CMI2) = 0;
    IEN( CMT2,CMI2 ) = 1;
}
