#include "Datetime.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int dejDenVTydnu(int r, int m, int d)
{
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	r -= m < 3;
	return (r + r / 4 - r / 100 + r / 400 + t[m - 1] + d) % 7;
}


//(2018-05-01 01:00:00)
tDateTime dejDateTime(char* datetime)
{
	tDateTime dateTime;
	char* dat = calloc(20, sizeof(char));
	strcpy(dat, datetime);
	char* date = strtok(dat, " ");
	char* year;
	char* month;
	char* day;
	
	char* time = strtok(NULL, " ");
	char* hour;
	char* minute;
	char* second;

	
	for (int timeType = 0; timeType < 2; ++timeType)
	for (int cell = 0; cell < 3; ++cell)
	{
		if (timeType == 0 && cell == 0)
		{
			year = strtok(date, "-");
		}else if (timeType == 0 && cell == 1)
		{
			month = strtok(NULL, "-");
		}
		else if (timeType == 0 && cell == 2)
		{
			day = strtok(NULL, "-");
		}
		else if (timeType == 1 && cell == 0)
		{
			hour = strtok(time, ":");
		}
		else if (timeType == 1 && cell == 1)
		{
			minute = strtok(NULL, ":");
		}
		else if (timeType == 1 && cell == 2)
		{
			second = strtok(NULL, ":");
		}

		
	}

	dateTime.year = atoi(year);
	dateTime.month = atoi(month);
	dateTime.day = atoi(day);
	dateTime.hour = atoi(hour);
	dateTime.min = atoi(minute);
	dateTime.sec = atoi(second);
	dateTime.dayInWeek = dejDenVTydnu(dateTime.year, dateTime.month, dateTime.day);
	//nekdy pada a nevim proc... re-run by mel fungovat...
	//TODO zkusit vyresit
	free(dat);
	return dateTime;
}
