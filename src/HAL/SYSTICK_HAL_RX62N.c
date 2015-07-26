#include <stdint.h>
#include "CONFIG.h"
#include "SYSTICK_HAL.h"
#include "SYSTEM_ControlFlag.h"
#undef USE_BENCHMARK
static flag_t *__pFlag10ms = 0;
void SYSTICK_HALInit(flag_t *p){
	ASSERT(p != 0);
	__pFlag10ms = p;

	MSTP(CMT0) = 0;
	CMT.CMSTR0.BIT.STR0 = 0;
	CMT0.CMCNT = 0;
	CMT0.CMCR.WORD = (1<<7) | (1<<6) ;
	CMT0.CMCOR = (SYS_PCLK / 8.0F / 1000.0F * 10.0F) - 1;
	CMT.CMSTR0.BIT.STR0 = 1;

	IR(CMT0,CMI0) = 0;
	IPR(CMT0,CMI0) = 10;
	IEN(CMT0,CMI0) = 1;

}

#pragma interrupt SYSTICK_Handler(vect= VECT(CMT0, CMI0))
void SYSTICK_Handler(void){
	ASSERT(__pFlag10ms);
	*__pFlag10ms = 1;
}
