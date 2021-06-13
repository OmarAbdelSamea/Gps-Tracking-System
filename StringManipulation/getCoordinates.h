#ifndef getCoordinates_H
#define getCoordinates_H
#include<stdlib.h>
#include<stdio.h>
#include"string.h"
#include "../LCD/LCD.h"
#include "../tm4c123gh6pm.h"
#include "../Types.h"

#define NUM_OF_UNUSED_READINGS 5

void substr(const char* src, int m, int n, char* dest);
point frameProcessingGPGGA(char* frame);
double frameProcessingGPVTG(char* frame);
extern unsigned char falseReadDetector;

#endif

