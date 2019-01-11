#pragma once
#include <vector>

#include "Batiment.h"

using namespace std;

class BatimentPlace																									//Un objet "BatimentPlace" est un objet possédant un accès à un objet "Batiment"
																																		//afin de connaitre sa structure, ainsi que des coordonées de placement.
{
	private:
		pair<int, int> 		coordonnees;																	//Coordonées de placement du Bâtiment Placé sur une Carte
		Batiment 					batiment;																			//Référence au Bâtiment disponibles de la Carte

	public:
		BatimentPlace(Batiment bat, pair<int, int> coord);							//Constructeur

		pair<int, int>		getCoordonnees();															//Getter de coordonées
		Batiment					getBatiment();																//Getter de batiment

		void							setCoordonnees(pair<int, int> coord);					//Setter de coordonées
};
