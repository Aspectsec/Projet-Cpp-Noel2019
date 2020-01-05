#ifndef _UI_
#define _UI_

#include "Moteur.h"

class UI
{
	private:
		Moteur* moteur;
		
	public:
		UI(Moteur* ptr);
		~UI();
		
		void Start();
		void Menu();
};

#endif
