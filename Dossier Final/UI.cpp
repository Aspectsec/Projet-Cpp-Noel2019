#include "UI.h"
#include <string.h>


UI::UI(Moteur* ptr) : moteur(ptr)
{
	
}

UI::~UI()
{
	
}

void UI::Menu()
{
	moteur->Affiche();
	
	fprintf(stderr, "\n------------------------------Menu-------------------------------\n\n");
	
	fprintf(stderr, "0.\tQuitter\n");
	fprintf(stderr, "1.\tImporter un fichier CSV\n");
	fprintf(stderr, "2.\tImporter une ImageB\n");
	fprintf(stderr, "3.\tImporter une ImageNG\n");
	fprintf(stderr, "4.\tImporter une ImageRGB\n");
	fprintf(stderr, "5.\tExporter une Image\n");
	fprintf(stderr, "6.\tSupprimer une image\n");
	fprintf(stderr, "7.\tVisualiser une image\n");
	fprintf(stderr, "8.\tVisualiser deux images cote a cote\n");
	fprintf(stderr, "9.\tAugmenter la luminosite d'une Image\n");
	fprintf(stderr, "10.\tDiminuer la luminosite d'une Image\n");
	fprintf(stderr, "11.\tSoustraire deux images\n");
	fprintf(stderr, "12.\tSeuillage\n");
	fprintf(stderr, "13.\tNegatif\n");
	fprintf(stderr, "14.\tFiltreMedian\n");
	fprintf(stderr, "15.\tFiltreMoyenneur\n");
	fprintf(stderr, "16.\tDilatation\n");
	fprintf(stderr, "17.\tErosion\n");
}

