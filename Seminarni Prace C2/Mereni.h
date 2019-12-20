#pragma once
#ifndef SENZOR_H
#define SENZOR_H
#include "Datetime.h"

typedef struct mereni {
	int idMereni;
	tDateTime timestamp;
	float m3;
	struct mereni* dalsi;
}tMereni;

tMereni* vytvorMereni(int idMereni, tDateTime ts, float m3);
// vrac� adresu dynamick� alokace mereni, ukazatel dalsi se nastav� na NULL
void vypisMereni(tMereni* mereni);
//vyp�e mereni na obrazovku 
#endif
