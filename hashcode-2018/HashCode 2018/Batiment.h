#pragma once
#include <vector>

using namespace std;

class Batiment {

private:
	vector<pair<int, int>> briques;
	vector<Batiment> tableauBatiment;
	pair<int, int> coordonees;
	int hauteur;
	int largeur;

public:
	Batiment();														//Constructeur par défaut
	Batiment(const int, const int, pair<int, int>);					//Constructeur
	Batiment(const Batiment &);										//Constructeur de recopie
	~Batiment();													//Destructeur par défaut

	virtual void ajouterBrique(pair<int, int>);						//Ajoute un # du fichier de lecture
	virtual void setCoordonees(pair<int, int>);						//Ajout de la coordonees du batiment
	virtual void toString();										//Affichage du batiment
	void insert(Batiment b);										//Inserer un Batiment a la liste 
};