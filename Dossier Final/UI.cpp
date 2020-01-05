#include "UI.h"


UI::UI(Moteur* ptr) : moteur(ptr)
{
	
}

UI::~UI()
{
	
}

void UI::Menu()
{
	moteur->Affiche();
	
	fprintf(stderr, "\n-------------------------------\n");
	
	fprintf(stderr, "0.\tQuitter\n");
	fprintf(stderr, "1.\tImporter une ImageNG\n");
	fprintf(stderr, "2.\tImporter une ImageRGB\n");
	fprintf(stderr, "3.\tSupprimer une image\n");
	fprintf(stderr, "4.\tVisualiser une image\n");
	fprintf(stderr, "5.\tVisualiser deux images cote a cote\n");
	fprintf(stderr, "6.\tAugmenter la luminosite d'une ImageNG\n");
	fprintf(stderr, "7.\tDiminuer la luminosite d'une ImageNG\n");
	fprintf(stderr, "8.\tSoustraire\n");
	fprintf(stderr, "9.\tSeuillage\n");
	fprintf(stderr, "10.\tNegatif\n");
	fprintf(stderr, "11.\tFiltreMedian\n");
	fprintf(stderr, "12.\tFiltreMoyenneur\n");
	fprintf(stderr, "13.\tDilatation\n");
	fprintf(stderr, "14.\tErosion\n");
}

void UI::Start()
{
	short choix;
	int id1, id2;
	int taille;
	char path[80];
	
	while(choix != 0)
	{
		do
		{
			Menu();
			fprintf(stderr, "\n> ");
			fflush(stdin);
			scanf("%hu", &choix);
		}while(choix < 0 || choix > 15);
		
		switch(choix)
		{
			case 0 : break;
			
			case 1 :		fprintf(stderr, "\nChemin : ");
							fflush(stdin);
							gets(path);
							fprintf(stderr, "\nID de l'image importee : %d", moteur->ImporteImageNG(path));
							break;
						
			case 2:		fprintf(stderr, "\nChemin : ");
							fflush(stdin);
							gets(path);
							fprintf(stderr, "\nID de l'image importee : %d", moteur->ImporteImageRGB(path));
							break;
			
			case 3:		fprintf(stderr, "\nID de l'image : ");
							scanf("%d", &id1);
							moteur->SupprimeImage(id1);
							break;
						
			case 4:		fprintf(stderr, "\nID de l'image : ");
							scanf("%d", &id1);
							moteur->VisualiseImage(id1);
							break;
						
			case 5:		fprintf(stderr, "\nID de l'image 1 : ");
							scanf("%d", &id1);
							fprintf(stderr, "\nID de l'image 2 : ");
							scanf("%d", &id2);
							moteur->VisualiseImages(id1, id2);
							break;
						
			case 6 :		fprintf(stderr, "\nID de l'image : ");
							scanf("%d", &id1);
							fprintf(stderr, "\nValeur : ");
							scanf("%d", &taille);
							fprintf(stderr, "\nID de l'image modifiee : %d", moteur->AugmenteLuminosite(id1, taille));
							break;
						
			case 7 :		fprintf(stderr, "\nID de l'image : ");
							scanf("%d", &id1);
							fprintf(stderr, "\nValeur : ");
							scanf("%d", &taille);
							fprintf(stderr, "\nID de l'image modifiee : %d", moteur->DiminueLuminosite(id1, taille));
							break;
						
			case 8 :		fprintf(stderr, "\nID de l'image 1 : ");
							scanf("%d", &id1);
							fprintf(stderr, "\nID de l'image 2 : ");
							scanf("%d", &id2);
							fprintf(stderr, "\nID de l'image modifiee : %d", moteur->Soustraire(id1, id2));
							break;
						
			case 9 :		fprintf(stderr, "\nID de l'image : ");
							scanf("%d", &id1);
							fprintf(stderr, "\nValeur : ");
							scanf("%d", &taille);
							fprintf(stderr, "\nID de l'image modifiee : %d", moteur->Seuillage(id1, taille));
							break;
						
			case 10 :	fprintf(stderr, "\nID de l'image : ");
							scanf("%d", &id1);
							fprintf(stderr, "\nID de l'image modifiee : %d", moteur->Negatif(id1));
							break;
					
			case 11 :	fprintf(stderr, "\nID de l'image : ");
							scanf("%d", &id1);
							fprintf(stderr, "\nTaille du filtre : ");
							scanf("%d", &taille);
							fprintf(stderr, "\nID de l'image modifiee : %d", moteur->FiltreMedian(id1, taille));
							break;
							
			case 12 :	fprintf(stderr, "Voulez vous filtrer une partie(1) ou toute l'image(2) ? ");
							scanf("%hu", &choix);
							fprintf(stderr, "\nTaille du filtre : ");
							scanf("%d", &taille);
							if(choix == 1) fprintf(stderr, "\nID de l'image modifiee : %d", moteur->FiltreMoyenneur(id1, taille));
							else				fprintf(stderr, "\nID de l'image modifiee : %d", moteur->FiltreMoyenneurSelection(id1, taille));
							break;
							
			case 13 :	fprintf(stderr, "\nID de l'image : ");
							scanf("%d", &id1);
							fprintf(stderr, "\nTaille du filtre : ");
							scanf("%d", &taille);
							fprintf(stderr, "\nID de l'image modifiee : %d", moteur->Dilatation(id1, taille));
							break;
							
			case 14 :	fprintf(stderr, "\nID de l'image : ");
							scanf("%d", &id1);
							fprintf(stderr, "\nTaille du filtre : ");
							scanf("%d", &taille);
							fprintf(stderr, "\nID de l'image modifiee : %d", moteur->Erosion(id1, taille));
							break;
		}
	}
	
	exit(0);
}
