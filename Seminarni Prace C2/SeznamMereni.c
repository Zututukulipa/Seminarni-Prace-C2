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

	fptr = fopen("data.csv", "r");

	char buf[40];

	if (!fptr) {
		printf("Can't open file\nExiting...\n");
		exit(0);
	}
	fgets(buf, 40, fptr); //skips header
	int field_count = 0;
	int flag = 0;
	int currentId = 0;
	int breakFlag = 0;
	while (fgets(buf, 40, fptr)) {
		field_count = 0;

		char* last = strrchr(buf, ';');
		m3Mereni = atof(last + 1);

		char* field = strtok(buf, ";");

		if (last != NULL) {
			printf("Last token: %s\n", last + 1);
		}

		while (field) {
			if (field_count == 0) {
				idMereni = atoi(field);
			}
			if (field_count == 1) {
				currentId = atoi(field);
				if (currentId != idSenzoru) {
					++breakFlag;
					break;
				}
			}
			if (field_count == 2) {
				datumMereni = *dejDateTime(field);
			}
			field = strtok(NULL, ";");
			field_count++;

		}
		if (flag == 0) {
			++flag;
			jednotlivaMereni = vytvorMereni(idMereni, datumMereni, m3Mereni);
		}
		else if (breakFlag == 1) {
			breakFlag = 0;
		}
		else
		{
			tMereni* tmpMereni = jednotlivaMereni;
			while (tmpMereni->dalsi != NULL)
			{
				tmpMereni = tmpMereni->dalsi;
			}
			tmpMereni->dalsi = vytvorMereni(idMereni, datumMereni, m3Mereni);

		}
	}


	fclose(fptr);
	seznamMereni->seznam = jednotlivaMereni;
	return seznamMereni;
}

void vypisVsechnaMereni()
{
	FILE* fptr;
	tMereni* jednotlivaMereni = malloc(sizeof(tMereni));
	int idMereni = 0;
	tDateTime datumMereni = { 0,0,0,0,0,0 };
	float m3Mereni = 0;

	fptr = fopen("data.csv", "r");

	char buf[40];

	if (!fptr) {
		printf("Can't open file\nExiting...\n");
		exit(0);
	}
	fgets(buf, 40, fptr); //skips header
	int field_count = 0;
	int flag = 0;
	int currentId = 0;
	int breakFlag = 0;
	
	while (fgets(buf, 40, fptr)) {
		field_count = 0;

		char* last = strrchr(buf, ';');
		m3Mereni = atof(last + 1);

		char* field = strtok(buf, ";");


		while (field) {
			if (field_count == 0) {
				idMereni = atoi(field);
			}
			if (field_count == 1) {
				currentId = atoi(field);
			}

			if (field_count == 2) {
				datumMereni = *dejDateTime(field);
			}
			field = strtok(NULL, ";");
		}
					   		

		jednotlivaMereni = vytvorMereni(idMereni, datumMereni, m3Mereni);
		vypisMereni(jednotlivaMereni);
	}
	fclose(fptr);

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

		if (!fptr) {
			printf("Can't open file\nExiting...\n");
			exit(0);
		}
		fgets(buf, 40, fptr); //skips header
		while (fgets(buf, 40, fptr)) {
			strtok(buf, ";"); // skipping first cell
			int id = atoi(strtok(NULL, ";"));
			if (valueInArrayCheck(id, idArray, size) == 0) {
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

		return idArray;
	}