#ifndef SYSTICK_H
#define SYSTICK_H
#include "tm4c123gh6pm.h"
#include "portF.h"
#include <stdint.h>

void systick_init(void);

void systick_wait(uint32_t delay);

void systick_wait10(uint32_t delay);

#endif
