#pragma once
#include <iostream>
#include <fstream>

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

void Carte::toFile()
{
	ofstream fichier("../VisuMaps/visu_b.in", ios::out | ios::trunc);  // ouverture en �criture avec effacement du fichier ouvert

	if (fichier)
	{
		for (int i = 0; i <= this->cote - 1; i++)		//Affichage de la matrice
		{
			for (int j = 0; j <= cote - 1; j++) {
				fichier << schema[i][j] << " ";
			}
			fichier << endl;
		}

		fichier.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
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

bool Carte::placerBatiment(Batiment b, pair<int, int> c)
{
	bool condition = true;
	if (c.first < 0 || c.second < 0) {
		cout << "hors carte" << endl;
	}
	else {
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
	return condition;
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
			listeUtilitaire.push_back(listeBatiments[i]);
		}
	}
}

void Carte::afficherBatCoeff() {
	for (int i = 0; i < listeBatimentUtilitaireTriee.size(); i++) {
		for (int j = 0; j < listeBatimentUtilitaireTriee[i].size(); j++) {
			cout << "Batiment de groupe : " <<i << " - Spe : " << listeBatimentUtilitaireTriee[i][j].getSpecificite() << "Largeur : "<< listeBatimentUtilitaireTriee[i][j].getLargeur() << endl;
		}
	}
	/*for (int i = 0; i < listeBatimentUtilitaireTriee.size(); i++) {
		for (int j = 0; j < listeBatimentUtilitaireTriee[i].size(); j++) {
			cout << "Batiment de groupe : " << i << " - Spe : " << listeBatimentUtilitaireTriee[i][j].getSpecificite()<< endl;
		}
	}*/
}

void Carte::triBatimentUti() {
	for (int i = 0; i < listeUtilitaire.size(); i++)
	{
		for (int j = i; j < listeUtilitaire.size(); j++)
		{
			if (listeUtilitaire[j].getSpecificite() < listeUtilitaire[i].getSpecificite()) {
				auto valeurtemporaire = listeUtilitaire[i];
				listeUtilitaire[i] = listeUtilitaire[j];
				listeUtilitaire[j] = valeurtemporaire;
		
			}	
		}
	}

	int specificite = 0;
	vector<Batiment> bat;
	listeBatimentUtilitaireTriee.push_back(bat);

	for (int i = 0; i < listeUtilitaire.size(); i++) {
		if (listeUtilitaire[i].getSpecificite()-1 != specificite) {
			vector<Batiment> bat;
			listeBatimentUtilitaireTriee.push_back(bat);
			specificite += 1;
			bat.push_back(listeUtilitaire[i]);
		}
		else {
			listeBatimentUtilitaireTriee[specificite].push_back(listeUtilitaire[i]);
		}
	}

	for (int i = 0; i < listeBatimentUtilitaireTriee.size(); i++)
	{
		for (int j =0; j < listeBatimentUtilitaireTriee[i].size()-1; j++)
		{
			if (listeBatimentUtilitaireTriee[i][j].getLargeur() < listeBatimentUtilitaireTriee[i][j+1].getLargeur()) {
				auto valeurtemporaire = listeBatimentUtilitaireTriee[i][j];
				listeBatimentUtilitaireTriee[i][j+1] = listeBatimentUtilitaireTriee[i][j];
				listeBatimentUtilitaireTriee[i][j] = valeurtemporaire;
			}
		}
	}
}



bool Carte::placerBatimentOpti(pair<int, int> pointA, pair<int, int> pointB)
{
	Batiment bestBat = listeCoeffResidentiel[0].first;

	if (placerBatiment(bestBat, pair<int, int>(pointB.first / 2 - bestBat.getLargeur() / 2, pointB.second / 2 - bestBat.getHauteur() / 2)))
	{
		placerBatimentOpti(pair<int, int>(pointA.first, pointA.second), pair<int, int>(pointB.first / 2, pointB.second / 2));        //0,0
		placerBatimentOpti(pair<int, int>(pointB.first / 2, pointA.second), pair<int, int>(pointB.first, pointB.second / 2));       //0,1
		placerBatimentOpti(pair<int, int>(pointA.first, pointB.second / 2), pair<int, int>(pointB.first / 2, pointB.second));       //1,0
		placerBatimentOpti(pair<int, int>(pointB.first / 2, pointB.second / 2), pair<int, int>(pointB.first, pointB.second));       //1,1
		return true;
	}
	else
	{
		return false;
	}
}