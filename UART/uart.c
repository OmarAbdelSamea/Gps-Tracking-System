// U1Rx connected to PC4
// U1Tx connected to PC5

#include "UART.h"


/****************** UART0 *************/
void UART0_Init(void){
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; 
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;
  UART0_CTL_R &= ~UART_CTL_UARTEN;      
  UART0_IBRD_R = 520;  
  UART0_FBRD_R = 53;  
                                        
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= UART_CTL_UARTEN;       
  GPIO_PORTA_AFSEL_R |= 0x03;           
  GPIO_PORTA_DEN_R |= 0x03;                                            
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          
}




unsigned char UART0_InChar(void){
  while((UART0_FR_R&UART_FR_RXFE) != 0);
  return((unsigned char)(UART0_DR_R&0xFF));
}


unsigned char UART0_InCharNonBlocking(void){
  if((UART0_FR_R&UART_FR_RXFE) == 0){
    return((unsigned char)(UART0_DR_R&0xFF));
  } else{
    return 0;
  }
}


void UART0_OutChar(unsigned char data){
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

/****************** UART1 *************/
void UART1_Init(void){
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART1
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC; // activate port C
  UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART1_IBRD_R = 520;  									// 80,000,000/(16*115,200)) = 43.40278
  UART1_FBRD_R = 53;  									//6-bbit fraction, round(0.40278 * 64) = 26
  UART1_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN); // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART1_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTC_AFSEL_R |= 0x30;           // enable alt funct on PC5-4
  GPIO_PORTC_DEN_R |= 0x30;             // enable digital I/O on PC5-4                             
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000; // configure PC5-4 as UART1
  GPIO_PORTC_AMSEL_R &= ~0x30;          // disable analog functionality on PC5-4
}

unsigned char UART1_InChar(void){
  while((UART1_FR_R&UART_FR_RXFE) != 0);
  return((unsigned char)(UART1_DR_R&0xFF));
}


unsigned char UART1_InCharNonBlocking(void){
  if((UART1_FR_R&UART_FR_RXFE) == 0){
    return((unsigned char)(UART1_DR_R&0xFF));
  } else{
    return 0;
  }
}


void UART1_OutChar(unsigned char data){
  while((UART1_FR_R&UART_FR_TXFF) != 0);
  UART1_DR_R = data;
}

/**************** UART2 *****************/
void UART2_Init(void){
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART2; // activate UART2
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; // activate port D
  UART2_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART2_IBRD_R = 520;  // 80,000,000/(16*115,200)) = 43.40278
  UART2_FBRD_R = 53;  //6-bbit fraction, round(0.40278 * 64) = 26
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART2_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART2_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTD_AFSEL_R |= 0xC0;           // enable alt funct on PD 6-7 
  GPIO_PORTD_DEN_R |= 0xC0;             // enable digital I/O on PD 6-7
                                        // configure PD6-7 as UART2
  GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0x00FFFFFF)+0x11000000;
  GPIO_PORTD_AMSEL_R &= ~0xC0;          // disable analog functionality on PD6-7
}

unsigned char UART2_InChar(void){
  while((UART2_FR_R&UART_FR_RXFE) != 0);
  return((unsigned char)(UART2_DR_R&0xFF));
}

unsigned char UART2_InCharNonBlocking(void){
  if((UART2_FR_R&UART_FR_RXFE) == 0){
    return((unsigned char)(UART2_DR_R&0xFF));
  } else{
    return 'a';
  }
}

void UART2_OutChar(unsigned char data){
  while((UART2_FR_R&UART_FR_TXFF) != 0);
  UART2_DR_R = data;
}







