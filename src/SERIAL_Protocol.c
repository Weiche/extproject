/*""FILE COMMENT""*********************************************************************************
 *  System Name : ���̃v���O�����͋���p�ł��B(�]�p�s��)
 *  File Name   : SERIAL.c
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
#include "CONFIG.h"
#include <stdint.h>
#include "SERIAL_Driver.h"
#include "SERIAL_Protocol.h"
void	SERIAL_ProtocolInit(SERIAL_Protocol_t *this){

}
void	SERIAL_ProtocolReset(void){

}

#ifndef SERIAL_ProtocolGetConnectionState
int32_t SERIAL_ProtocolGetConnectionState(void){
	return SERIAL_STATE_CONNONLINE;
}
int32_t SERIAL_ProtocolGetPacketState(void){
	return SERIAL_STATE_CONNOFFLINE;
}
#endif

int32_t SERIAL_ProtocolRecv(data_t *buff){
	return 0;
}/* return receive packet number */
int32_t SERIAL_ProtocolSend(const data_t *buff){
	return 0;
}
/**************************************************************************************************
    end of file
**************************************************************************************************/
