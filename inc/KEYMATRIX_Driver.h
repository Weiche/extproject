/*
 * KEYMATRIX_Driver.h
 *
 *  Created on: 2015”N7ŒŽ16“ú
 *      Author: First Version Tetsu Gi 2015/07/16
 */

#ifndef KEYMATRIX_DRIVER_H_
#define KEYMATRIX_DRIVER_H_

/* Include					*/
#include <stdint.h>
/* Export Constant			*/
/* Export Macro				*/
/* Export Typedef			*/
/* Public Function Prototype */

void KEYMATRIX_DriverInit(void);
void KEYMATRIX_DriverScan(void);

/* Callback Function Prototype */
/*********************************************
 * function: void KEYMATRIX_Callback( uint32_t code )
 * @brief	when key pressed , called by KEYMATRIX_DriverScan
 * @param	code: which key pressed
 * @return	none
 ********************************************/
extern void KEYMATRIX_Callback(uint32_t code);

#endif /* KEYMATRIX_DRIVER_H_ */
