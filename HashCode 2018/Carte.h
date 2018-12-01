#pragma once
#include <vector>

using namespace std;

class Carte {

private:
	vector<vector<int>> carte;

public:
	Carte();					//Constructeur par d�faut
	Carte(const Carte &);		//Constructeur de recopie
	~Carte();					//Destructeur par d�faut

	string toString();			//Affichage de la Carte
};