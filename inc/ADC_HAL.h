/*
 * ADC_HAL.h
 *
 *  Created on: 2015”N7ŒŽ16“ú
 *      Author: First Version Tetsu Gi 2015/07/16
 */
#ifndef ADC_HAL_H
#define ADC_HAL_H

#include <stdint.h>
/******************************
 * Function: void ADC_HALInit(void)
 * @brief	Initialize Hardware for ADC
 * - Software trigger
 * - Sampling Time < 10us
 ******************************/
void ADC_HALInit(void) ;
/******************************
 * Function: void ADC_HALSoftStart(void)
 * @brief	Software trigger to start a ADC conversion
 * - Software trigger
 *
 ******************************/
void ADC_HALSoftStart(void) ;
/******************************
 * Function: ADC_HALGetRaw(void)
 * @brief	Get Raw value of ADC
 * @return
 * 	type=int32_t
 * 	minus=> Error
 * 	ERROR_ADC_FAIL  @ERROR.h
 * 	plus=> Value
 ******************************/
int32_t ADC_HALGetRaw(void) ;
/******************************
 * function: ADC_HALGetMaxRawValue(void)
 * @brief	Get Max Raw value( Vin = Vref ) of ADC
 * @return
 * 	type=int32_t
 * @example return 1024 for 10bit ADC
 * @example return 4096 for 12bit ADC
 *
 ******************************/
int32_t ADC_HALGetMaxRawValue(void);
/******************************
 * function: int32_t ADC_HALGetRefVoltage(void)
 * @brief	Get Vref
 * @return
 * 	type=int32_t
 * 	@example return 3300 for 3.3V Vref
 * 	@example return 5000 for 5.0V Vref
 *
 ******************************/
int32_t ADC_HALGetRefVoltage(void);

#endif
