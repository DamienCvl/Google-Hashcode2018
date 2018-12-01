#pragma once
#include <vector>

using namespace std;

class Carte {

private:
	vector<vector<int>> carte;

public:
	Carte();					//Constructeur par défaut
	Carte(const Carte &);		//Constructeur de recopie
	~Carte();					//Destructeur par défaut

	string toString();			//Affichage de la Carte
};