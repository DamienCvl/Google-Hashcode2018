#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>

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
	ofstream fichier("../Maps/b_short_walk_visu.in", ios::out | ios::trunc);

	if (fichier)
	{
		for (int i = 0; i <= this->cote - 1; i++)		//Affichage de la matrice
		{
			for (int j = 0; j <= cote - 1; j++) {
				if (schema[i][j] == 0) {
					fichier << "[" << 666 << "]";
				}
				else
				{
					fichier << "[" << schema[i][j] << "]";
				}
			}
			fichier << endl;
		}

		fichier.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

void Carte::toOut()
{
	ofstream fichier("../Maps/b_short_walk.out", ios::out | ios::trunc);

	if (fichier)
	{
		fichier << listeBatimentsPlaces.size() << endl;
		for (int i = 0; i < listeBatimentsPlaces.size() - 1; i++)
		{
			fichier << listeBatimentsPlaces[i].getBatiment().getLigne() 
					<< " " << listeBatimentsPlaces[i].getCoordonnees().first 
					<< " " << listeBatimentsPlaces[i].getCoordonnees().second << endl;
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
	this->ajouterLignes();
}

void Carte::ajouterLignes()
{
	for (int i = 0; i < listeBatiments.size(); i++)
	{
		listeBatiments[i].setLigne(i + 1);
	}
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
	if (c.first < 0 || c.second < 0 || c.first > 999 || c.second > 999) {
		cout << "Hors Carte" << endl;
		return false;
	}
	else {
		BatimentPlace bp(b, c);

		int x, y;

		//cout << "Coordonnees : (" << c.first << ";" << c.second << ")" << endl;
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

				if (bp.getBatiment().getSpecificite() < 0) {
					if (bp.getBatiment().getSpecificite() > -10)
					{
						this->schema[x][y] = bp.getBatiment().getSpecificite() * 10;
					}
					else
					{
						this->schema[x][y] = bp.getBatiment().getSpecificite();
					}
				}
				else {
					if (bp.getBatiment().getSpecificite() < 10)
					{
						this->schema[x][y] = bp.getBatiment().getSpecificite() * 100;
					}
					else
					{
						this->schema[x][y] = bp.getBatiment().getSpecificite() * 10;
					}
				}
			}
			this->ajouterBatimentPlace(bp);
			return true;
		}
		else {
			//cout << "Place Occupee" << endl;
			return false;
		}
	}
}

bool Carte::placerBatimentOpti()
{
	Batiment bestBat = listeCoeffResidentiel[0].first;

	int decLarg = this->calculLargMax();
	int decHaut = this->calculHautMax();

	cout << "LargMax : " << decLarg << " - HautMax : " << decHaut << endl;

	for (int x = 0; x < cote - bestBat.getLargeur(); x = x + decLarg + bestBat.getLargeur())		//Affichage de la matrice
	{
		for (int y = 0; y < (cote - bestBat.getHauteur()); y = y + decHaut + bestBat.getHauteur()) {
			this->placerBatiment(bestBat, pair<int, int>(x, y));
		}
	}

	for (int x = decLarg - 1; x < cote - decLarg; x = x + decLarg + bestBat.getLargeur())		//Affichage de la matrice
	{
		for (int y = decHaut - 1; y < cote - decHaut; y = y + decHaut + bestBat.getHauteur()) {
			this->placerBatiment(bestBat, pair<int, int>(x, y));
		}
	}

	return true;
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
			float coeff = sizeBatiment / (hauteur * largeur)*spe;
			listeCoeffResidentiel.push_back(pair<Batiment, float>(listeBatiments[i], coeff));
		}
		else {
			float coeff = sizeBatiment / (hauteur * largeur);
			listeUtilitaire.push_back(listeBatiments[i]);
		}
	}

	this->triBatimentRes();
	this->triBatimentUti();
}

//Tiphaine
void Carte::triBatimentRes() {
	for (int i = 0; i < listeCoeffResidentiel.size(); i++)
	{
		for (int j = i; j < listeCoeffResidentiel.size(); j++)
		{
			if (listeCoeffResidentiel[j].second > listeCoeffResidentiel[i].second)
			{
				auto valeurtemporaire = listeCoeffResidentiel[i];
				listeCoeffResidentiel[i] = listeCoeffResidentiel[j];
				listeCoeffResidentiel[j] = valeurtemporaire;
			}
		}
	}
}

