/*
 * TEST.c
 *
 *  Created on: 2015”N7ŒŽ18“ú
 *      Author: CHE WEI
 */

#include "SYSTEM_HAL.h"
#include "SYSTEM_ControlFlag.h"
/*
 *  12MHz Clock/8 => 0.666us / Tick
 *
 *
 *
 */
void TEST_RefTimerInit(void){
    MSTP(CMT3) = 0;
    CMT.CMSTR1.BIT.STR3 = 0;
    CMT3.CMCNT = 0;
    CMT3.CMCOR = 0xFFFF;
    CMT3.CMCR.WORD = 0x00C0;
    IR( CMT3,CMI3) = 0;
    IPR( CMT3,CMI3) = 1;
    IEN( CMT3,CMI3 ) = 0;
    CMT.CMSTR1.BIT.STR3 = 1;
}

uint16_t TEST_GetRefTimerCNT(void){
	return CMT3.CMCNT;
}
