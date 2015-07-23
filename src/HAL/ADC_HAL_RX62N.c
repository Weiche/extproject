#include <stdint.h>
#include "CONFIG.h"
#include "ADC_HAL.h"

void ADC_HALInit(void) {
	/***** 10�r�b�gA/D�R���o�[�^�̏����ݒ� *****/
	/* AD0���W���[���X�g�b�v���� */
	MSTP(AD0) = 0;
	/* ADTRG0#����̃g���K�I�� ,PCLK/8(6MHz��4MHz),�V���O�����[�h�I�� */
	AD0.ADCR.BIT.TRGS = 0x3;
	AD0.ADCR.BIT.MODE = 0;
	AD0.ADCR.BIT.CKS = 0;
	/* AN0�I��, �ϊ���~, ADI0���荞�ݗv���̔��������� */
	AD0.ADCSR.BIT.CH = 0;
	AD0.ADCSR.BIT.ADIE = 1;
	/* ���荞�݃X�e�[�^�X�t���O�N���A */
	IR ( AD0, ADI0 )= 0;
	IEN( AD0, ADI0 )= 0;
	IPR( AD0, ADI0 )= 2;
}

void ADC_HALSoftStart(void) {
	AD0.ADCSR.BIT.ADST = 1;
}

int32_t ADC_HALGetRaw(void) {
	static uint32_t cnt = 0;
	static uint8_t i;
	static uint32_t fix_ad;
	static uint32_t ad[ADC_OVERSAMPLING];

	if ( IR ( AD0, ADI0 )== 1 ) {

		IR(AD0,ADI0)=0;
		ad[cnt] = (AD0.ADDRA);
		if(ADC_OVERSAMPLING <= ++cnt) {
			cnt=0;
			fix_ad=0;

			for(i=0;i<ADC_OVERSAMPLING;i++) {

				fix_ad += ad[i];

			}

			fix_ad /= ADC_OVERSAMPLING;

		}
	}

	else {
		return ERROR_ADC_FAIL;
	}

	return fix_ad;

}
int32_t ADC_HALGetMaxRawValue(void) {

	return (1 << ADC_RESOLUTION_BIT);

}
int32_t ADC_HALGetRefVoltage(void) {

	return (uint16_t) (ADC_VOLTAGE_REF * 1000);

}

