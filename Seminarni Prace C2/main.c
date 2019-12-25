#include "Datetime.h"
#include "Mereni.h"
#include <stdio.h>
#include <crtdbg.h>
#include "SeznamMereni.h"
#include <stdlib.h>

void controls(tSeznamMereni* seznam, char* date, float** currentAnalysis)
{
	int choiceId = -1;
	printf(
		"SENSOR CONTROLS\nplease choose your action..\n1. Display all measurements\n2. Load measurements\n3. Display loaded measurements\n4. Delete record\n5. Create Average Set\n6. Save Average Set\n7. Display deviation to Average Set\n8. Delete Average Set\n9. Unfocus Measuremets\n-----------------------\n>");
	scanf("%d", &choiceId);
	printf("\n");
	switch (choiceId)
	{
	case 1:
		vypisVsechnaMereni();
		controls(seznam, date, currentAnalysis);
		break;
	case 2:
		if (seznam)
			dealokujSeznam(seznam);
		int sensorId = -1;
		int* pole = dejPoleIdSenzoru();
		for (int index = 0; index < 9; ++index)
			printf("[%d] ", pole[index]);
		free(pole);
		printf("\nPlease enter sensor ID\n");
		scanf("%d", &sensorId);
		printf("\n");
		seznam = nactiMereni(sensorId);
		controls(seznam, date, currentAnalysis);
		break;
	case 3:
		if (seznam)
			vypisSeznam(seznam);
		else
			printf("Please, allocate a list first..\n");
		controls(seznam, date, currentAnalysis);
		break;
	case 4:
		if (seznam)
		{
			printf("Please, enter measurement timestamp..\nformat: 2018-06-01 01:00:00\n");
			scanf("%s", &date);
			odeberMereni(seznam, *dejDateTime(date));
			date = NULL;
			controls(seznam, date, currentAnalysis);
		}
		break;
	case 5:
		if (seznam)
		{
			currentAnalysis = analyzuj(seznam, *dejDateTime("2000-01-01 00:00:00"),
			                           *dejDateTime("2100-12-12 23:59:59"));
			vypisAvgMereni(currentAnalysis);
			controls(seznam, date, currentAnalysis);
		}
		break;
	case 6:
		printf("Saved.\noutput.csv\n");
		controls(seznam, date, currentAnalysis);
		break;
	case 7:
		if (currentAnalysis)
			vypisAvgMereni(currentAnalysis);
		else
			printf("Average set is not yet created.\n");
		controls(seznam, date, currentAnalysis);
		break;
	case 8:
		if (!currentAnalysis)
			dealokujMatici(currentAnalysis);
		controls(seznam, date, currentAnalysis);
		break;
	case 9:
		if (!seznam)
			dealokujSeznam(seznam);
		controls(seznam, date, currentAnalysis);
		break;
	default:
		if(seznam)
		{
			dealokujSeznam(seznam);
		}
		if(currentAnalysis)
		{
			dealokujMatici(currentAnalysis);
		}
		if(date)
		{
			free(date);
		}
		break;
	}
}

int main()
{
	tSeznamMereni* seznam = NULL;
	int choiceId = -1;
	char* date = NULL;
	float** currentAnalysis = NULL;
	controls(seznam, date, currentAnalysis);
	if (seznam)
	{
		dealokujSeznam(seznam);
	}
	if (currentAnalysis)
	{
		dealokujMatici(currentAnalysis);
	}
	if (date)
	{
		free(date);
	}
	if(_CrtDumpMemoryLeaks())
	{
		//Kurva...
		printf("UNALLOCATED MEMORY!");
	}else
	{
		printf("MEMORY SUCCESSFULLY DELETED");
	}

	return 0;
}
