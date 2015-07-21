/*
 * SERIAL_Driver.h
 *
 *  Created on: 2015”N7ŒŽ16“ú
 *      Author: First Version Tetsu Gi 2015/07/16
 */

#ifndef SERIAL_DRIVER_H_
#define SERIAL_DRIVER_H_

/* Include					*/
#include "DATA_CircularBuffer.h"
#include "SYSTEM_ControlFlag.h"
/* Export Constant			*/
#define SERIAL_RX_BUFFERSIZE	(128)

/* Export Macro				*/

/* Export Typedef			*/
struct s_serial_driver {
	int32_t TX_State;
	int32_t RX_State;
	uint32_t Error_State;
	DATA_CircularBuffer_t RX_Buffer;
	uint8_t RX_Memory[SERIAL_RX_BUFFERSIZE];
};
typedef struct s_serial_driver SERIAL_Driver_t;

/* Public Function Prototype */
void	SERIAL_DriverInit	( SERIAL_Driver_t *this );
void	SERIAL_DriverReset	( SERIAL_Driver_t *this );
int32_t	SERIAL_DriverSend	( SERIAL_Driver_t *this , const uint8_t *buff	, uint8_t num);
int32_t	SERIAL_DriverRecv	( SERIAL_Driver_t *this , uint8_t *buff			, uint8_t max_num);
void	SERIAL_DriverFlush	( SERIAL_Driver_t *this );
void SERIAL_DriverBackground( SERIAL_Driver_t *this );
#endif /* SERIAL_DRIVER_H_ */
