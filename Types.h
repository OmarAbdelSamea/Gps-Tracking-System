#ifndef TYPES_H
#define TYPES_H

typedef struct distance
{
    unsigned short meters;
    unsigned short centimeters;
}distance;

typedef struct{
	long double latitude;
	long double longitude;
	long double altitude;
	double diameter;
	char valid;
}point;

#endif


