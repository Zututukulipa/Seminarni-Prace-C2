#include "Datetime.h"
#include "Mereni.h"
#include <stdio.h>
#include "SeznamMereni.h"

int main()
{
	vypisVsechnaMereni();
	int* ids = dejPoleIdSenzoru();
	tSeznamMereni* seznam = nactiMereni(1);
	

	return 0;	
}
