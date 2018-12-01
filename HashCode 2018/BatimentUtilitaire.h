#pragma once
#include <vector>

#include "Batiment.h"

using namespace std;

class BatimentUtilitaire : Batiment {

private:
	int type;

public:
	BatimentUtilitaire();								//Constructeur par défaut
	BatimentUtilitaire(const BatimentUtilitaire &);		//Constructeur de recopie
	~BatimentUtilitaire();								//Destructeur par défaut
};