/*
 * KEYMATRIX_HAL.h
 *
 *  Created on: 2015”N7ŒŽ16“ú
 *      @author: First Version Tetsu Gi 2015/07/16
 */

#ifndef KEYMATRIX_HAL_H_
#define KEYMATRIX_HAL_H_

/* Include					*/
#include <stdint.h>
/* Export Constant			*/
/* Export Macro				*/
/* Export Typedef			*/
/* Public Function Prototype */

/******************************
 * function: void KEYMATRIX_DriverInit(void)
 * @brief		Scan key array
 ******************************/
void KEYMATRIX_HALInit(void);

/******************************
 * function: void KEYMATRIX_HALSetScanline(uint8_t scan_line)
 * @brief		Set scan line,
 ******************************/
void KEYMATRIX_HALSetScanline(uint8_t scan_line);

/******************************
 * function: void KEYMATRIX_HALGetData(uint8_t scan_line)
 * @brief		get line data
 ******************************/
void KEYMATRIX_HALGetData(uint8_t data_line);

#endif /* KEYMATRIX_HAL_H_ */
