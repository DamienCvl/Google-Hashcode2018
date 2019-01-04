#pragma once
#include <iostream>

#include "Carte.h"


using namespace std;

Carte::Carte()
{

}

Carte::Carte(int c)
{
	this->cote = c;

	vector<int> donnees(c, 0);					//Creation de la matrice
	vector<vector<int>> matrice(c, donnees);	

	this->schema = matrice;
}

Carte::Carte(const Carte &)
{

}

Carte::~Carte()
{

}

void Carte::toString()
{
	cout << "\nAffichage de la Carte : \n";

	for (int i = 0; i <= this->cote - 1; i++)		//Affichage de la matrice
	{
		for (int j = 0; j <= cote - 1; j++) {
			cout << schema[i][j] << " ";
		}
		cout << endl;
	}
}

vector<Batiment> Carte::getListeBatiments()
{
	return this->listeBatiments;
}

void Carte::setListeBatiments(vector<Batiment> lBatiments)
{
	this->listeBatiments = lBatiments;
}

vector<BatimentPlace> Carte::getListeBatimentsPlaces()
{
	return this->listeBatimentsPlaces;
}

void Carte::ajouterBatimentPlace(BatimentPlace bp)
{
	this->listeBatimentsPlaces.push_back(bp);
}

void Carte::placerBatiment(Batiment b, pair<int, int> c)
{
	bool condition = true;

	BatimentPlace bp(&b, c);

	int x, y;

	cout << "Coordonees : (" << c.first << ";" << c.second << ")" << endl;
	vector<pair<int, int>> briques = bp.getBatiment().getBriques();

	for (int i = 0; i < briques.size(); i++)
	{
		x = briques[i].first + c.first;
		y = briques[i].second + c.second;

		if (this->schema[x][y] != 0) {
			condition = false;
		}
	}

	if (condition == true) {
		for (int i = 0; i < briques.size(); i++)
		{
			x = briques[i].first + c.first;
			y = briques[i].second + c.second;

			this->schema[x][y] = bp.getBatiment().getSpecificite();
		}
		this->ajouterBatimentPlace(bp);
	}
	else {
		cout << "Place occupée" << endl;
	}
}

//Tiphaine
void Carte::calculCoeff(vector<Batiment> listeBatiments) {
	for (int i = 0; i < listeBatiments.size(); i++) {

		float sizeBatiment = listeBatiments[i].getBriques().size();
		float hauteur = listeBatiments[i].getHauteur();
		float largeur = listeBatiments[i].getLargeur();
		
		if (listeBatiments[i].getSpecificite() < 0) {
			
			float spe = -listeBatiments[i].getSpecificite();

			// nombre de case prise/(largeur*hauteur) * nombre utilitaire 		
			float coeff = sizeBatiment/(hauteur * largeur)*spe;
			listeCoeffResidentiel.push_back(pair<Batiment, float>(listeBatiments[i], coeff));
		}
		else {
			float coeff = sizeBatiment / (hauteur * largeur);
			listeCoeffUtilitaire.push_back(pair<Batiment, float>(listeBatiments[i], coeff));
		}
	}
}

void Carte::afficherBatCoeff() {

	for (int i = 0; i < listeCoeffResidentiel.size(); i++) {
		cout << "Batiment : " << i << " - Spe : " << listeCoeffResidentiel[i].first.getSpecificite() << " - Coeff : " << listeCoeffResidentiel[i].second << endl;
	}

	for (int i = 0; i < listeCoeffUtilitaire.size(); i++) {
		cout << "Batiment : " << i << " - Spe : " << listeCoeffUtilitaire[i].first.getSpecificite() << " - Coeff : " << listeCoeffUtilitaire[i].second << endl;
	}
}
