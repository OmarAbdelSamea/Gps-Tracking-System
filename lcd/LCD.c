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

void LCD_OutUDec(unsigned short n){
  if(n < 10){
    LCD_OutString("    ");
    LCD_OutChar(n+'0'); 
  } else if(n<100){
    LCD_OutString("   ");
    LCD_OutChar(n/10+'0'); 
    LCD_OutChar(n%10+'0'); 
  } else if(n<1000){
    LCD_OutString("  ");
    LCD_OutChar(n/100+'0'); 
    n = n%100;
    LCD_OutChar(n/10+'0'); 
    LCD_OutChar(n%10+'0'); 
  }
  else if(n<10000){
    LCD_OutChar(' ');
    LCD_OutChar(n/1000+'0'); 
    n = n%1000;
    LCD_OutChar(n/100+'0'); 
    n = n%100;
    LCD_OutChar(n/10+'0'); 
    LCD_OutChar(n%10+'0'); 
  }
  else {
    LCD_OutChar(n/10000+'0'); 
    n = n%10000;
    LCD_OutChar(n/1000+'0'); 
    n = n%1000;
    LCD_OutChar(n/100+'0'); 
    n = n%100;
    LCD_OutChar(n/10+'0');
    LCD_OutChar(n%10+'0');
  }
}


void LCD_SetCursor(unsigned char newX, unsigned char newY){
  if((newX > 11) || (newY > 5)){        
    return;                          
  }
  lcdwrite(COMMAND, 0x80|(newX*7));     
  lcdwrite(COMMAND, 0x40|newY);         
}

void LCD_Clear(void){
  int i;
  for(i=0; i<(MAX_X*MAX_Y/8); i=i+1){
    lcdwrite(DATA, 0x00);
  }
  LCD_SetCursor(0, 0);
}

void LCD_DrawFullImage(const char *ptr){
  int i;
  LCD_SetCursor(0, 0);
  for(i=0; i<(MAX_X*MAX_Y/8); i=i+1){
    lcdwrite(DATA, ptr[i]);
  }
}
char Screen[SCREENW*SCREENH/8]; 

void LCD_PrintBMP(unsigned char xpos, unsigned char ypos, const unsigned char *ptr, unsigned char threshold){
  long width = ptr[18], height = ptr[22], i, j;
  unsigned short screenx, screeny;
  unsigned char mask;
  if((height <= 0) ||              
     ((width%2) != 0) ||          
     ((xpos + width) > SCREENW) || 
     (ypos < (height - 1)) ||      
     (ypos > SCREENH))           { 
    return;
  }
  if(threshold > 14){
    threshold = 14;             
  }

  screeny = ypos/8;
  screenx = xpos + SCREENW*screeny;
  mask = ypos%8;                
  mask = 0x01<<mask;            
  j = ptr[10];                  
  for(i=1; i<=(width*height/2); i=i+1){
    if(((ptr[j]>>4)&0xF) > threshold){
      Screen[screenx] |= mask;
    } else{
      Screen[screenx] &= ~mask;
    }
    screenx = screenx + 1;
    if((ptr[j]&0xF) > threshold){
      Screen[screenx] |= mask;
    } else{
      Screen[screenx] &= ~mask;
    }
    screenx = screenx + 1;
    j = j + 1;
    if((i%(width/2)) == 0){    
      if(mask > 0x01){
        mask = mask>>1;
      } else{
        mask = 0x80;
        screeny = screeny - 1;
      }
      screenx = xpos + SCREENW*screeny;
      switch((width/2)%4){     
        case 0: j = j + 0; break;
        case 1: j = j + 3; break;
        case 2: j = j + 2; break;
        case 3: j = j + 1; break;
      }
    }
  }
}

void LCD_ClearBuffer(void){int i;
  for(i=0; i<SCREENW*SCREENH/8; i=i+1){
    Screen[i] = 0;              
  }
}

void LCD_SetPixel(unsigned char x, unsigned char y) {
  unsigned short PixelByte;            
  unsigned char PixelBit;
  if ((x<84) && (y<48)) {              
    PixelByte = ((y/8)*84) + x;
    PixelBit = y % 8;
    Screen[PixelByte] |= 1U<<PixelBit;
  }
}

void LCD_ClearPixel(unsigned char x, unsigned char y) {
  unsigned short PixelByte;            
  unsigned char PixelBit;              
  if ((x<84) && (y<48)) {              
    PixelByte = ((y/8)*84) + x;
    PixelBit = y % 8;
    Screen[PixelByte] &= ~(1U<<PixelBit);
  }
}

void LCD_DisplayBuffer(void){
  LCD_DrawFullImage(Screen);
}

