#include <stdint.h>
#include "CONFIG.h"
#include "ADC_HAL.h"
#include "ADC_Driver.h"

/********************************************************************************************************
 * function: ADC_DriverInit(void)
 * @brief	ADC driver initialize and HAL initialize,get informations( raw value for Vref , Vref) from HAL
 * @todo	ADC_DriverInit body
 ********************************************************************************************************/
void ADC_DriverInit(void) {

	ADC_HALInit();

}

/*********************************************************************************************************
 * function: void ADC_DriverSoftStart(void)
 * @brief	Start ADC convert
 * @todo	ADC_DriverSoftStart(void) body
 *********************************************************************************************************/
void ADC_DriverSoftStart(void) {

	ADC_HALSoftStart();

}

/*********************************************************************************************************
 * function: int32_t ADC_DriverGetVoltage(void)
 * @brief		Get voltage
 * @return		int32_t (voltage * 1000) , minus=> Error
 * @example		4.343V => return 4343
 * @todo		ADC_DriverGetVoltage(void) body
 *********************************************************************************************************/
int32_t ADC_DriverGetVoltage(void) {
	//TODO Optimize
	int32_t ret;
	ret = ADC_HALGetRaw();
	if (ret < 0) {
		return ERROR_ADC_FAIL;
	} else {
		return (ret * ADC_HALGetRefVoltage() ) / (ADC_HALGetMaxRawValue() - 1);
	}
}

