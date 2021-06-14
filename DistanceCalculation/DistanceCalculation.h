#ifndef DISTANCECALCULATION_H
#define DISTANCECALCULATION_H
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "../Types.h"

long double to_rad(long double degree);
distance distanceCalculation(point point1, point point2);
double distanceBetween(point point1, point point2);
#endif
