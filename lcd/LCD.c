#include "LCD.h"

#define DC                      (*((volatile unsigned long *)0x40004100))
#define DC_COMMAND              0
#define DC_DATA                 0x40
#define RESET                   (*((volatile unsigned long *)0x40004200))
#define RESET_LOW               0
#define RESET_HIGH              0x80

enum typeOfWrite{
  COMMAND,                              
  DATA                                  
};

void static lcdwrite(enum typeOfWrite type, char message){
  if(type == COMMAND){
    while((SSI0_SR_R&SSI_SR_BSY)==SSI_SR_BSY){};
    DC = DC_COMMAND;
    SSI0_DR_R = message;
    while((SSI0_SR_R&SSI_SR_BSY)==SSI_SR_BSY){};
  } else{
    while((SSI0_SR_R&SSI_SR_TNF)==0){};
    DC = DC_DATA;
    SSI0_DR_R = message;
  }
}


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

  RESET = RESET_LOW;                    
  for(delay=0; delay<10; delay=delay+1);
  RESET = RESET_HIGH;                   

  lcdwrite(COMMAND, 0x21);              
                                        
  lcdwrite(COMMAND, CONTRAST);           
  lcdwrite(COMMAND, 0x04);              
  lcdwrite(COMMAND, 0x14);              

  lcdwrite(COMMAND, 0x20);              
  lcdwrite(COMMAND, 0x0C); 
}

void LCD_OutChar(unsigned char data){
  int i;
  lcdwrite(DATA, 0x00);                
  for(i=0; i<5; i=i+1){
    lcdwrite(DATA, ASCII[data - 0x20][i]);
  }
  lcdwrite(DATA, 0x00);             
}

void LCD_OutString(char *ptr){
  while(*ptr){
    LCD_OutChar((unsigned char)*ptr);
    ptr = ptr + 1;
  }
}