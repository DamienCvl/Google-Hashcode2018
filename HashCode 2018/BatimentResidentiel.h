#pragma once
#include <vector>

#include "Batiment.h"

using namespace std;

class BatimentResidentiel : Batiment {

private:
	int capacite;

public:
	BatimentResidentiel();									//Constructeur par d�faut
	BatimentResidentiel(const BatimentResidentiel &);		//Constructeur de recopie
	~BatimentResidentiel();									//Destructeur par d�faut
};