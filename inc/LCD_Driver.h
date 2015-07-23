#ifndef LCD_DRIVER_H
#define  LCD_DRIVER_H


/* Include					*/
#include <stdint.h>
#include "CONFIG.h"

/* Export Constant			*/

/* Export Macro				*/

/* Export Typedef			*/

/* Public Function Prototype */
void LCD_DriverInit(void); /* LCDの初期設定 */
void LCD_DriverSetCursor(int32_t x, int32_t y); /* 表示位置の指定 */
void LCD_DriverPuts(const uint8_t *str); /* 文字列の表示 */
void LCD_DriverPutc(uint8_t c); /* 文字の表示 */
void LCD_DriverWriteCreg(uint8_t data); /* コマンドレジスタへの書き込み(4ビット×2) */
void LCD_DriverWriteDreg(uint8_t data); /* データレジスタへの書き込み(4ビット×2) */
void LCD_DriverAddCGRAM(uint8_t addr, const uint8_t *pdot);
void LCD_DriverRefresh(void);
void LCD_DriverBufferWrite(uint8_t pos, uint8_t c);
void LCD_DriverBufferClear(void) ;
void LCD_DriverAddCGRAM(uint8_t addr, const uint8_t *pdot);

#endif
/* End of File */
