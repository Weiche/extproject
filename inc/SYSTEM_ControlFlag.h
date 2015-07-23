/*
 * SYSTEM_ControlFlag.h
 *
 *  Created on: 2015”N7ŒŽ17“ú
 *      Author: Che Wei
 */

#ifndef SYSTEM_CONTROLFLAG_H_
#define SYSTEM_CONTROLFLAG_H_
/* Include					*/
#include <stdint.h>
#include <SYSTEM_HAL.h>
/* Export Constant			*/
/* Export Macro				*/

#define		SYSTEM_GetFlagLCD()		(LCD_TIMERFLAG)
#define		SYSTEM_SetFlagLCD()		LCD_TIMERFLAG = 1
#define		SYSTEM_ClrFlagLCD()		LCD_TIMERFLAG = 0

/* Export Typedef			*/
typedef volatile uint8_t flag_t;
/* Public Function Prototype */
/* Public Variables */

#endif /* SYSTEM_CONTROLFLAG_H_ */