int Carte::calculLargMax()
{
	int largMax = 0;

	for (int i = 0; i < listeBatiments.size(); i++)
	{
		if (listeBatiments[i].getLargeur() > largMax)
		{
			largMax = listeBatiments[i].getLargeur();
		}
	}
	return largMax;
}

int Carte::calculHautMax()
{
	int hautMax = 0;

	for (int i = 0; i < listeBatiments.size(); i++)
	{
		if (listeBatiments[i].getLargeur() > hautMax)
		{
			hautMax = listeBatiments[i].getLargeur();
		}
	}
	return hautMax;
}

//Tiphaine
void Carte::afficherBatCoeff() {

	for (int i = 0; i < listeCoeffResidentiel.size(); i++) {
		cout << "Batiment : " << i << " - Spe : " << listeCoeffResidentiel[i].first.getSpecificite() << " - Coeff : " << listeCoeffResidentiel[i].second << endl;
	}

	for (int i = 0; i < listeCoeffUtilitaire.size(); i++) {
		cout << "Batiment : " << i << " - Spe : " << listeCoeffUtilitaire[i].first.getSpecificite() << " - Coeff : " << listeCoeffUtilitaire[i].second << endl;
	}
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
		if (listeUtilitaire[i].getSpecificite() - 1 != specificite) {
			vector<Batiment> bat;
			listeBatimentUtilitaireTriee.push_back(bat);
			specificite += 1;
			bat.push_back(listeUtilitaire[i]);
		}
		else {
			listeBatimentUtilitaireTriee[specificite].push_back(listeUtilitaire[i]);
		}
	}

	for (vector<Batiment> vb : listeBatimentUtilitaireTriee)
	{
		for (int i = 0; i < vb.size(); i++)
		{
			for (int j = i; j < vb.size(); j++)
			{
				if (vb[j].getLargeur() > vb[i].getLargeur()) {
					auto valeurtemporaire = vb[i];
					vb[i] = vb[j];
					vb[j] = valeurtemporaire;
				}
			}
		}
	}
}

void Carte::placerUtilitaire() {

	int decLarg = this->calculLargMax();
	int decHaut = this->calculHautMax();

	unsigned int typeUtilitaire = 0;
	unsigned int ancienTypeUtilitaire = 0;
	unsigned int nbrUtilitairePlace = 0;
	bool is_batimentPlace = false;

	for (unsigned int i = 0; i < cote; i++) {

		vector<int> temp = schema[i];
		cout << "Etude de la ligne : " << i << endl;
		for (unsigned int j = 0; j < cote; j++) {
			int brique = temp[j];
			pair<int, int> coordBrique;
			coordBrique.first = i;
			coordBrique.second = j;
			is_batimentPlace = false;
			if (brique == 0) {
				for (typeUtilitaire = ancienTypeUtilitaire + 1; !(is_batimentPlace); typeUtilitaire++) {
					if (typeUtilitaire == listeBatimentUtilitaireTriee.size()) typeUtilitaire = 0;
					for (unsigned int k = 0; k < listeBatimentUtilitaireTriee[typeUtilitaire].size(); k++) {
						if (coordBrique.first < cote - decLarg && coordBrique.second < cote - decHaut)
						{
							if (placerBatiment(listeBatimentUtilitaireTriee[typeUtilitaire][k], coordBrique)) {
								is_batimentPlace = true;
								ancienTypeUtilitaire = typeUtilitaire;
								nbrUtilitairePlace++;
								//cout << "Batiment utilitaire de type " << typeUtilitaire + 1 << " place à la coord : " << coordBrique.first << ":" << coordBrique.second << endl;
								break;
							}
						}
					}
					if (ancienTypeUtilitaire == typeUtilitaire) {
						break;
					}
				}
				//if (!is_batimentPlace) {
					//cout << "Aucun batiment utilitaire ne peut etre place en : " << coordBrique.first << ':' << coordBrique.second << endl;
				//}
			}
		}
	}
	cout << "Nombre de batiments utilitaires places : " << nbrUtilitairePlace << endl;
}