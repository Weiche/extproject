#include <stdint.h>
#include "CONFIG.h"
#include "SYSTICK_HAL.h"
#include "TIMER_Driver.h"
void TIMER_DriverInit( TIMER_t *ptimer ){
	ASSERT(ptimer);
	TIMER_DriverReset(ptimer);
}

void TIMER_DriverStart( TIMER_t *ptimer ){
	ASSERT(ptimer);
	ptimer->state = TIMER_STATE_START;
}

void TIMER_DriverStop( TIMER_t *ptimer ){
	ASSERT(ptimer);
	ptimer->state = TIMER_STATE_STOP;
}

void TIMER_DriverToggle( TIMER_t *ptimer ){
	ASSERT(ptimer);
	if( ptimer->state != TIMER_STATE_STOP ){
		ptimer->state = TIMER_STATE_STOP;
	}else{
		ptimer->state = TIMER_STATE_START;
	}
}

void TIMER_DriverReset( TIMER_t *ptimer ){
	ASSERT(ptimer);
	ptimer->sec_100 = 0;
	ptimer->sec	   = 0;
	ptimer->min     = 0;
}

void TIMER_DriverCount( TIMER_t *ptimer ){
	ASSERT(ptimer);
	if( ptimer->state == TIMER_STATE_START ){
		ptimer->sec_100 ++;
		if( ptimer->sec_100 >= 100 ){
			ptimer->sec++;
			ptimer->sec_100 = 0;
			if( ptimer->sec >= 60 ){
				ptimer->sec = 0;
				if( ptimer->min < TIMER_MAX_MINUTE ){
					ptimer->min ++;
				}
			}
		}
	}
}
