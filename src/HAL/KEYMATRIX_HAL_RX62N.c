#include <stdint.h>
#include "CONFIG.h"
#include "KEYMATRIX_HAL.h"


/******************************
 * function: void KEYMATRIX_HALInit(void)
 * @brief		Scan key array
 ******************************/
void KEYMATRIX_HALInit(void){
	
/*****4�~4�L�[�}�g���N�X�̏�����*****/	
	PORT6.DDR.BYTE &= 0xF0;                      // P63-P60�����^�[�����C���ɐݒ�
	PORT6.ICR.BYTE |= 0x0F;                      // P63-P60�[�q�̓��̓o�b�t�@��L���ɐݒ�
	PORT6.DR.BYTE  &= 0x0F;                      //�X�L�����f�[�^�ݒ�
	PORT6.DDR.BYTE &= 0x0F;
	PORT6.DDR.BYTE |= 0x10;                      //P64�̂݃X�L�������C���ݒ�
	
}

/******************************
 * function: void  KEYMATRIX_HALSetScanline(uint8_t scan_line)
 * @brief		Set scan line,
 * @param
 ******************************/
void KEYMATRIX_HALSetScanline( uint8_t scan_line){
/*****�X�L�������C���o�͐؂�ւ�*****/
    PORT6.DDR.BYTE &= 0x0F;                      //��UP67-P64�[�q���ׂĂ���͕����ɐݒ�
    PORT6.DR.BYTE |= 0xF0;                       //��UP67-P64�[�q���ׂĂ�1�ɐݒ�
	//PORT6.DR.BYTE  &= 0x0F;                      //�X�L�����f�[�^��ݒ�
	/* Che 07/23*/
    PORT6.DR.BYTE  &= ~(scan_line);

    PORT6.DDR.BYTE |= (scan_line & 0xF0);                 //1�[�q�̂݃X�L�������C���o��
}

/******************************
 * function: void KEYMATRIX_HALGetData(uint8_t data_line)
 * @brief		get line data
 * @param
 ******************************/
void KEYMATRIX_HALGetData( uint8_t *data_line){

   (*data_line) = ((PORT6.PORT.BYTE & 0x0F) ^ 0x0F);    //1���C�����̏�Ԃ�ǂݎ�艺��4bit�Ɋi�[//
	                                            //�A�N�e�B�u�𔽓]//
}
