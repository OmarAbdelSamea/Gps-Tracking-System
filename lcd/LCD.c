#include "LCD.h"

void LCD_Init(void){   
  volatile unsigned long delay;
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_SSI0;  
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; 
  delay = SYSCTL_RCGC2_R;               
  GPIO_PORTA_DIR_R |= 0xC0;             
  GPIO_PORTA_AFSEL_R |= 0x2C;           
  GPIO_PORTA_AFSEL_R &= ~0xC0;          
  GPIO_PORTA_DEN_R |= 0xEC;             
                                        
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFF0F00FF)+0x00202200;
                                        
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0x00FFFFFF)+0x00000000;
  GPIO_PORTA_AMSEL_R &= ~0xEC;          
  SSI0_CR1_R &= ~SSI_CR1_SSE;           
  SSI0_CR1_R &= ~SSI_CR1_MS;            
                     
  SSI0_CC_R = (SSI0_CC_R&~SSI_CC_CS_M)+SSI_CC_CS_SYSPLL;
                                        
                                        
                                        
  SSI0_CPSR_R = (SSI0_CPSR_R&~SSI_CPSR_CPSDVSR_M)+24; 
  SSI0_CR0_R &= ~(SSI_CR0_SCR_M |       
                  SSI_CR0_SPH |         
                  SSI_CR0_SPO);         
                                        
  SSI0_CR0_R = (SSI0_CR0_R&~SSI_CR0_FRF_M)+SSI_CR0_FRF_MOTO;
                                     
  SSI0_CR0_R = (SSI0_CR0_R&~SSI_CR0_DSS_M)+SSI_CR0_DSS_8;
  SSI0_CR1_R |= SSI_CR1_SSE;  
}

void LCD_OutChar(unsigned char data){
                 
}