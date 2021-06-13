#ifndef UART_H
#define UART_H

// U1Rx connected to PC4
// U1Tx connected to PC5

#include "stdint.h"
#include "../tm4c123gh6pm.h"

/******** UART0 **********/
void UART0_Init(void);

unsigned char UART0_InChar(void);

unsigned char UART0_InCharNonBlocking(void);

void UART0_OutChar(unsigned char data);

/******** UART1 **********/
void UART1_Init(void);

unsigned char UART1_InChar(void);

unsigned char UART1_InCharNonBlocking(void);

void UART1_OutChar(unsigned char data);

/******** UART2 **********/
void UART2_Init(void);

unsigned char UART2_InChar(void);

unsigned char UART2_InCharNonBlocking(void);

void UART2_OutChar(unsigned char data);
#endif
