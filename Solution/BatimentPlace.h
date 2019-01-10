#pragma once
#include <vector>

#include "Batiment.h"

using namespace std;

class BatimentPlace															//Un objet "BatimentPlace" est un objet possédant un accès à un objet "Batiment"
																			//afin de connaitre sa structure, ainsi que des coordonées de placement.						
{
private:
	pair<int, int> coordonnees;
	const Batiment * batiment;

public:
	BatimentPlace(const Batiment * bat, pair<int, int> coord);			//Constructeur

	pair<int, int>		getCoordonnees();
	void				setCoordonnees(pair<int, int> coord);

	Batiment			getBatiment();

};