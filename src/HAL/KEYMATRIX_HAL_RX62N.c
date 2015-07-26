#include <stdint.h>
#include "CONFIG.h"
#include "KEYMATRIX_HAL.h"


/******************************
 * function: void KEYMATRIX_HALInit(void)
 * @brief		Scan key array
 ******************************/
void KEYMATRIX_HALInit(void){
	
/*****4�~4�L�[�}�g���N�X�̏�����*****/	
	KEYMATRIX_PORT.DDR.BYTE &= 0xF0;                      // P63-P60�����^�[�����C���ɐݒ�
	KEYMATRIX_PORT.ICR.BYTE |= 0x0F;                      // P63-P60�[�q�̓��̓o�b�t�@��L���ɐݒ�
	KEYMATRIX_PORT.DR.BYTE  &= 0x0F;                      //�X�L�����f�[�^�ݒ�
	KEYMATRIX_PORT.DDR.BYTE &= 0x0F;
	KEYMATRIX_PORT.DDR.BYTE |= 0x10;                      //P64�̂݃X�L�������C���ݒ�
	
}

/******************************
 * function: void  KEYMATRIX_HALSetScanline(uint8_t scan_line)
 * @brief		Set scan line,
 * @param
 ******************************/
void KEYMATRIX_HALSetScanline( uint8_t scan_line){
/*****�X�L�������C���o�͐؂�ւ�*****/
    KEYMATRIX_PORT.DDR.BYTE &= 0x0F;                      //��UP67-P64�[�q���ׂĂ���͕����ɐݒ�
    KEYMATRIX_PORT.DR.BYTE |= 0xF0;                       //��UP67-P64�[�q���ׂĂ�1�ɐݒ�
	//KEYMATRIX_PORT.DR.BYTE  &= 0x0F;                      //�X�L�����f�[�^��ݒ�
	/* Che 07/23*/
    KEYMATRIX_PORT.DR.BYTE  &= ~(scan_line);

    KEYMATRIX_PORT.DDR.BYTE |= (scan_line & 0xF0);                 //1�[�q�̂݃X�L�������C���o��
}

/******************************
 * function: void KEYMATRIX_HALGetData(uint8_t data_line)
 * @brief		get line data
 * @param
 ******************************/
void KEYMATRIX_HALGetData( uint8_t *data_line){

   (*data_line) = ((KEYMATRIX_PORT.PORT.BYTE & 0x0F) ^ 0x0F);    //1���C�����̏�Ԃ�ǂݎ�艺��4bit�Ɋi�[//
	                                            //�A�N�e�B�u�𔽓]//
}
