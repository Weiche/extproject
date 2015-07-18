#ifndef WDT_H
#define WDT_H
	#include <stdint.h>

	#define WDT_CSK_PCLK_4		(0)
	#define WDT_CSK_PCLK_64		(1)
	#define WDT_CSK_PCLK_128	(2)
	#define WDT_CSK_PCLK_512	(3)
	#define WDT_CSK_PCLK_2048	(4)
	#define WDT_CSK_PCLK_8192	(5)
	#define WDT_CSK_PCLK_32768	(6)
	#define WDT_CSK_PCLK_131072	(7)

	void WDT_Init(int32_t div, uint8_t ticks, uint8_t reset);
	void WDT_Feed(void);

#endif

