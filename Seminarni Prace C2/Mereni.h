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
// vrací adresu dynamické alokace mereni, ukazatel dalsi se nastaví na NULL
void vypisMereni(tMereni* mereni);
//vypíše mereni na obrazovku 
#endif
