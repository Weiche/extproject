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
#if (ADC_OVERSAMPLING <= 1)
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
#else
 int32_t ADC_DriverGetVoltage(void) {
 	//TODO Optimize
 	int32_t ret;

 	static uint32_t ad[ADC_OVERSAMPLING];
 	static uint32_t fix_ad;
 	static uint8_t i;
 	static uint32_t cnt = 0;
 	ret = ADC_HALGetRaw();
 	if (ret < 0) {
 		return ERROR_ADC_FAIL;
 	}
 	ad[cnt] = ret;
	if (ADC_OVERSAMPLING <= ++cnt){
 	  cnt=0;
 	  fix_ad=0;
 	  for(i=0;i<ADC_OVERSAMPLING;i++){
 	  fix_ad += ad[i];
 	  }

 	  fix_ad/=ADC_OVERSAMPLING;
 	  ret=fix_ad;

 	  }
 	return (ret * ADC_HALGetRefVoltage() ) / (ADC_HALGetMaxRawValue() - 1);
 }
#endif
