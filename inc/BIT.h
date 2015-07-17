#ifndef _BIT_H
#define _BIT_H

#include <stdint.h>
/******************************
 * function: uint8_t BIT_CountXBit( const uintX_t data )
 * @brief	count bits for a X bit variable
 * @param	uintX_t, data to count bits
 * @return	uint8_t, number of 1
 * @example BIT_Count8Bit( 0xFF ) => return 8,BIT_Count16Bit( 0xFF01 ) => return 9,
 ******************************/
uint8_t BIT_Count8Bit( uint8_t data );

uint8_t BIT_Count16Bit( uint16_t data );

uint8_t BIT_Count32Bit( uint32_t data );

#endif
/*  End of File */
