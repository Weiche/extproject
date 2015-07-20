/***** �t�@�C���̎�荞�� *****/
#include <stdint.h>
#include <machine.h>                        /* �g�ݍ��݊֐��p�w�b�_�t�@�C��<machine.h>�̎�荞�� */
#include "iodefine.h"
#include "WDT.h"
static uint8_t __WDT_FeedValue;

void WDT_Init(int32_t div, uint8_t ticks, uint8_t reset) {
	WDT.WRITE.WINB = 0x5ADF; /* �J�E���^�I�[�o�t���[���Ƀ��Z�b�g */
	WDT.WRITE.WINA = 0xA5F8 | (div & 0x07); /* �E�H�b�`�h�b�O�^�C�}���[�h,�J�E���g�J�n,PCLK/131072 */
	__WDT_FeedValue = 0x100 - ticks;
}

void WDT_Feed(void) {
	WDT.WRITE.WINA = 0x5A00 | (__WDT_FeedValue & 0xFF);
}


/** End of file */
