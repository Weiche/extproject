/*""FILE COMMENT""*********************************************************************************
 *  System Name : ���̃v���O�����͋���p�ł��B(�]�p�s��)
 *  File Name   : lcd.c
 *  Contents    : �f�o�C�X�h���C�o�݌v�R�[�X ���K1 I/O�|�[�g
 *              : �ۑ�F:LCD�\���v���O�����̍쐬
 *  Model       : 
 *  CPU         : RX�t�@�~��/RX600�V���[�Y/RX62N�O���[�v
 *  Compiler    : RX�t�@�~�� C/C++�R���p�C��
 *  OS          : �g�p����
 *  Programmer  : ���l�T�X�����̃g���[�j���O�Z���^�[
 *  Note        : �R���p�C���I�u�W�F�N�g�I�v�V����-nostuff�w��
 *              : �R���p�C���I�u�W�F�N�g�I�v�V����-section=L=C�w��
 *              : �R���p�C���œK���I�v�V����-noschedule�w��
 *              : �R���p�C���œK���I�v�V����-case=ifthen�w��
 **************************************************************************************************
 * Copyright (C) 2011(2012) Renesas Electronics Corporation
 *  and Renesas Solutions Corp. All rights reserved.
 **************************************************************************************************
 *  History     : 
 *""FILE COMMENT END""****************************************************************************/

