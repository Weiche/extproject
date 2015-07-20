/*
 * SYSTEM_HAL.h
 *
 *  Created on: 2015”N7ŒŽ17“ú
 *      Author: Administrator
 */

#ifndef SYSTEM_HAL_H_
#define SYSTEM_HAL_H_
/* Include					*/
#include "iodefine.h"
#include <machine.h>
/* Export Constant			*/
/* Export Macro				*/
#define		Enable_Interrupt()	setpsw_i()
#define		Disable_Interrupt()	clrpsw_i()

#define		LCD_TIMERFLAG	(IR(CMT2,CMI2))
/* Export Typedef			*/
/* Public Function Prototype */


#endif /* SYSTEM_HAL_H_ */

