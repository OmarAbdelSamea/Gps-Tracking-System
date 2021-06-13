/*  $GPGGA,091030.00,3005.07165,N,03119.65437,E,1,05,2.24,81.9,M,15.4,M,,*6C */
#include"getCoordinates.h"

void substr(const char* src, int m, int n, char* dest)
{
	unsigned long j = 0;
	for (j = m; j < n && (*(src + j) != '\0'); j++)
	{
		dest[j - m]= src[j];
	}
	dest[n] = '\0';
}

point frameProcessingGPGGA(char* frame) {
	unsigned long i = 0;
	char* ptr;
	long double temp_point;
	point sel_point;
	int count_commas = 0;
	char index_second_comma, index_third_comma, index_fourth_comma, index_fifth_comma,index_eighth_comma, index_ninth_comma, index_tenth_comma;
	char dest[15];
	i = 0;
	while (1) {
		if (frame[i] == ',') {
			count_commas++;
			if (count_commas == 2) {
				index_second_comma = i;
			}
			else if (count_commas == 3) {
				index_third_comma = i;
			}
			else if (count_commas == 4) {
				index_fourth_comma = i;
			}
			else if (count_commas == 5) {
				index_fifth_comma = i;
			}
			else if (count_commas == 6) {
				if (frame[i + 1] == '0') {
					sel_point.valid = 0;
					return sel_point;
				}
			}
			else if (count_commas == 8) {
				index_eighth_comma = i;
			}
			else if (count_commas == 9) {
				index_ninth_comma = i;
			}
			else if (count_commas == 10) {
				index_tenth_comma = i;
				break;
			}
		}
		i++;
	}

	substr(frame, index_second_comma + 1, index_third_comma, dest);
	sel_point.latitude = strtold(dest, &ptr);
	
	substr(frame, index_fourth_comma + 1, index_fifth_comma, dest);
	sel_point.longitude = strtold(dest, &ptr);
	
	substr(frame, index_eighth_comma + 1, index_ninth_comma, dest);
	sel_point.diameter = strtold(dest, &ptr);
	
	substr(frame, index_ninth_comma + 1, index_tenth_comma, dest);
	sel_point.altitude = strtold(dest, &ptr);
	
	if (frame[index_third_comma + 1] == 'S') {
		sel_point.latitude = -sel_point.latitude;
	}
	if (frame[index_fifth_comma + 1] == 'W') {
		sel_point.longitude = -sel_point.longitude;
	}
	sel_point.valid = 1;
	if (sel_point.valid == 1 && falseReadDetector < NUM_OF_UNUSED_READINGS)
	{
		falseReadDetector++;
		sel_point.valid = 0;
	}
		
	/*
	LCD_OutUDec(sel_point.valid);
	*/
	
	temp_point = (char)(sel_point.latitude / 100);
	temp_point = temp_point + ((sel_point.latitude - temp_point * 100) / 60);
	sel_point.latitude = temp_point;
	
	temp_point = (char)(sel_point.longitude / 100);
	temp_point = temp_point + ((sel_point.longitude - temp_point * 100) / 60);
	sel_point.longitude = temp_point;
	return sel_point;
}

double frameProcessingGPVTG(char* frame) {
	
	unsigned long i = 0;
	char* ptr;
	int count_commas = 0;
	double velocity;
	char index_seventh_comma, index_eighth_comma;
	char dest[15];
	i = 0;
	while (1) {
		if (frame[i] == ',') {
			count_commas++;
			if (count_commas == 7) {
				index_seventh_comma = i;
			}
			else if (count_commas == 8) {
				index_eighth_comma = i;
				break;
			}
		}
		i++;
	}

	substr(frame, index_seventh_comma + 1, index_eighth_comma, dest);

	velocity = strtod(dest, &ptr);

	return velocity;
}
