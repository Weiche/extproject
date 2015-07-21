/*
 * SERIAL_HAL.h
 *
 *  Created on: 2015”N7ŒŽ16“ú
 *      Author: First Version Tetsu Gi 2015/07/16
 */

#ifndef SERIAL_HAL_H_
#define SERIAL_HAL_H_

/* Include					*/
#include <stdint.h>
#include "CONFIG.h"
/* Export Constant			*/
#define SERIAL_BAUD_9600		(9600)
#define SERIAL_BAUD_19200		(19200)
#define SERIAL_BAUD_38400		(38400)
#define SERIAL_BAUD_115200		(115200)

/* Export Macro				*/
#define SERIAL_HAL_DMA_TC_FLAG		(DMA_TCFLAG)
/* Export Typedef			*/
/* Public Function Prototype */

void SERIAL_HALInit(uint32_t baud);
int32_t SERIAL_HALTrySend(uint8_t c);
int32_t SERIAL_HALTryRead(void);
void SERIAL_HALSendDMA(const uint8_t *p, uint32_t num);

/* Callback Function Prototype */
extern int32_t SERIAL_DriverCallback(int32_t SERIAL_Event, void* param);

#endif /* SERIAL_HAL_H_ */
