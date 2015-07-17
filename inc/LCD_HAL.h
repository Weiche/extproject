#ifndef LCD_HAL_H
#define  LCD_HAL_H

#include <stdint.h>
/***** Function Prototype *****/

void LCD_HALInit(void);
void LCD_HALWriteNibbleCreg(const uint8_t data); /* �R�}���h���W�X�^�ւ̏�������(4�r�b�g) */
void LCD_HALWriteNibbleDreg(const uint8_t data); /* �f�[�^���W�X�^�ւ̏�������(4�r�b�g) */
void LCD_HALWait(const int32_t time);
void LCD_HALRefreshTimerInit(void);

#endif
/* End of File */
