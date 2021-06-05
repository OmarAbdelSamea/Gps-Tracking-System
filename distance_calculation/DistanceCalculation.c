#include "DistanceCalculation.h"

long double to_rad(long double degree){
    long double pi = 3.141592653;
    long double one_degree = (pi)/180;
    return (one_degree * degree); 
}

long double distance_calculation(long double lat1, long double lat2, long double long1, long double long2){
    long double dlong;
    long double dlat;
    long double ans;
    long double earth_radius;
		
    lat1 = to_rad(lat1/100);
    lat2 = to_rad(lat2/100);
    long1 = to_rad(long1/100);
    long2 = to_rad(long2/100);



    dlong = long2 - long1;
    dlat = lat2 - lat1;

    ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    earth_radius = 6371;

    ans = ans * earth_radius;

    return ans *1000;

}

