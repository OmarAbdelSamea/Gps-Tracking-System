#include "systick.h"

uint32_t data = 0x02;

void systick_init(void) {
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x00000007;
}

void SysTick_Handler(void) {
	PortF_Output(data);
	data = data << 1;
	if (data == 0x10) { data = 0x02; }
}
