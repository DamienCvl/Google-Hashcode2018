#pragma once
#include <vector>

#include "Batiment.h"

using namespace std;

class BatimentResidentiel : Batiment {

private:
	int capacite;

public:
	BatimentResidentiel();									//Constructeur par défaut
	BatimentResidentiel(const BatimentResidentiel &);		//Constructeur de recopie
	~BatimentResidentiel();									//Destructeur par défaut
};