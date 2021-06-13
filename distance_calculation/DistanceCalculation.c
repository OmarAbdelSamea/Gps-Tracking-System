#include "DistanceCalculation.h"

long double to_rad(long double degree){
    long double pi = 3.141592653;
    long double one_degree = (pi)/180;
    return (one_degree * degree);
}

distance distanceCalculation(point point1, point point2){
    long double dlong;
    long double dlat;
    long double ans;
    long double earth_radius;
	float f;
    int temp;

	distance output;
		
    point1.latitude = to_rad(point1.latitude);
    point2.latitude = to_rad(point2.latitude);
    point1.longitude = to_rad(point1.longitude);
    point2.longitude = to_rad(point2.longitude);
	
    dlong = point2.longitude - point1.longitude;
    dlat = point2.latitude - point2.latitude;

    ans = pow(sin(dlat / 2), 2) + cos(point1.latitude ) * cos(point2.latitude) * pow(sin(dlong / 2), 2);
    ans = 2 * asin(sqrt(ans));

    earth_radius = 6371;
    
    ans = ans * earth_radius;
    f =100000*( ans - floor(ans));
    temp =(int)(ans*1000);
    output.meters= (unsigned short)temp;
    output.centimeters= (unsigned short)f;
    return output;
}

double distanceBetween(point point1, point point2)
{
	distance output;
    double delta;
    double sdlong;
    double cdlong;
    double slat1;
    double clat1;
    double slat2;
    double clat2;
	double denom;
        
    delta = to_rad(point1.longitude-point2.longitude);
    sdlong = sin(delta);
    cdlong = cos(delta);
    point1.latitude = to_rad(point1.latitude);
    point2.latitude = to_rad(point2.latitude);
    slat1 = sin(point1.latitude);
    clat1 = cos(point1.latitude);
    slat2 = sin(point2.latitude);
    clat2 = cos(point2.latitude);
    delta = (clat1 * slat2) - (slat1 * clat2 * cdlong);
    delta = delta * delta;
    delta += ((clat2 * sdlong) * (clat2 * sdlong));
    delta = sqrt(delta);
    denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
    delta = atan2(delta, denom);
        delta = delta * 6372795;
        if (delta > 8)
        {
            delta = 0;
        }
    return delta;
}

