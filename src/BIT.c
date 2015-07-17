#include <stdint.h>
#include "BIT.h"

uint8_t BIT_Count8Bit( uint8_t data ){
	register uint8_t temp;
	temp = ( data & 0x55 ) + (( data & 0xAA ) >> 1 );
	temp = ( temp & 0x33 ) + (( temp & 0xCC ) >> 2 );
	temp = ( temp & 0x0F ) + (( temp & 0xF0 ) >> 4 );
	return temp;
}

uint8_t BIT_Count16Bit( uint16_t data ){
	register uint16_t temp;
	temp = ( data & 0x5555 ) + (( data & 0xAAAA ) >>1 );
	temp = ( temp & 0x3333 ) + (( temp & 0xCCCC ) >>2 );
	temp = ( temp & 0x0F0F ) + (( temp & 0xF0F0 ) >>4 );
	temp = ( temp & 0x00FF ) + (( temp & 0xFF00 ) >>8 );
	return (uint8_t)temp;
}

uint8_t BIT_Count32Bit( uint32_t data ){
	register uint32_t temp;
	temp = ( data & 0x55555555 ) + (( data & 0xAAAAAAAA ) >> 1  );
	temp = ( temp & 0x33333333 ) + (( temp & 0xCCCCCCCC ) >> 2  );
	temp = ( temp & 0x0F0F0F0F ) + (( temp & 0xF0F0F0F0 ) >> 4  );
	temp = ( temp & 0x00FF00FF ) + (( temp & 0xFF00FF00 ) >> 8  );
	temp = ( temp & 0x0000FFFF ) + (( temp & 0xFFFF0000 ) >> 16 );
	return (uint8_t)temp;
}

