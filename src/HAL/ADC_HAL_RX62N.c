#include <stdint.h>
#include "CONFIG.h"
#include "ADC_HAL.h"

void ADC_HALInit(void) {
	/***** 10ビットA/Dコンバータの初期設定 *****/
	/* AD0モジュールストップ解除 */
	MSTP(AD0) = 0;
	/* ADTRG0#からのトリガ選択 ,PCLK/8(6MHz≧4MHz),シングルモード選択 */
	AD0.ADCR.BIT.TRGS = 0x3;
	AD0.ADCR.BIT.MODE = 0;
	AD0.ADCR.BIT.CKS = 0;
	/* AN0選択, 変換停止, ADI0割り込み要求の発生を許可 */
	AD0.ADCSR.BIT.CH = 0;
	AD0.ADCSR.BIT.ADIE = 1;
	/* 割り込みステータスフラグクリア */
	IR ( AD0, ADI0 )= 0;
	IEN( AD0, ADI0 )= 0;
	IPR( AD0, ADI0 )= 2;
}

void ADC_HALSoftStart(void) {
	AD0.ADCSR.BIT.ADST = 1;
}

int32_t ADC_HALGetRaw(void)
{
	if ( IR ( AD0, ADI0 )== 1 ) {
		return AD0.ADDRA & 0x3FF;
	}
	return ERROR_ADC_FAIL;
}
int32_t ADC_HALGetMaxRawValue(void) {

	return (1 << ADC_RESOLUTION_BIT);

}
int32_t ADC_HALGetRefVoltage(void) {

	return (uint16_t) (ADC_VOLTAGE_REF * 1000);

}