void UI::Start()
{
	short choix = -1;
	int id1, id2;
	int taille;
	char path[80];
	
	ifstream fImagesIn("Sauvegarde.dat", ios::in);
	moteur->LoadState(fImagesIn);
	fImagesIn.close();
	
	while(choix != 0)
	{
		do
		{
			Menu();
			fprintf(stderr, "\n> ");
			fflush(stdin);
			scanf("%hu", &choix);
		}while(choix < 0 || choix > 17);
		
		try
		{
			switch(choix)
			{
				case 0 : 	{
									ofstream fImagesOut("Sauvegarde.dat", ios::out);
									moteur->SaveState(fImagesOut);
									fImagesOut.close();
									break;
								}
				
				case 1:		fprintf(stderr, "\nChemin : ");
								fflush(stdin);
								fgets(path, sizeof(path), stdin);
								path[strcspn(path, "\n")] = '\0';
								moteur->ImportCSV(path);
								break;
				
				case 2 :		fprintf(stderr, "\nChemin : ");
								fflush(stdin);
								fgets(path, sizeof(path), stdin);
								path[strcspn(path, "\n")] = '\0';
								fprintf(stderr, "\nID de l'image importee : %d\n", moteur->ImporteImageB(path));
								break;
				
				case 3 :		fprintf(stderr, "\nChemin : ");
								fflush(stdin);
								fgets(path, sizeof(path), stdin);
								path[strcspn(path, "\n")] = '\0';
								fprintf(stderr, "\nID de l'image importee : %d\n", moteur->ImporteImageNG(path));
								break;
						
				case 4:		fprintf(stderr, "\nChemin : ");
								fflush(stdin);
								fgets(path, sizeof(path), stdin);
								path[strcspn(path, "\n")] = '\0';
								fprintf(stderr, "\nID de l'image importee : %d\n", moteur->ImporteImageRGB(path));
								break;
				
				case 5:		fprintf(stderr, "\nID de l'image : ");
								scanf("%d", &id1);
								fprintf(stderr, "\nChemin : ");
								fflush(stdin);
								fgets(path, sizeof(path), stdin);
								path[strcspn(path, "\n")] = '\0';
								moteur->ExporterBMP(id1, path);
								break;
			
				case 6:		fprintf(stderr, "\nID de l'image : ");
								scanf("%d", &id1);
								moteur->SupprimeImage(id1);

								break;
						
				case 7:		fprintf(stderr, "\nID de l'image : ");
								scanf("%d", &id1);
								moteur->VisualiseImage(id1);
								break;
						
				case 8:		fprintf(stderr, "\nID de l'image 1 : ");
								scanf("%d", &id1);
								fprintf(stderr, "\nID de l'image 2 : ");
								scanf("%d", &id2);
								moteur->VisualiseImages(id1, id2);
								break;
						
				case 9 :		fprintf(stderr, "\nID de l'image : ");
								scanf("%d", &id1);
								fprintf(stderr, "\nValeur : ");
								scanf("%d", &taille);
								fprintf(stderr, "\nID de l'image modifiee : %d\n", moteur->AugmenteLuminosite(id1, taille));
								break;
						
				case 10 :		fprintf(stderr, "\nID de l'image : ");
								scanf("%d", &id1);
								fprintf(stderr, "\nValeur : ");
								scanf("%d", &taille);
								fprintf(stderr, "\nID de l'image modifiee : %d\n", moteur->DiminueLuminosite(id1, taille));
								break;
						
				case 11 :		fprintf(stderr, "\nID de l'image 1 : ");
								scanf("%d", &id1);
								fprintf(stderr, "\nID de l'image 2 : ");
								scanf("%d", &id2);
								fprintf(stderr, "\nID de l'image modifiee : %d\n", moteur->Soustraire(id1, id2));
								break;
						
				case 12 :		fprintf(stderr, "\nID de l'image : ");
								scanf("%d", &id1);
								fprintf(stderr, "\nValeur : ");
								scanf("%d", &taille);
								fprintf(stderr, "\nID de l'image modifiee : %d\n", moteur->Seuillage(id1, taille));
								break;
						
				case 13 :	fprintf(stderr, "\nID de l'image : ");
								scanf("%d", &id1);
								fprintf(stderr, "\nID de l'image modifiee : %d\n", moteur->Negatif(id1));
								break;
					
				case 14 :	fprintf(stderr, "\nID de l'image : ");
								scanf("%d", &id1);
								fprintf(stderr, "\nTaille du filtre : ");
								scanf("%d", &taille);
								fprintf(stderr, "\nID de l'image modifiee : %d\n", moteur->FiltreMedian(id1, taille));
								break;
							
				case 15 :	fprintf(stderr, "Voulez vous filtrer une partie(1) ou toute l'image(2) ? ");
								scanf("%hu", &choix);
								fprintf(stderr, "\nID de l'image : ");
								scanf("%d", &id1);
								fprintf(stderr, "\nTaille du filtre : ");
								scanf("%d", &taille);
								
								if(choix == 2) fprintf(stderr, "\nID de l'image modifiee : %d\n", moteur->FiltreMoyenneur(id1, taille));
								else				fprintf(stderr, "\nID de l'image modifiee : %d\n", moteur->FiltreMoyenneurSelection(id1, taille));
								
								break;
							
				case 16 :	fprintf(stderr, "\nID de l'image : ");
								scanf("%d", &id1);
								fprintf(stderr, "\nTaille du filtre : ");
								scanf("%d", &taille);
								fprintf(stderr, "\nID de l'image modifiee : %d\n", moteur->Dilatation(id1, taille));
								break;
							
				case 17 :	fprintf(stderr, "\nID de l'image : ");
								scanf("%d", &id1);
								fprintf(stderr, "\nTaille du filtre : ");
								scanf("%d", &taille);
								fprintf(stderr, "\nID de l'image modifiee : %d\n", moteur->Erosion(id1, taille));
								break;
			}
		cout << endl << endl;
		}
		catch(MoteurException e) { fprintf(stderr, "%s\n", e.getErreur()); moteur->log(e.getErreur());}
		catch(WindowSDLexception e) { fprintf(stderr, "%s\n", e.getMessage()); moteur->log(e.getMessage());}
		catch(RGBException e) { fprintf(stderr, "%s\n", e.getErreur()); moteur->log(e.getErreur());}
		catch(XYException e) { fprintf(stderr, "%s\n", e.getErreur()); moteur->log(e.getErreur());}
	}
	
	exit(0);
}
