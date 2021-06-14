#include "esp.h"

void esp(double dist,point P){
	char d[20];
	char lng[20];
	char lat[20];
	char str[200];
	char inChar;
	unsigned long distr;
	unsigned long lngr;
	unsigned long latr;
	int i=0;
	
	distr = sprintf(d,"%0.14lf",dist);
	lngr = sprintf(lng,"%0.14lf",(double)P.longitude);
	latr = sprintf(lat,"%0.14lf",(double)P.latitude);
	
	if(P.valid){
		str[0]='S';
		for(i=0;i<latr;i++){
			str[i+1] = lat[i];
		}
		str[i+1] = 'L';
		
		for(i=0;i<lngr;i++){
			str[i+2+latr] = lng[i];
		}
		str[i+2+latr] = 'D';
		
		for(i=0;i<distr;i++){
			str[i+3+latr+lngr] = d[i];
		}
		str[i+3+latr+lngr] = 'N';
		str[i+4+latr+lngr] = '\0';		
		for(i=0;i<200;i++){
			UART1_OutChar(str[i]);
		
			//UART0_OutChar(str[i]);
		}
		str[200]=0;
		/*
		for(i=0;i<1000;i++){
			inChar = UART1_InCharNonBlocking();
			UART0_OutChar(inChar);
		}*/
	}
}
