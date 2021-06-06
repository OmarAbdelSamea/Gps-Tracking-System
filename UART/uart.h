#ifndef _UART_H_
#define _UART_H_

// U1Rx connected to PC4
// U1Tx connected to PC5

#include "stdint.h"               
#include <tm4c123gh6pm.h>


/******** UART1 **********/
void UART1_Init(void);

unsigned char UART1_InChar(void);

void UART1_OutChar(unsigned char data);


#endif
