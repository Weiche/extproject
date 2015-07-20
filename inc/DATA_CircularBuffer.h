/*
 * DATA_CircularBuffer.h
 *
 *  Created on: 2015”N7ŒŽ19“ú
 *      Author: Tetsu Gi
 */

#ifndef DATA_CIRCULARBUFFER_H_
#define DATA_CIRCULARBUFFER_H_
#include <stdint.h>

#define BUFFER_DATA_TYPE	uint8_t
#define BUFFER_DATA_SIZE	(1)

struct s_circular_buffer{
	uint32_t BufferSize;
	BUFFER_DATA_TYPE *buffer;
	BUFFER_DATA_TYPE *BufferEnd;
	BUFFER_DATA_TYPE *pRead;
	BUFFER_DATA_TYPE *pWrite;
	uint32_t Count;
};
typedef struct s_circular_buffer DATA_CircularBuffer_t;


#endif /* DATA_CIRCULARBUFFER_H_ */
