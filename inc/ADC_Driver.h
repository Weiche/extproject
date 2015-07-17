/*
 * CONTROLLER.h
 *
 *  Created on: 2015”N7ŒŽ16“ú
 *      Author: First Version Tetsu Gi 2015/07/16
 */
#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H
/* Includes */
#include <stdint.h>

/********************************
 * 	Function Prototype
 *
 *******************************/

/******************************
 * function: ADC_DriverInit(void)
 * @brief	ADC driver initialize and HAL initialize,get informations( raw value for Vref , Vref) from HAL
 ******************************/
void ADC_DriverInit(void);

/******************************
 * function: void ADC_DriverSoftStart(void)
 * @brief	Start ADC convert
 ******************************/
void ADC_DriverSoftStart(void);

/******************************
 * function: int32_t ADC_DriverGetVoltage(void)
 * @brief		Get voltage
 * @return		int32_t (voltage * 1000) , minus=> Error
 * @example		4.343V => return 4343
 ******************************/
int32_t ADC_DriverGetVoltage(void);

#endif
