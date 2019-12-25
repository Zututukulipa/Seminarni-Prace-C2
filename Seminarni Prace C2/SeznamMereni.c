#include "Mereni.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SeznamMereni.h"

tSeznamMereni* nactiMereni(int idSenzoru)
{
	FILE* fptr;
	tSeznamMereni* seznamMereni = malloc(sizeof(tSeznamMereni));
	seznamMereni->idSenzoru = idSenzoru;
	tMereni* jednotlivaMereni = malloc(sizeof(tMereni));
	int idMereni;
	tDateTime datumMereni;
	float m3Mereni;
	tMereni* tmpMereni = NULL;

	fptr = fopen("data.csv", "r");

	char buf[40];

	if (!fptr)
	{
		printf("Can't open file\nExiting...\n");
		exit(0);
	}
	fgets(buf, 40, fptr); //skips header
	int field_count = 0;
	int flag = 0;
	int currentId = 0;
	int breakFlag = 0;
	while (fgets(buf, 40, fptr))
	{
		field_count = 0;

		char* last = strrchr(buf, ';');
		m3Mereni = atof(last + 1);

		char* field = strtok(buf, ";");

		while (field)
		{
			if (field_count == 0)
			{
				idMereni = atoi(field);
			}
			if (field_count == 1)
			{
				currentId = atoi(field);
				if (currentId != idSenzoru)
				{
					++breakFlag;
					break;
				}
			}
			if (field_count == 2)
			{
				datumMereni = *dejDateTime(field);
			}
			field = strtok(NULL, ";");
			field_count++;
		}
		if (flag == 0 && breakFlag < 1)
		{
			++flag;
			jednotlivaMereni = vytvorMereni(idMereni, datumMereni, m3Mereni);
			seznamMereni->datumOd = datumMereni;
		}
		else if (breakFlag == 1)
		{
			breakFlag = 0;
		}
		else
		{
			tmpMereni = jednotlivaMereni;
			while (tmpMereni->dalsi != NULL)
			{
				tmpMereni = tmpMereni->dalsi;
			}
			tmpMereni->dalsi = vytvorMereni(idMereni, datumMereni, m3Mereni);
			seznamMereni->datumDo = datumMereni;
		}
	}


	fclose(fptr);
	seznamMereni->seznam = jednotlivaMereni;
	tmpMereni = NULL;
	free(tmpMereni);

	return seznamMereni;
}

void vypisVsechnaMereni()
{
	FILE* fptr;
	tMereni* jednotlivaMereni = malloc(sizeof(tMereni));
	int idMereni = 0;
	tDateTime datumMereni = {0, 0, 0, 0, 0, 0};
	float m3Mereni = 0;

	fptr = fopen("data.csv", "r");

	char buf[40];

	if (!fptr)
	{
		printf("Can't open file\nExiting...\n");
		exit(0);
	}
	fgets(buf, 40, fptr); //skips header
	int field_count = 0;
	int flag = 0;
	int currentId = 0;
	int breakFlag = 0;

	while (fgets(buf, 40, fptr))
	{
		field_count = 0;

		char* last = strrchr(buf, ';');
		m3Mereni = atof(last + 1);

		char* field = strtok(buf, ";");


		while (field)
		{
			if (field_count == 0)
			{
				idMereni = atoi(field);
			}
			if (field_count == 1)
			{
				currentId = atoi(field);
			}

			if (field_count == 2)
			{
				datumMereni = *dejDateTime(field);
			}
			field = strtok(NULL, ";");
			++field_count;
		}
		free(last);
		free(field);
		
		jednotlivaMereni = vytvorMereni(idMereni, datumMereni, m3Mereni);
		vypisMereni(jednotlivaMereni);
	}
	dealokujSeznam(jednotlivaMereni);
	fclose(fptr);
	free(fptr);
}

int timestampTimeToSecs(tDateTime timestamp)
{
	int retVal = timestamp.hour * 60 * 60 + timestamp.min * 60 + timestamp.sec;

	return retVal;
}

