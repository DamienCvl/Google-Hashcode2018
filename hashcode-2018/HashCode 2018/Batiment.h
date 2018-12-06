#pragma once
#include <vector>
using namespace std;

class Batiment {

private:
	vector<pair<int, int>> briques;
	pair<int, int> coordonees;
	int hauteur;
	int largeur;
	int specificite; // Taille ou capacite

public:
	Batiment();														//Constructeur par d�faut
	Batiment(const int, const int, pair<int, int>);					//Constructeur
	Batiment(const Batiment &);										//Constructeur de recopie
	~Batiment();													//Destructeur par d�faut

	virtual void ajouterBrique(pair<int, int>);						//Ajoute un # du fichier de lecture
	virtual void setCoordonees(pair<int, int>);						//Ajout de la coordonees du batiment
	virtual void toString();										//Affichage du batiment
	int getLargeur();
	int getHauteur();
	pair<int, int> getCoordonees();
	int getSpecificite();
	vector<pair<int, int>> GetBriques();
};