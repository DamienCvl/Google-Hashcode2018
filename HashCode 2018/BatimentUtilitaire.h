#pragma once
#include <vector>

#include "Batiment.h"

using namespace std;

class BatimentUtilitaire : Batiment {

private:
	int type;

public:
	BatimentUtilitaire(const int hauteur, const int largeur, pair<int, int> coord, const int type);			//Constructeur par défaut
	BatimentUtilitaire(const BatimentUtilitaire &);		//Constructeur de recopie
	~BatimentUtilitaire();								//Destructeur par défaut
};