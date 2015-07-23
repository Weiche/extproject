/*
 * DATA_CircularBuffer.c
 *
 *  Created on: 2015”N7ŒŽ19“ú
 *      Author: Tetsu Gi
 */
#include <stdint.h>
#include "CONFIG.h"
#include "DATA_CircularBuffer.h"

#define __EINT()
#define __DINT()

int32_t DATA_CircularBufferInit(DATA_CircularBuffer_t *p,
		BUFFER_DATA_TYPE *buffer, int32_t buffersize) {
	ASSERT( p ); ASSERT( buffer ); ASSERT( buffersize > 4);

	p->buffer = p->pWrite = p->pRead = buffer;
	p->BufferEnd = buffer + buffersize;
	p->Count = 0;
	p->BufferSize = buffersize;
	return ERROR_OK;
}

int32_t DATA_CircularBufferPut(DATA_CircularBuffer_t *p, BUFFER_DATA_TYPE c) {
	/* ASSERT p is not null */
	ASSERT( p );
	/* check if buffer is full */
	if( p->Count == p->BufferSize ){
		return ERROR_Full;
	}
	/* write buffer , critical session*/
	__DINT();
	(*(p->pWrite)++) = c;
	if (p->pWrite == (p->buffer + p->BufferSize)) {
		p->pWrite = p->buffer;
	}
	p->Count++;
	__EINT();
	return ERROR_OK;
}

int32_t DATA_CircularBufferGet(DATA_CircularBuffer_t *p, BUFFER_DATA_TYPE *pc) {
	ASSERT( p );
	ASSERT( pc );

	if( p->Count == 0 ){
		return ERROR_Empty;
	}

	/* write buffer , critical session*/
	__DINT();
	*pc = (*(p->pRead)++);
	if (p->pRead == (p->buffer + p->BufferSize)) {
		p->pRead = p->buffer;
	}
	p->Count--;
	__EINT();

	return ERROR_OK;
}

int32_t DATA_CircularBufferFlush(DATA_CircularBuffer_t *p) {
	ASSERT( p );

	__DINT();
	p->pRead = p->pWrite = p->buffer;
	p->Count = 0;
	__EINT();

	return ERROR_OK;
}