/***** �t�@�C���̎�荞�� *****/
#include "CONFIG.h"
#include "LCD_HAL.h"
#include "LCD_Driver.h"
#define LCD_BUFFERSIZE	(32)
static uint8_t __LCD_Buffer[LCD_BUFFERSIZE];

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * �֐���     : LCD__Initial
 * �@�\       : LCD�̏����ݒ�
 * ����       : �Ȃ�
 * �ԋp�l     : �Ȃ�
 * �g�p�֐�   : LCD_HALWait,LCD_HALWriteNibbleCreg,LCD_DriverWriteCreg
 * ���ӎ���   : LCD����͏������݌Œ�(CPU:�o��,LCD:����)�ōs���܂��B
 *            : �r�W�[�̉����҂��͎w�莞�Ԃ̃��[�v�҂��ōs���܂�(�r�W�[�t���O�ǂݏo���ł͍s���܂���)�B
 * History    : 
 *""FUNC COMMENT END""****************************************************************************/
void LCD_DriverInit(void) {

	LCD_HALInit();
	/***** LCD�̏����� *****/
	/*----- LCD 8�r�b�g�ŃR�}���h��t -----*/
	LCD_HALWait(15000); /* 15ms�ȏ�̃E�F�C�g */
	LCD_HALWriteNibbleCreg(0x03); /* �t�@���N�V�����Z�b�g8bit(0x03) */

	LCD_HALWait(4100); /* 4.1ms�ȏ�̃E�F�C�g */
	LCD_HALWriteNibbleCreg(0x03); /* �t�@���N�V�����Z�b�g8bit(0x03) */

	LCD_HALWait(100); /* 100��s�ȏ�̃E�F�C�g */
	LCD_HALWriteNibbleCreg(0x03); /* �t�@���N�V�����Z�b�g8bit(0x03) */

	LCD_HALWait(100); /* 100��s�ȏ�̃E�F�C�g */
	LCD_HALWriteNibbleCreg(0x02); /* �t�@���N�V�����Z�b�g4bit(0x02) */

	/*----- LCD 4�r�b�g�ŃR�}���h��t -----*/
	LCD_HALWait(100); /* 100��s�ȏ�̃E�F�C�g */
	LCD_DriverWriteCreg(0x28); /* �t�@���N�V�����Z�b�g4bit */
	/* (2�s�5�~7�h�b�g)(0x28) */

	LCD_HALWait(100); /* 100��s�ȏ�̃E�F�C�g */
	LCD_DriverWriteCreg(0x08); /* �\���I�t(0x08) */
	LCD_HALWait(40); /* �r�W�[�̉����҂�(40��s�ȏ�̃E�F�C�g) */

	LCD_DriverWriteCreg(0x01); /* �\���N���A(0x01) */
	LCD_HALWait(1700); /* �r�W�[�̉����҂�(1.64ms�ȏ�̃E�F�C�g) */

	LCD_DriverWriteCreg(0x06); /* �G���g���[���[�h�Z�b�g(�C���N�������g)(0x06) */
	LCD_HALWait(40); /* �r�W�[�̉����҂�(40��s�ȏ�̃E�F�C�g) */

	LCD_DriverWriteCreg(0x0c); /* �\���I����J�[�\���I�t�A�u�����N�I�t(0x0c) */
	LCD_HALWait(40); /* �r�W�[�̉����҂�(40��s�ȏ�̃E�F�C�g) */

	LCD_HALRefreshTimerInit();
}

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * �֐���     : LCD__SetCursor
 * �@�\       : �\���ʒu���w�肷��(�����\���o�b�t�@�ւ̈ʒu)
 * ����       : int x : X��(��0x0����E0xf)
 *            : int y : Y��(��0x0���牺0x1)
 * �ԋp�l     : �Ȃ�
 * �g�p�֐�   : LCD_DriverWriteCreg,LCD_HALWait
 * ���ӎ���   : DDRAM�A�h���X�Z�b�g��(LCD_DriverWriteCreg�Ăяo����)�́A�r�W�[�̉����҂��̂���
 *            : 40��s�ȏ�̃E�F�C�g���K�v�ł��B
 * History    : 
 *""FUNC COMMENT END""****************************************************************************/
void LCD_DriverSetCursor(int32_t x, int32_t y) {
	ASSERT((x < 32) && (y < 2));
	LCD_DriverWriteCreg( 0x80 | y * 0x40 + x );
}

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * �֐���     : LCD_DriverWriteString
 * �@�\       : �������LCD�ɕ\������
 * ����       : uint8_t *str : �\�����镶����̐擪�A�h���X
 * �ԋp�l     : �Ȃ�
 * �g�p�֐�   : LCD_DriverWriteDreg,LCD_HALWait
 * ���ӎ���   : �w�肳�ꂽ�������'\0'�܂ŕ\�����܂��B�I�[��'\0'���i�[����Ă��镶������w�肷��K�v��
 *            : ����܂��B
 *            : DDRAM�f�[�^�������݌�(LCD_DriverWriteDreg�Ăяo����)�́A�r�W�[�̉����҂��̂���
 *            : 40��s�ȏ�̃E�F�C�g���K�v�ł��B
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
 * �֐���     : LCD_DriverWriteCreg
 * �@�\       : �R�}���h���W�X�^�ւ̏�������(4�r�b�g�~2)
 * ����       : unsigned uint8_t data : �������ޒl
 * �ԋp�l     : �Ȃ�
 * �g�p�֐�   : LCD_HALWriteNibbleCreg
 * ���ӎ���   : �������݂͏��4�r�b�g�A����4�r�b�g�̏��Ԃōs���܂��B
 *            : �{�֐��̌Ăяo����A�r�W�[�̉����҂������Ă��������B
 * History    : 
 *""FUNC COMMENT END""****************************************************************************/
void LCD_DriverWriteCreg(uint8_t data) {
	LCD_HALWriteNibbleCreg(data >> 4 & 0x0f);
	LCD_HALWriteNibbleCreg(data & 0x0f);
}

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * �֐���     : LCD_DriverWriteDreg
 * �@�\       : �f�[�^���W�X�^�ւ̏�������(4�r�b�g�~2)
 * ����       : unsigned uint8_t data : �������ޒl
 * �ԋp�l     : �Ȃ�
 * �g�p�֐�   : LCD_HALWriteNibbleDreg
 * ���ӎ���   : �������݂͏��4�r�b�g�A����4�r�b�g�̏��Ԃōs���܂��B
 *            : �{�֐��̌Ăяo����A�r�W�[�̉����҂������Ă��������B
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
