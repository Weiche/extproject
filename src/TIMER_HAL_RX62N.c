#include <stdint.h>
#include "TIMER_HAL.h"
#include "SYSTEM_ControlFlag.h"

void TIMER_HALInit(flag_t *p){
	TIMER_DriverReset();
}
void TIMER_InterruptHandler(void){
	static flag_t dummy;
	static flag_t *__pFlag10ms = & dummy;
	*__pFlag10ms = 1;
}
