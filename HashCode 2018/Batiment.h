#pragma once
#include <vector>

using namespace std;

class Batiment {

private:
	vector<pair<int, int>> briques;
	pair<int, int> coordonees;
	int hauteur;
	int largeur;

public:
	Batiment();														//Constructeur par d�faut
	Batiment(const int, const int, pair<int, int>);					//Constructeur
	Batiment(const Batiment &);										//Constructeur de recopie
	~Batiment();													//Destructeur par d�faut

	virtual void ajouterBrique(pair<int, int>);						//Ajoute un # du fichier de lecture
	virtual void toString();										//Affichage du batiment
};