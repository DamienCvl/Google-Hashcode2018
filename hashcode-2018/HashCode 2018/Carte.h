#pragma once
#include <vector>

using namespace std;

class Carte {

private:
	vector<vector<int>> schema;
	int cote;

public:
	Carte();					//Constructeur par défaut
	Carte(int cote);			//Constructeur
	Carte(const Carte &);		//Constructeur de recopie
	~Carte();					//Destructeur par défaut

	void toString();			//Affichage de la Carte
};