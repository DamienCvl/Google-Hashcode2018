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
	ofstream fichier("../VisuMaps/visu_b.in", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

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

void Carte::placerBatiment(Batiment b, pair<int, int> c)
{
	BatimentPlace bp(&b, c);

	int x, y;

	cout << "Coordonees : (" << c.first << ";" << c.second << ")" << endl;
	cout << "Specificité : (" << bp.getBatiment().getSpecificite() << ")" << endl;
	vector<pair<int, int>> briques = bp.getBatiment().getBriques();

	for (int i = 0; i < briques.size(); i++)
	{
		x = briques[i].first + c.first;
		y = briques[i].second + c.second;

		this->schema[x][y] = bp.getBatiment().getSpecificite();
	}

	this->ajouterBatimentPlace(bp);
}
