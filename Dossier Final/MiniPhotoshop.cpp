#include "Moteur.h"
#include "UI.h"

int main()
{
	Moteur moteur;
	UI ui(&moteur);
	
	ui.Start();
	
	return 0;
}