tMereni* odeberMereni(tSeznamMereni* origin, tDateTime timestamp)
{
	tSeznamMereni* seznam = origin;
	tMereni* tmp = seznam->seznam;
	tMereni* ret = seznam->seznam;
	int timestampSec = timestamp.hour * 60 * 60 + timestamp.min * 60 + timestamp.sec;
	while (tmp->dalsi != NULL)
	{
		tmp = tmp->dalsi;
		if (timestampSec == timestampTimeToSecs(tmp->timestamp) && timestamp.day == tmp->timestamp.day && timestamp.
			month == tmp->timestamp.month && timestamp.year == tmp->timestamp.year)
		{
			seznam = NULL;
			free(seznam);
			ret->dalsi = ret->dalsi->dalsi;
			ret = NULL;
			free(ret);
;			return tmp;
		}
		ret = ret->dalsi;
	}
	free(tmp);
	free(seznam);
	free(ret);
	
	return NULL;
}

void dealokujSeznam(tSeznamMereni* seznam)
{
	tMereni* m;
	while (seznam->seznam != NULL)
	{
		m = seznam->seznam;
		seznam->seznam = seznam->seznam->dalsi;
		free(m);
	}
}

void vypisAvgMereni(float** avgMereni)
{
	if (avgMereni)
	{
		for (int day = 0; day < 7; ++day)
		{
			switch (day)
			{
			case 0: printf("Mo.\n");
				break;
			case 1: printf("Tue.\n");
				break;
			case 2: printf("Wed.\n");
				break;
			case 3: printf("Thu.\n");
				break;
			case 4: printf("Fri.\n");
				break;
			case 5: printf("Sat.\n");
				break;
			case 6: printf("Sun.\n");
				break;
			}
			for (int hour = 0; hour < 24; ++hour)
			{
				printf("%f ", avgMereni[day][hour]);
			}
			printf("\n");
		}
	}
	else { printf("Not found."); }
}

float** analyzuj(tSeznamMereni* seznam, tDateTime datumOd, tDateTime datumDo)
{
	tMereni* mereni = seznam->seznam;
	float** avgMereni = calloc(7, sizeof(float));
	int** dayHits = calloc(7, sizeof(int));
	for (int i = 0; i < 7; ++i)
	{
		avgMereni[i] = calloc(24, sizeof(float));
		dayHits[i] = calloc(24, sizeof(int));
	}
	int min = timestampTimeToSecs(datumOd);
	int max = timestampTimeToSecs(datumDo);
	while (mereni->dalsi != NULL)
	{
		int currentTimeInSecs = timestampTimeToSecs(mereni->timestamp);
		if (currentTimeInSecs <= max && currentTimeInSecs >= min && mereni->m3 > 0)
		{
			avgMereni[mereni->timestamp.dayInWeek][mereni->timestamp.hour] += mereni->m3;
			++dayHits[mereni->timestamp.dayInWeek][mereni->timestamp.hour];
		}
		mereni = mereni->dalsi;
	}


	for (int d = 0; d < 7; ++d)
	{
		free(dayHits[d]);
	}
	free(dayHits);
	mereni = NULL;
	free(mereni);
	return avgMereni;
}

void dealokujMatici(float** matice)
{
	for (int d = 0; d < 7; ++d)
	{
		free(matice[d]);
	}
	free(matice);
}

float dejOdchylku(tSeznamMereni* seznam, float** matice, tDateTime timestamp)
{
	float** seznamTable = analyzuj(seznam, timestamp, timestamp);
	float retValue = seznamTable[timestamp.day][timestamp.hour] - matice[timestamp.day][timestamp.hour];
	dealokujMatici(seznamTable);
	return retValue;
}


int valueInArrayCheck(int val, int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == val)
			return 1;
		if (arr[i] == 0)
			return 0;
	}
	return 0;
}

int* dejPoleIdSenzoru()
{
	int size = 10;
	int* idArray = calloc(size, sizeof(int));

	FILE* fptr;
	fptr = fopen("data.csv", "r");

	char buf[40];

	if (!fptr)
	{
		printf("Can't open file\nExiting...\n");
		exit(0);
	}
	fgets(buf, 40, fptr); //skips header
	while (fgets(buf, 40, fptr))
	{
		strtok(buf, ";"); // skipping first cell
		int id = atoi(strtok(NULL, ";"));
		if (valueInArrayCheck(id, idArray, size) == 0)
		{
			for (int i = 0; i < size; ++i)
			{
				if (idArray[i] == 0)
				{
					idArray[i] = id;
					break;
				}
			}
		}
	}
	fclose(fptr);
	return idArray;
}

void vypisSeznam(tSeznamMereni* seznam)
{
	tMereni* tmp = seznam->seznam;
	while (tmp->dalsi != NULL)
	{
		vypisMereni(tmp);
		tmp = tmp->dalsi;
	}
	tmp = NULL;
	free(tmp);
}
