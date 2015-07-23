/***** ÉtÉ@ÉCÉãÇÃéÊÇËçûÇ› *****/
#include <stdint.h>
#include "CONFIG.h"
#include "SYSTICK_HAL.h"
#include "SYSTEM_ControlFlag.h"

#include "ADC_Driver.h"
#include "KEYMATRIX_Driver.h"
#include "TIMER_Driver.h"
#include "VIEW_Renderer.h"
#include "SERIAL_Protocol.h"

#include "CONTROLLER.h"
#if 1
#define TOGGLE_P15()	PORT1.DR.BIT.B5 ^= 1
#else
#define TOGGLE_P15()
#endif

#define YIELD(flag)	TOGGLE_P15();(flag) = __LINE__;break;case __LINE__:
#define START(flag)	switch(flag){case 1:
#define END(flag)	(flag) = 0;}

/* Private Variables */
/* Important Objects */
static flag_t FLAG_10ms;
static TIMER_t TIMER_OneHour;
static SERIAL_Protocol_t Serial;

/* Normal */
static data_t packet[2];
static data_t packet_tx[2];
static VIEW_ascii_t self_view = { "00", "00", "00", "000" };
static VIEW_ascii_t rx_view = { "00", "00", "00", "000" };
/*  Function Prototype  */
static void VTC_Voltage2Char(uint32_t voltage, VIEW_ascii_t *p_view);
static void TTC_Timer2Char(const TIMER_t *time, VIEW_ascii_t *p_View);

#define EVENT_RX_ERROR	(0xFFF)
static view_t VIEW_State = VIEW_SELF;
static int32_t VIEW_DispErrorTimer;
static void __Recv2View(const data_t *pdata, VIEW_ascii_t *pview) {
	if (pdata->type == 0 && pdata->length == 6) {
		pview->min[0] = pdata->data_ascii[0];
		pview->min[1] = pdata->data_ascii[1];
		pview->sec[0] = pdata->data_ascii[2];
		pview->sec[1] = pdata->data_ascii[3];
		pview->sec100[0] = pdata->data_ascii[4];
		pview->sec100[1] = pdata->data_ascii[5];
	} else if (pdata->type == 1 && pdata->length == 3) {
		pview->adc[0] = pdata->data_ascii[0];
		pview->adc[1] = pdata->data_ascii[1];
		pview->adc[2] = pdata->data_ascii[2];
	}
}
static void __SelfData(void) {
	packet_tx[0].length = 6;
	packet_tx[0].type = 0;
	packet_tx[0].data_ascii[0] = self_view.min[0];
	packet_tx[0].data_ascii[1] = self_view.min[1];
	packet_tx[0].data_ascii[2] = self_view.sec[0];
	packet_tx[0].data_ascii[3] = self_view.sec[1];
	packet_tx[0].data_ascii[4] = self_view.sec100[0];
	packet_tx[0].data_ascii[5] = self_view.sec100[1];

	packet_tx[1].length = 3;
	packet_tx[1].type = 1;
	packet_tx[1].data_ascii[0] = self_view.adc[0];
	packet_tx[1].data_ascii[1] = self_view.adc[1];
	packet_tx[1].data_ascii[2] = self_view.adc[2];
}
static VIEW_ascii_t *__VIEW_StateMachine(int32_t event) {
	VIEW_ascii_t *pv;
	switch (VIEW_State) {
	case VIEW_SELF:
		if (Serial.CONN_State == SERIAL_STATE_CONNONLINE) {
			VIEW_State = VIEW_RECV;
		} else if (event == EVENT_RX_ERROR) {
			VIEW_State = VIEW_ERROR;
			VIEW_DispErrorTimer = 100;
		}
		pv = &self_view;
		break;
	case VIEW_RECV:
		if (Serial.CONN_State == SERIAL_STATE_CONNOFFLINE) {
			VIEW_State = VIEW_SELF;
		} else if (event == EVENT_RX_ERROR) {
			VIEW_State = VIEW_ERROR;
			VIEW_DispErrorTimer = 100;
		}
		pv = &rx_view;
		break;
	case VIEW_ERROR:
		if ((VIEW_DispErrorTimer--) == 0) {
			if (Serial.CONN_State == SERIAL_STATE_CONNOFFLINE) {
				VIEW_State = VIEW_SELF;
			} else {
				VIEW_State = VIEW_RECV;
			}
			pv = &rx_view;
		}
		break;
	}
	return pv;
}
void CONTROLLER_Init(void) {
	TIMER_DriverInit(&TIMER_OneHour);
	SERIAL_ProtocolInit(&Serial);
	VIEW_Init();
	ADC_DriverInit();
	KEYMATRIX_DriverInit();
	SYSTICK_HALInit(&FLAG_10ms);
}

void CONTROLLER_MainLoop(void) {
	static int32_t ret;
	static int32_t adv;

	/* Executed Every Loop */
	SERIAL_ProtocolBackground(&Serial);

	if ( SYSTEM_GetFlagLCD() == 1) {
		SYSTEM_ClrFlagLCD();
		VIEW_Refresh();
	}
	PORT1.DR.BIT.B5 = 0;
	START(FLAG_10ms)
	TIMER_DriverCount(&TIMER_OneHour);
	ADC_DriverSoftStart();

	YIELD(FLAG_10ms)
	KEYMATRIX_DriverScan();
	TTC_Timer2Char(&TIMER_OneHour, &self_view);

	YIELD(FLAG_10ms)
	adv = ADC_DriverGetVoltage();
	VTC_Voltage2Char(adv, &self_view);

	YIELD(FLAG_10ms)
	__SelfData();
	SERIAL_ProtocolSend(&Serial, &packet_tx[0], 2);

	YIELD(FLAG_10ms)
	ret = SERIAL_ProtocolRecv(&Serial, packet, 2);

	YIELD(FLAG_10ms)
	if (ret < 0) {
		__VIEW_StateMachine(EVENT_RX_ERROR);
	} else {
		while (ret--) {
			__Recv2View(&(packet[ret]), &rx_view);
		}
	}
	YIELD(FLAG_10ms)
	VIEW_Render(VIEW_State, __VIEW_StateMachine(0));
	END(FLAG_10ms)

return;
}

static void VTC_Voltage2Char(uint32_t voltage, VIEW_ascii_t *p_View) {
p_View->adc[0] = (uint8_t) (voltage / 1000 + 0x30);
p_View->adc[1] = (uint8_t) (voltage / 100 % 10 + 0x30);
p_View->adc[2] = (uint8_t) (voltage / 10 % 10 + 0x30);

}

static void TTC_Timer2Char(const TIMER_t *time, VIEW_ascii_t *p_View) {

p_View->min[0] = (uint8_t) (time->min / 10 + 0x30);
p_View->min[1] = (uint8_t) (time->min % 10 + 0x30);

p_View->sec[0] = (uint8_t) (time->sec / 10 + 0x30);
p_View->sec[1] = (uint8_t) (time->sec % 10 + 0x30);

p_View->sec100[0] = (uint8_t) (time->sec_100 / 10 + 0x30);
p_View->sec100[1] = (uint8_t) (time->sec_100 % 10 + 0x30);

}

void KEYMATRIX_Callback(uint32_t code) {

if (code == 0x1000) {
	TIMER_DriverToggle(&TIMER_OneHour);
}
if (code == 0x0100 && TIMER_OneHour.state == 0) {
	TIMER_DriverReset(&TIMER_OneHour);
}
}

/** End of file */
