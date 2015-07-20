#include <stdint.h>
#include "BIT.h"
#if 1
uint8_t BIT_Count8Bit( uint8_t data ) {
	register uint8_t temp;
	temp = ( data & 0x55 ) + (( data & 0xAA ) >> 1 );
	temp = ( temp & 0x33 ) + (( temp & 0xCC ) >> 2 );
	temp = ( temp & 0x0F ) + (( temp & 0xF0 ) >> 4 );
	return temp;
}

uint8_t BIT_Count16Bit( uint16_t data ) {
	register uint16_t temp;
	temp = ( data & 0x5555 ) + (( data & 0xAAAA ) >>1 );
	temp = ( temp & 0x3333 ) + (( temp & 0xCCCC ) >>2 );
	temp = ( temp & 0x0F0F ) + (( temp & 0xF0F0 ) >>4 );
	temp = ( temp & 0x00FF ) + (( temp & 0xFF00 ) >>8 );
	return (uint8_t)temp;
}

uint8_t BIT_Count32Bit( uint32_t data ) {
	register uint32_t temp;
	temp = ( data & 0x55555555 ) + (( data & 0xAAAAAAAA ) >> 1 );
	temp = ( temp & 0x33333333 ) + (( temp & 0xCCCCCCCC ) >> 2 );
	temp = ( temp & 0x0F0F0F0F ) + (( temp & 0xF0F0F0F0 ) >> 4 );
	temp = ( temp & 0x00FF00FF ) + (( temp & 0xFF00FF00 ) >> 8 );
	temp = ( temp & 0x0000FFFF ) + (( temp & 0xFFFF0000 ) >> 16 );
	return (uint8_t)temp;
}
#else
static const int BITS_COUNT_TABLE[256] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3,
		2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3,
		2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5,
		4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4,
		3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5,
		4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3,
		2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5,
		4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5,
		4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5,
		4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5,
		4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7,
		6, 7, 7, 8, };

uint8_t BIT_Count8Bit(uint8_t data) {
	return BITS_COUNT_TABLE[data];
}

uint8_t BIT_Count16Bit(uint16_t data) {
	register uint8_t *p = (void*) &data;
	return (BITS_COUNT_TABLE[p[0]] + BITS_COUNT_TABLE[p[1]]);
}

uint8_t BIT_Count32Bit(uint32_t data) {
	register uint8_t *p = (void*) &data;
	return (BITS_COUNT_TABLE[p[0]] + BITS_COUNT_TABLE[p[1]]
			+ BITS_COUNT_TABLE[p[2]] + BITS_COUNT_TABLE[p[3]]);
}

#endif
