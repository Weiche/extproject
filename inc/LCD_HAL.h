#ifndef LCD_HAL_H
#define  LCD_HAL_H

#include <stdint.h>
/***** Function Prototype *****/

void LCD_HALInit(void);
void LCD_HALWriteNibbleCreg(uint8_t data); /* コマンドレジスタへの書き込み(4ビット) */
void LCD_HALWriteNibbleDreg(uint8_t data); /* データレジスタへの書き込み(4ビット) */
void LCD_HALWait(uint32_t time);
void LCD_HALRefreshTimerInit(void);

#endif
/* End of File */
