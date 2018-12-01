#pragma once
#include <vector>

using namespace std;

class Batiment {

private:
	vector<vector <bool>> schema;
	int * coordonees;
	int hauteur;
	int largeur;

public:
	Batiment(const int &, const int &, int *);								//Constructeur par défaut
	Batiment(const Batiment &);												//Constructeur de recopie
	~Batiment();															//Destructeur par défaut

	virtual void ajouterBrique(const int &, const int &, const bool &);
	virtual void toString();												//Affichage du Batiment
};