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

// vrac� pole id v�ech senzor� v souboru
int* dejPoleIdSenzoru();

// na�te v�echna m��en� dan�ho senzoru, vyu��v� vytvorMereni, pokud ji� n�jak� seznam existuje, mus� b�t dealokov�n
tSeznamMereni *nactiMereni(int idSenzoru);

// vyp�e v�echna m��en�, vyu��v� vypisMereni
void vypisVsechnaMereni();

// odebere a vr�t� po�adovan� m��en� ze seznamu
tMereni* odeberMereni(tDateTime timestamp);

// sma� (dealokuj) v�echny z�znamy a tSeznam
void dealokujSeznam();

// V�po�et pr�m�ru pro v�echny kombinace den v t�dnu,
// kter� vr�t� dynamick� 2D pole 7x24 �den v t�dnu� x �hodina dne� (v litrech)
float** analyzuj(tDateTime datumOd, tDateTime datumDo);

// sma� (dealokuj) matici
void dealokujMatici();

//vr�t� odchylku v litrech dan�ho z�znamu (m��en� v dle timestamp) oproti spr�vn�mu pr�m�ru z matice pr�m�r�
float dejOdchylku(tDateTime timestamp);
#endif
