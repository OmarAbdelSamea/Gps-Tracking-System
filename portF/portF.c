#include "portF.h"

void PortF_init(void){
    volatile unsigned long delay;
    SYSCTL_RCGCGPIO_R |= 0x00000020;
    delay = SYSCTL_RCGCGPIO_R;
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x0E;
    GPIO_PORTF_AMSEL_R &= ~0x0E;
    GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
    GPIO_PORTF_AFSEL_R &= ~0x0E;
    GPIO_PORTF_DIR_R = 0x0E;
    GPIO_PORTF_DEN_R = 0x1F;
    GPIO_PORTF_DATA_R &= ~0x0E;
    GPIO_PORTF_PUR_R = 0x11;


}

uint32_t PortF_Input(void) {
    return (GPIO_PORTF_DATA_R & 0x11);
}

void PortF_Output(uint32_t data) {
    GPIO_PORTF_DATA_R = data;
}