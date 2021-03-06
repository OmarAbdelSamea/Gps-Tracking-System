/* Gps_Tracking_System CSE312 */
#include "tm4c123gh6pm.h"
#include "UART/UART.h"
#include "PLL/PLL.h"
#include "LCD/LCD.h"
#include "Systick/systick.h"
#include "PortF/portF.h"
#include "StringManipulation/ExtractString.h"
#include "StringManipulation/getCoordinates.h"
#include "StringManipulation/esp.h"
#include "DistanceCalculation/DistanceCalculation.h"
#include <stdio.h>

unsigned char extractComplete;
char outStringGPGGA[100], outStringGPVTG[100], stringDistance[40], stringVelocity[40];
point newPointGPGGA, lastPointGPGGA;
double velocity;
unsigned char inChar, falseReadDetector = 0;
double newDistance = 0, newDelta;

void DisableInterrupts(void);
void EnableInterrupts(void);
	
int main()
{
	unsigned long i;
	DisableInterrupts();
	PLL_Init();
  LCD_Init();
	LCD_Clear();
	UART0_Init();
	UART1_Init();
	UART2_Init();
	PortF_init();
	lastPointGPGGA.valid = -1;
	EnableInterrupts();
	while(1)
	{
		extractComplete = extractString(outStringGPGGA, outStringGPVTG);
		/* GPGGA */
  	newPointGPGGA = frameProcessingGPGGA(outStringGPGGA);
		
		velocity = frameProcessingGPVTG(outStringGPVTG);
		
		if(lastPointGPGGA.valid == -1)
		{
			lastPointGPGGA = newPointGPGGA;
		}
		if(newPointGPGGA.valid != 0 && lastPointGPGGA.valid != 0 && (!(velocity < 1.4 && newPointGPGGA.diameter <= 4.1 ) || !(velocity < 4 && newPointGPGGA.diameter > 4.1)))
		{
			newDelta = distanceBetween(lastPointGPGGA, newPointGPGGA);
			newDistance += newDelta;
		}
		lastPointGPGGA = newPointGPGGA;			
		if(falseReadDetector < NUM_OF_UNUSED_READINGS)
		{
			LCD_Clear();
			LCD_SetCursor(0,2);
			LCD_OutString("Please Wait");
			LCD_SetCursor(0,3);
			for(i=0; i<falseReadDetector*2; i++){
				LCD_OutChar('.');
			}
			lastPointGPGGA.valid = -1;
		}
		else
		{
			esp(newDistance,newPointGPGGA);
			sprintf(stringDistance, "%lf", newDistance);
			LCD_Clear();
			LCD_OutString("Distance:");
			LCD_SetCursor(0,1);
			LCD_OutString(stringDistance);
			LCD_SetCursor(0,4);
			LCD_OutString("Velocity:");
			LCD_SetCursor(0,5);
			sprintf(stringVelocity, "%lf", velocity);
			LCD_OutString(stringVelocity);
		}
	}
}
