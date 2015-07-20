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
#include <stdint.h>
#include "CONFIG.h"
#include "SERIAL_HAL.h"
static void SERIAL_HALDMAInit(void) {

}

void SERIAL_HALInit(uint32_t baud) {
	SERIAL_HALDMAInit();
}

int32_t SERIAL_HALTrySend(uint8_t c) {
	/* Error */
	return 0;
}

int32_t SERIAL_HALTryRead(void) {
	return 0;
}

void SERIAL_HALSendDMA(const uint8_t *p, uint32_t num) {

}

int32_t SERIAL_HALErrorHandle(void){
	/* if some error */
	return ERROR_SERIAL_FAIL;
	/* else */
	return ERROR_OK;
}
/**************************************************************************************************
 end of file
 **************************************************************************************************/
