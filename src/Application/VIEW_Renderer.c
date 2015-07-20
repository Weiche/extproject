#include <stdint.h>
#include "CONFIG.h"
#include "LCD_Driver.h"
#include "VIEW_Renderer.h"



/* private functions */
static void VIEW_RenderTime(const VIEW_ascii_t *p) {
	ASSERT(p != 0);
	/* render timer */
	LCD_DriverBufferWrite( VIEW_OFFSET_TIMER + 0, p->min[0]);
	LCD_DriverBufferWrite( VIEW_OFFSET_TIMER + 1, p->min[1]);
	LCD_DriverBufferWrite( VIEW_OFFSET_TIMER + 2, ':');
	LCD_DriverBufferWrite( VIEW_OFFSET_TIMER + 3, p->sec[0]);
	LCD_DriverBufferWrite( VIEW_OFFSET_TIMER + 4, p->sec[1]);
	LCD_DriverBufferWrite( VIEW_OFFSET_TIMER + 5, ':');
	LCD_DriverBufferWrite( VIEW_OFFSET_TIMER + 6, p->sec100[0]);
	LCD_DriverBufferWrite( VIEW_OFFSET_TIMER + 7, p->sec100[1]);
}
#if (USE_ADCBAR_EXT==0)
static void VIEW_RenderADCValue(const VIEW_ascii_t *p) {
	ASSERT(p != 0);
	/* render adc value */
	LCD_DriverBufferWrite( VIEW_OFFSET_ADCVal + 0, p->adc[0]);
	LCD_DriverBufferWrite( VIEW_OFFSET_ADCVal + 1, '.');
	LCD_DriverBufferWrite( VIEW_OFFSET_ADCVal + 2, p->adc[1]);
	LCD_DriverBufferWrite( VIEW_OFFSET_ADCVal + 3, p->adc[2]);
	LCD_DriverBufferWrite( VIEW_OFFSET_ADCVal + 4, 'V');
}
#else
static void VIEW_RenderADCBar(const VIEW_ascii_t *p) {
	static const uint8_t table[] = { 0x20, 0x01, 0x02, 0x03, 0x04, 0xFF };
	int32_t i, adc, adc_disp;

	ASSERT(p != 0);

	/* render adc bar */
	adc = 0;
	adc += (p->adc[0] - 0x30) * 100;
	adc += (p->adc[1] - 0x30) * 10;
	adc += (p->adc[2] - 0x30) * 1;

	adc_disp = adc / (330 / 30);
	i = 0;
	while (adc_disp >= 5) {
		LCD_DriverBufferWrite( VIEW_OFFSET_BAR + i, table[5]);
		adc_disp -= 5;
		i++;
	}
	LCD_DriverBufferWrite( VIEW_OFFSET_BAR + i, table[adc_disp]);
	i++;

	while (i < 6) {
		LCD_DriverBufferWrite( VIEW_OFFSET_BAR + i, table[0]);
		i++;
	}
}
#endif

static void VIEW_RenderL(void) {
	LCD_DriverBufferWrite( VIEW_OFFSET_ADCVal + 0, 'L');
}

static void VIEW_RenderADCBar(const VIEW_ascii_t *p){

}
/* public functions */
void VIEW_Render(view_t view_code, const void *p) {
	const VIEW_ascii_t *pVIEW = p;

	LCD_DriverBufferClear();
	switch (view_code) {
	case VIEW_SELF:
		VIEW_RenderL();
		VIEW_RenderTime(p);
		VIEW_RenderADCValue(p);
		VIEW_RenderADCBar(p);
		break;
	case VIEW_RECV:
		ASSERT(p);
		VIEW_RenderTime(p);
		VIEW_RenderADCValue(p);
		VIEW_RenderADCBar(p);
		break;
	case VIEW_MESSAGE:
		/* p string output */
		//VIEW_RenderMessage( p );
		if (p == 0) {
			/* strcpy() */
		}
		break;
	case VIEW_ERROR:
		//VIEW_RenderError( p );
		break;

	}
	(void)pVIEW;
}

void VIEW_Init(void) {
	LCD_DriverInit();
}

void VIEW_Clear(void) {
	LCD_DriverBufferClear();
}

/***************
 *	End of File
 ****************/
