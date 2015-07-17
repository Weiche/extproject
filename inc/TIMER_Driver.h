/*
 * TIMER_Driver.h
 *
 *  Created on: 2015”N7ŒŽ16“ú
 *      Author: First Version Tetsu Gi 2015/07/16
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

/* Include					*/
/* Export Constant			*/
/* Export Macro				*/
#define TIMER_STATE_START	(1)
#define TIMER_STATE_STOP	(0)

/* Export Typedef			*/
struct s_timer {
	uint8_t sec_100;
	uint8_t sec;
	uint8_t min;
	uint8_t	state;
};
typedef struct s_timer TIMER_t;

/* Public Function Prototype */
void TIMER_DriverInit( TIMER_t *ptimer );
void TIMER_DriverStart( TIMER_t *ptimer );
void TIMER_DriverStop( TIMER_t *ptimer );
void TIMER_DriverToggle( TIMER_t *ptimer );
void TIMER_DriverReset( TIMER_t *ptimer );
void TIMER_DriverCount( TIMER_t *ptimer );

#endif /* TIMER_DRIVER_H_ */
