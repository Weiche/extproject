#ifndef CONFIG_H
#define CONFIG_H

/* Include */
#include "iodefine.h"
#include "machine.h"
#include "ERROR.h"

/* System clock configuration */
#define SYS_ICLK	(12000000.0F)
#define SYS_PCLK	(12000000.0F)
#define SYS_BCLK	(12000000.0F)

/* Function Configuration */
#define USE_ASSERT				(1)
/* Controller configuration */
#define LCD_REFRESH_PERIOD		(100)/*ms*/


/* KEYMATRIX configuration */
#define KEYMATRIX_PORT			(PORT6)
#define KEYMATRIX_PORT_DIR		(PORT6.DDR.BYTE)
#define KEYMATRIX_PORT_DOUT		(PORT6.DR.BYTE)
#define KEYMATRIX_PORT_DIN		(PORT6.PORT.BYTE)

/* SERIAL configuration */

/* SERIAL HAL */
#define SERIAL_HAL_BAUD			(38400)
#define SERIAL_HAL_STOPBIT		(1)
#define SERIAL_HAL_STARTBIT		(0)
#define SERIAL_METHOD_DMA		(1)

/* SERIAL PROTOCOL */
#define SERIAL_PROTOCOL_START_CODE		('^')
#define SERIAL_PROTOCOL_END_CODE		('$')
#define SERIAL_PROTOCOL_MAXPACKETLEN	(10)

/* VIEW configuration */
#define VIEW_OFFSET_BAR			(24)
#define VIEW_OFFSET_L			(16)
#define VIEW_OFFSET_ADCVal		(9)
#define VIEW_OFFSET_TIMER		(0)

/* Assertion */
#if ( USE_ASSERT == 1 )
#define ASSERT(a)	if(!(a)){while(1);}
#else
#define ASSERT(a)
#endif

#endif
/* End of File */
