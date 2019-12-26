
#include "Mereni.h"
#include <stdlib.h>
#include <stdio.h>

tMereni* vytvorMereni(int idMereni, tDateTime ts, float m3)
{
	tMereni *vytvoreneMereni = malloc(sizeof(tMereni));
	if (vytvoreneMereni) {
		vytvoreneMereni->idMereni = idMereni;
		vytvoreneMereni->timestamp = ts;
		vytvoreneMereni->m3 = m3;
		vytvoreneMereni->dalsi = NULL;
		return  vytvoreneMereni;
	}
	else
		return NULL;
}


void vypisMereni(tMereni* mereni)
{
	printf("ID: %d\nDATE: %d-%d-%d %d:%d:%d\nCONSUMPTION: %f\n\n",
		mereni->idMereni,
		mereni->timestamp.year, mereni->timestamp.month, mereni->timestamp.day,
		mereni->timestamp.hour, mereni->timestamp.min, mereni->timestamp.sec,
		mereni->m3);
}