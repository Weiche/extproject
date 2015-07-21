#ifndef CONFIG_H
#define CONFIG_H

/* Include */
#include "ERROR.h"
#include "SYSTEM_HAL.h"

/*******************************
 * HARDWARE
 *******************************/
#define SYS_ICLK	(12000000.0F)
#define SYS_PCLK	(12000000.0F)
#define SYS_BCLK	(12000000.0F)

/*******************************
 * FUNCTIONS
 *******************************/
#define USE_ASSERT				(0)


/*******************************
 * LCD
 *******************************/
#define LCD_REFRESH_PERIOD		(100)/*ms*/


/*******************************
 * KEY_MATRIX
 *******************************/
#define KEYMATRIX_PORT			(PORT6)
#define KEYMATRIX_PORT_DIR		(PORT6.DDR.BYTE)
#define KEYMATRIX_PORT_DOUT		(PORT6.DR.BYTE)
#define KEYMATRIX_PORT_DIN		(PORT6.PORT.BYTE)

/*******************************
 * SERIAL
 *******************************/

/* SERIAL HAL */
#define SERIAL_HAL_BAUD			(38400)
#define SERIAL_HAL_STOPBIT		(1)
#define SERIAL_HAL_STARTBIT		(0)
#define SERIAL_METHOD_DMA		(1)
#define SERIAL_DRIVER_RXTIMEOUT (10000)
/* SERIAL PROTOCOL */
#define SERIAL_PROTOCOL_START_CODE		('^')
#define SERIAL_PROTOCOL_END_CODE		('$')
#define SERIAL_PROTOCOL_MAXPACKETLEN	(10)

/*******************************
 * VIEW
 *******************************/
#define VIEW_OFFSET_BAR			(24)
#define VIEW_OFFSET_L			(16)
#define VIEW_OFFSET_ADCVal		(9)
#define VIEW_OFFSET_TIMER		(0)
#define VIEW_OFFSET_ERROR		(0)
#define VIEW_OFFSET_ERRORMSG	(16)

/*******************************
 * TIMER
 *******************************/
#define TIMER_MAX_MINUTE		(60)

/*******************************
 * CHECK
 *******************************/
#if ( USE_ASSERT == 1 )
#define ASSERT(a)	if(!(a)){Disable_Interrupt();while(1);}
#else
#define ASSERT(a)
#endif

#endif
/* End of File */
