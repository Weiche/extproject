/***** ÉtÉ@ÉCÉãÇÃéÊÇËçûÇ› *****/

#include "CONFIG.h"
#include "SYSTEM_HAL.h"
#include "SYSTICK_HAL.h"
#include "SYSTEM_ControlFlag.h"

#include "ADC_Driver.h"
#include "KEYMATRIX_Driver.h"
#include "TIMER_Driver.h"
#include "VIEW_Renderer.h"
#include "SERIAL_Protocol.h"

#include "CONTROLLER.h"

/* Just a joke :) */
#define YIELD(flag)	(flag) = __LINE__;break;case __LINE__:
#define START(flag)	switch(flag){case 1:
#define END(flag)	(flag) = 0;}

/* Private Variables */
static SERIAL_Protocol_t serial;
static flag_t FLAG_10ms;
/* Test Private Variables */
static uint16_t __timer_temp,delay;
static volatile uint16_t mainloop_us;
static data_t	packet[2] = {
		{
				"112211",
				6,
				0
		},
		{
				"132",
				3,
				1
		}
};
static VIEW_ascii_t test_view= {
		"11","23","88","123"
};

void CONTROLLER_Init(void) {
	SYSTICK_HALInit(&FLAG_10ms);
	SERIAL_ProtocolInit(&serial);
	VIEW_Init();
	TEST_RefTimerInit();
}

void CONTROLLER_MainLoop(void) {
	static int32_t ret;
	//TODO CONTROLLER_MainLoop
	__timer_temp = TEST_GetRefTimerCNT();
	SERIAL_ProtocolBackground(&serial);
	if(	SYSTEM_GetFlagLCD() == 1 ){
		SYSTEM_ClrFlagLCD();
		LCD_DriverRefresh();
	}
	START(FLAG_10ms);
	for( delay = 0; delay < 12 * 20; delay++);/* 24us */
	nop();

	YIELD(FLAG_10ms);
	for( delay = 0; delay < 12 * 20; delay++);/* 24us */
	nop();

	YIELD(FLAG_10ms);
	for( delay = 0; delay < 12 * 40; delay++);/* 16us */
	nop();

	YIELD(FLAG_10ms);
	VIEW_Render(VIEW_SELF, &test_view); /* 8us */

	YIELD(FLAG_10ms);
	ret = SERIAL_ProtocolSend( &serial, packet ,2 );/* 28us */

	END(FLAG_10ms);

	mainloop_us = TEST_GetRefTimerCNT() - __timer_temp;
	nop();
	(void)ret;
}
/** End of file */
