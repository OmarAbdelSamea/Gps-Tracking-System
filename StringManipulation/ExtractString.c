#include "ExtractString.h"

unsigned char extractString(char outStringGPGGA[], char outStringGPVTG[])
{
    char sysGPGGA[] = "GPGGA", sysGPVTG[] = "GPVTG";
    char flgGPGGA = 0, flgGPVTG = 0;
		char flgTypeGPGGA = 0, flgTypeGPVTG = 0;

    uint32_t i = 0;
    unsigned char inChar;
		flgGPGGA = 0;
		flgGPVTG = 0;
	
    while (1)
    {
				if(flgTypeGPGGA == 1 && flgTypeGPVTG == 1){
					return 0;
				}
        i = 0;
        inChar = UART1_InChar();
        GPIO_PORTF_DATA_R = 0x04;
        if (inChar == '$')
        {
            GPIO_PORTF_DATA_R = 0x0A; // update LEDs
            flgGPGGA = 0; flgGPVTG = 0;
						if(flgTypeGPGGA == 0)
							{
							outStringGPGGA[i] = inChar;
						}
					  if(flgTypeGPVTG == 0 )
							{
							outStringGPVTG[i] = inChar;
						}
            for (i = 1; i < 6; i++)
            {
                inChar = UART1_InChar();
								if(flgTypeGPGGA == 0)
									{
									outStringGPGGA[i] = inChar;
								}
								 if(flgTypeGPVTG == 0 )
									 {
							outStringGPVTG[i] = inChar;
									}
                if (outStringGPGGA[i] != sysGPGGA[i - 1] )
                {
                    flgGPGGA = 1;
                }
								if (outStringGPVTG[i] != sysGPVTG[i - 1] )
								{
										flgGPVTG = 1;
								}
								
            }
            if (flgGPGGA == 0 && flgTypeGPGGA == 0)
            {
                for (i = 6; i < 100; i++)
                {
                    inChar = UART1_InChar();
                    if (inChar == '$')
                    {
                        //GPIO_PORTF_DATA_R = 0x02; // update LEDs
                        outStringGPGGA[i] = '\0';
												flgTypeGPGGA = 1;
                        break;
                    }
                    else
                    {
                        outStringGPGGA[i] = inChar;
                    }
                }
            }
						else if (flgGPVTG == 0 && flgTypeGPVTG == 0)
            {
                for (i = 6; i < 100; i++)
                {
									
                    inChar = UART1_InChar();
                    if (inChar == '$')
                    {
                        //GPIO_PORTF_DATA_R = 0x02; // update LEDs
                        outStringGPVTG[i] = '\0';
												flgTypeGPVTG = 1;
                        break;
                    }
                    else
                    {
                        outStringGPVTG[i] = inChar;
                    }
                }
            }
        }
    }
}
