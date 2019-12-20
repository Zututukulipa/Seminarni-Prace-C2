#pragma once
#ifndef SEZNAM_H
#define  SEZNAM_H

#include "Datetime.h"
#include "Mereni.h"

typedef struct
{
	int idSenzoru;
	tDateTime datumOd;
	tDateTime datumDo;
	tMereni* seznam;
}tSeznamMereni;


tSeznamMereni* load(char* filePath);

// vrací pole id všech senzorù v souboru
int* dejPoleIdSenzoru();

// naète všechna mìøení daného senzoru, využívá vytvorMereni, pokud již nìjaký seznam existuje, musí být dealokován
tSeznamMereni *nactiMereni(int idSenzoru);

// vypíše všechna mìøení, využívá vypisMereni
void vypisVsechnaMereni();

// odebere a vrátí požadované mìøení ze seznamu
tMereni* odeberMereni(tDateTime timestamp);

// smaž (dealokuj) všechny záznamy a tSeznam
void dealokujSeznam();

// Výpoèet prùmìru pro všechny kombinace den v týdnu,
// který vrátí dynamické 2D pole 7x24 „den v týdnu“ x „hodina dne“ (v litrech)
float** analyzuj(tDateTime datumOd, tDateTime datumDo);

// smaž (dealokuj) matici
void dealokujMatici();

//vrátí odchylku v litrech daného záznamu (mìøení v dle timestamp) oproti správnému prùmìru z matice prùmìrù
float dejOdchylku(tDateTime timestamp);
#endif
