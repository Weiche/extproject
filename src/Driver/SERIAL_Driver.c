/*""FILE COMMENT""*********************************************************************************
 *  System Name : ���̃v���O�����͋���p�ł��B(�]�p�s��)
 *  File Name   : serial.c
 *  Contents    : �f�o�C�X�h���C�o�݌v�R�[�X �������K �v���O�����쐬
 *              : �ۑ�C:�p�\�R������̃R�}���h�w���ɉ������p���X���[�^�̐���
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
#include <stdint.h>
#include "SERIAL_HAL.h"
#include "SERIAL_Driver.h"

/***** �֐����^(�v���g�^�C�v)�錾 *****/
void SERIAL_DriverInit(SERIAL_Driver_t *this) {
	register int32_t ret;
	ASSERT(this);

	/* Initialize Hardware abstract layer */
	SERIAL_HALInit(SERIAL_HAL_BAUD);

	/* Initialize RX circular buffer */
	ret = DATA_CircularBufferInit(&(this->RX_Buffer), this->RX_Memory,
			sizeof(this->RX_Memory));
	ASSERT(ret == ERROR_OK);

	/* Initialize RX TX State */
	(void)ret;
}

void SERIAL_DriverReset(SERIAL_Driver_t *this) {
	ASSERT(this);

}

int32_t SERIAL_DriverSend(SERIAL_Driver_t *this, const uint8_t *buff,
		uint8_t num) {
	/* Assert non-null pointer */
	ASSERT(this);
	/* Assert non-null pointer */
	ASSERT(buff);
	this->TX_State = 1;
	SERIAL_HALSendDMA(buff, num);
	return num;
}

int32_t SERIAL_DriverRecv(SERIAL_Driver_t *this, uint8_t *buff, uint8_t max_num) {
	ASSERT(this);

	ASSERT(buff);
	return 0;
}

void SERIAL_DriverBackground( SERIAL_Driver_t *this ){
	int32_t ret;
	/* Handler Serial hardware errors */
	ret = SERIAL_HALErrorHandle();
	/* Polling Receive */

	/* Polling Transmit */
	(void)ret;
}

int32_t SERIAL_DriverCallback(int32_t SERIAL_Event, void* param){
	return ERROR_OK;
}
/**************************************************************************************************
 end of file
 **************************************************************************************************/
