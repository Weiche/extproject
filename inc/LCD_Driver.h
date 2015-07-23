#ifndef LCD_DRIVER_H
#define  LCD_DRIVER_H


/* Include					*/
#include <stdint.h>
#include "CONFIG.h"

/* Export Constant			*/

/* Export Macro				*/

/* Export Typedef			*/

/* Public Function Prototype */
void LCD_DriverInit(void); /* LCD�̏����ݒ� */
void LCD_DriverSetCursor(int32_t x, int32_t y); /* �\���ʒu�̎w�� */
void LCD_DriverPuts(const uint8_t *str); /* ������̕\�� */
void LCD_DriverPutc(uint8_t c); /* �����̕\�� */
void LCD_DriverWriteCreg(uint8_t data); /* �R�}���h���W�X�^�ւ̏�������(4�r�b�g�~2) */
void LCD_DriverWriteDreg(uint8_t data); /* �f�[�^���W�X�^�ւ̏�������(4�r�b�g�~2) */
void LCD_DriverAddCGRAM(uint8_t addr, const uint8_t *pdot);
void LCD_DriverRefresh(void);
void LCD_DriverBufferWrite(uint8_t pos, uint8_t c);
void LCD_DriverBufferClear(void) ;
void LCD_DriverAddCGRAM(uint8_t addr, const uint8_t *pdot);

#endif
/* End of File */
