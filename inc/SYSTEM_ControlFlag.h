/*
 * SYSTEM_ControlFlag.h
 *
 *  Created on: 2015”N7ŒŽ17“ú
 *      Author: Administrator
 */

#ifndef SYSTEM_CONTROLFLAG_H_
#define SYSTEM_CONTROLFLAG_H_
/* Include					*/
#include <stdint.h>
#include <SYSTEM_HAL.h>
/* Export Constant			*/
/* Export Macro				*/

#define		SYSTEM_GetFlagLCD()		(LCD_TIMERFLAG)
#define		SYSTEM_SetFlagLCD()		LCD_TIMERFLAG = 1;
#define		SYSTEM_ClrFlagLCD()		LCD_TIMERFLAG = 0;

#define		SYSTEM_GetFlag10ms()		(__SYSTEM_Flag10ms)
#define		SYSTEM_SetFlag10ms()		__SYSTEM_Flag10ms = 1;
#define		SYSTEM_ClrFlag10ms()		__SYSTEM_Flag10ms = 0;

/* Export Typedef			*/
typedef volatile uint8_t flag_t;
/* Public Function Prototype */
/* Public Variables */
extern flag_t __SYSTEM_Flag10ms;

#endif /* SYSTEM_CONTROLFLAG_H_ */

