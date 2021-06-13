#ifndef EXTRACTSTRING_H
#define EXTRACTSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../UART/UART.h"

#define POSITIONING_SYSTEM   "GPGGA"

unsigned char extractString(char outStringGPGGA[], char outStringGPVTG[]);

#endif
