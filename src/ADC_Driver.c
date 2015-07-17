#include "iodefine.h"
#include "machine.h"
#include "CONFIG.h"
#include <stdint.h>
#include "ADC_Driver.h"

/******************************
 * function: ADC_DriverInit(void)
 * @brief	ADC driver initialize and HAL initialize,get informations( raw value for Vref , Vref) from HAL
 * @todo	ADC_DriverInit body
 ******************************/
void ADC_DriverInit(void) {

}

/******************************
 * function: void ADC_DriverSoftStart(void)
 * @brief	Start ADC convert
 * @todo	ADC_DriverSoftStart(void) body
 ******************************/
void ADC_DriverSoftStart(void) {

}

/******************************
 * function: int32_t ADC_DriverGetVoltage(void)
 * @brief		Get voltage
 * @return		int32_t (voltage * 1000) , minus=> Error
 * @example		4.343V => return 4343
 * @todo		ADC_DriverGetVoltage(void) body
 ******************************/
int32_t ADC_DriverGetVoltage(void) {

	return ERROR_ADC_FAIL;
}
