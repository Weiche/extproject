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

#pragma interrupt sci_dummy(vect = VECT(SCI6,TXI6))
void sci_dummy(void){
	nop();
}
static void SERIAL_HALDMAInit(void) {
	MSTP(DMAC0) = 0;
	ICU.DMRSR0 = VECT(SCI6, TXI6); /* CMI0���荞�ݗv����DMAC�N���v���ɐݒ� */
	DMAC0.DMAMD.WORD = 0x8000; /*----- �]���A�h���X���[�h�̐ݒ� -----*/
	/*----- �]�����[�h�̐ݒ� -----*/
	/* Normal�]�����[�h        */
	/* ���s�[�g�̈�͓]����      */
	/* �f�[�^�]���T�C�Y��8�r�b�g */
	/* DMAC�N���v���͎��Ӌ@�\    */
	DMAC0.DMTMD.BIT.DCTG = 1;
	DMAC0.DMTMD.BIT.DTS = 1;
	DMAC0.DMTMD.BIT.MD = 0;
	DMAC0.DMTMD.BIT.SZ = 0;

}
static void SERIAL_HALSCIInit(uint32_t baud) {
	/***** �[�q�@�\�̏�����*****/
	IOPORT.PFFSCI.BIT.SCI6S = 0; /* P01�� RXD6-A/P01�[�q�Ƃ��đI�� */
	PORT0.ICR.BIT.B1 = 1; /* RXD6-A/P01�[�q�̓��̓o�b�t�@��L���ɂ��� */

	/***** �V���A���R�~���j�P�[�V�����C���^�t�F�[�XSCI6�̏����� *****/
	MSTP(SCI6) = 0; /* SCI6���W���[���X�g�b�v���� */
	/*----- ����M����Ƒ���M�N���b�N�̑I�� -----*/
	SCI6.SCR.BIT.TE = 0; /* ��M�֎~ */
	SCI6.SCR.BIT.RE = 0; /* ���M�֎~ */
	SCI6.SCR.BYTE = 0; /* RXI6�AERI6��M���荞�݋֎~ */
	/* TXI6���M���荞�݋֎~ */
	/* TEI6���M�������荞�݋֎~ */
	/* �����{�[���[�g�W�F�l���[�^�I�� */

	SCI6.SMR.BIT.MP = 0; /*----- ����M�t�H�[�}�b�g�̑I�� -----*/
	SCI6.SMR.BIT.STOP = 0; /* �������������[�h,�f�[�^��8�r�b�g */
	SCI6.SMR.BIT.PE = 0; /* �p���e�B�Ȃ�, 1�X�g�b�v�r�b�g */
	SCI6.SEMR.BIT.ABCS = 1; /* �]���N���b�N = PCLK */
	SCI6.SMR.BIT.CKS = 0;
	SCI6.BRR = (uint16_t) ( SYS_PCLK / ((float) baud * 8.0F * 2.0F) ); /* �]�����x�̐ݒ� */
	/***** SCI6�֘A�̊��荞�݂̏����� *****/
	IR( SCI6, RXI6 )= 0;
	IR( SCI6, TXI6 )= 0;
	IR( SCI6, ERI6 )= 0;
	IPR( SCI6, RXI6 )= 3;
	IPR( SCI6, TXI6 )= 0;
	IPR( SCI6, ERI6 )= 4;
	IEN( SCI6, RXI6 )= 0;
	IEN( SCI6, TXI6 )= 1;
	IEN( SCI6, ERI6 )= 0;

	SCI6.SCR.BYTE = (1 << 4) | (1 << 5) | (1 << 7); /*----- ����M����Ƒ���M�N���b�N�̑I�� -----*/
}
/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * �֐���     : SERIAL_HALInit
 * �@�\       : �V���A���ʐM�p���Ӌ@�\�̏�����
 * ����       : uint32_t baud : baudrate
 * �ԋp�l     : �Ȃ�
 * �g�p�֐�   : �Ȃ�
 * ���ӎ���   :
 * History    :
 *""FUNC COMMENT END""****************************************************************************/
void SERIAL_HALInit(uint32_t baud) {
	SERIAL_HALDMAInit();
	SERIAL_HALSCIInit(baud);
}

int32_t SERIAL_HALTrySend(uint8_t c) {
	/* Error */
	if ( SCI6.SSR.BIT.TDRE == 1) {
		SCI6.TDR = c;
		return ERROR_OK;
	}
	return ERROR_SERIAL_FAIL;
}

int32_t SERIAL_HALTryRead(void) {
	/* Error */
	if ( SCI6.SSR.BIT.RDRF == 1) {
		return (SCI6.RDR & 0xFF);
	}
	return ERROR_SERIAL_FAIL;
}

void SERIAL_HALSendDMA(const uint8_t *p, uint32_t num) {
	ASSERT(p);
	DMAC0.DMSAR = (void *) p;
	/* �]�����̊J�n�A�h���X��ݒ�(�z��pulse�̐擪�v�f�̐擪�A�h���X) */
	DMAC0.DMDAR = (void *) &(SCI6.TDR);
	/* �]����̊J�n�A�h���X��ݒ�(�p���X�o�̓|�[�gPORTB.DR�̃A�h���X) */
	DMAC0.DMCRA = num & 0xFFFF;
	DMAC0.DMCRB = 0x03FF; /* ���s�[�g�]���񐔂�ݒ�(1024��) */
	DMAC0.DMINT.BIT.DTIE = 1; /* �]���I�����荞�ݗv���̔��������� */
	DMAC.DMAST.BIT.DMST = 1; /* DMAC�S�`���l���̓]�������� */
	DMAC0.DMCNT.BIT.DTE = 1;
	DMAC0.DMCSL.BIT.DISEL = 0;
	IR(SCI6,TXI6) = 1;
}
#define BIT_FER		(1<<4)
#define BIT_ORER	(1<<5)
int32_t SERIAL_HALErrorHandle(void) {
	int32_t ret = ERROR_OK;
	volatile uint8_t dummy;
	if( SCI6.SSR.BIT.ORER == 1){
		ret = ERROR_SERIAL_OVERRUN;
		dummy = SCI6.RDR;
		SCI6.SSR.BYTE &= ~(BIT_FER|BIT_ORER);
	}
	if( SCI6.SSR.BIT.FER == 1){
		ret = ERROR_SERIAL_FLAMING;
		SCI6.SSR.BYTE &= ~(BIT_FER|BIT_ORER);
	}
	return ret;
}
/**************************************************************************************************
 end of file
 **************************************************************************************************/
