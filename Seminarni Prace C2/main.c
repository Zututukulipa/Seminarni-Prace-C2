#include "Datetime.h"
#include "Mereni.h"
#include <stdio.h>
#include <crtdbg.h>
#include "SeznamMereni.h"
#include <stdlib.h>

void controls(tSeznamMereni* seznam, char* date, float** currentAnalysis)
{
	tDateTime dateTime;
	float odchylka = 0.0f;
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
			odeberMereni(seznam, dejDateTime(date));
			date = NULL;
			controls(seznam, date, currentAnalysis);
		}
		break;
	case 5:
		if (seznam)
		{
			if (currentAnalysis)
			{
				dealokujMatici(currentAnalysis);
			}

			printf("FROM\nEnter date (yyyy-mm-dd hh:mm:ss):\n>");
			scanf(" %[^\n]", date);
			dateTime = dejDateTime(date);
			printf("TO\nEnter date (yyyy-mm-dd hh:mm:ss):\n>");
			scanf(" %[^\n]", date);
			currentAnalysis = analyzuj(seznam, dateTime,
			                            dejDateTime(date));
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
		{
			printf("Enter date (yyyy-mm-dd hh:mm:ss)\n");
			scanf(" %[^\n]s", date);
			odchylka = dejOdchylku(seznam, currentAnalysis, dejDateTime(date));
			printf("\n\tDeviation of %s is:\n\t%f\n", date, odchylka);
		}
		else
			printf("Average set is not yet created.\n");
		controls(seznam, date, currentAnalysis);
		break;
	case 8:
		if (!currentAnalysis){
			dealokujMatici(currentAnalysis);

		}
		controls(seznam, date, currentAnalysis);
		break;
	case 9:
		if (!seznam)
			dealokujSeznam(seznam);
		controls(seznam, date, currentAnalysis);
		break;
	default:
		if (seznam)
		{
			dealokujSeznam(seznam);
		}if(currentAnalysis)
		{
			dealokujMatici(currentAnalysis);

		}
		
		


		break;
	}
}

int main()
{
	tSeznamMereni* seznam = NULL;
	int choiceId = -1;
	char date[19];
	float*** currentAnalysis = calloc(7, sizeof(float));
	for (int i = 0; i < 7; ++i)
		currentAnalysis[i] = calloc(24, sizeof(float));
	controls(seznam, date, *currentAnalysis);
	if (seznam)
	{
		dealokujSeznam(seznam);
	}
	


	if (_CrtDumpMemoryLeaks())
	{
		//TODO kdyz pouzivam workaround na tu dealokaci, tak mi porad nekde lita jeden zaznam a ani za hovno ho nemuzu najit :/
		//Kurva...
		printf("UNALLOCATED MEMORY!");
	}
	else
	{
		printf("MEMORY SUCCESSFULLY DELETED");
	}

	return 0;
}
