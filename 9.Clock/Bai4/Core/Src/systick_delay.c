
#include "main.h"

void SysTick_delay(uint32_t delay_ms){
	uint32_t delay_ticks = delay_ms * (SystemCoreClock / 1000);
	SysTick->LOAD = delay_ticks - 1;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
}
