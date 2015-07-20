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
#define MEMORYPOOL_SIZE	(4)
#define MEMORYPOLL_CELLSIZE	(32)
/* Export Macro				*/

/* Export Typedef			*/
struct s_memorypool_cell{
	uint8_t buff[MEMORYPOLL_CELLSIZE];
	int16_t lock;
	int16_t size;
	struct s_memorypool *next;
};
typedef struct s_memorypool_cell DATA_MemoryPoolCell_t;

struct s_memorypool{
	DATA_MemoryPoolCell_t *root;
	DATA_MemoryPoolCell_t cells[MEMORYPOOL_SIZE];
};
typedef struct s_memorypool DATA_MemoryPool_t;

struct s_serial_driver {
	int32_t TX_State;
	int32_t RX_State;
	DATA_CircularBuffer_t RX_Buffer;
	uint8_t RX_Memory[MEMORYPOOL_SIZE * MEMORYPOLL_CELLSIZE];
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
