#pragma once
#include <iostream>

#include "Batiment.h"

using namespace std;

Batiment::Batiment()
{
	specificite = 0;
	hauteur = 0;
	largeur = 0;

	briques = vector<pair<int, int>>(0);
}

Batiment::Batiment(const int spe, const int h, const int l)
{
	specificite = spe;
	hauteur = h;
	largeur = l;

	briques = vector<pair<int, int>>(0);
}

Batiment::Batiment(const Batiment &b)
{
	specificite = b.specificite;
	hauteur = b.hauteur;
	largeur = b.largeur;

	briques = b.briques;
}

Batiment Batiment::operator=(const Batiment &b)
{
	this->specificite = b.specificite;
	this->hauteur = b.hauteur;
	this->largeur = b.largeur;

	this->briques = b.briques;
	return *this;
}

Batiment::~Batiment()
{
}

void Batiment::ajouterBrique(pair<int, int> br)
{
	if (br.first < 0 || br.second < 0) {
		cout << "brique hors de la carte" << endl;
	}
	else {
		auto it = briques.end();												//Placement d'un itérateur au bout de notre vecteur de briques
		briques.insert(it, br);													//Ajout d'une nouvelle brique au vecteur
	}
}

void Batiment::toString()
{
	cout << "\nAffichage du Batiment : \n";

	vector<int> donnees(largeur, 0);
	vector<vector<int>> matrice(hauteur, donnees);							//Creation de la matrice

	for (int i = 0; i <= briques.size() - 1; i++)							//Ajout des briques (un 1 dans la matrice = un # sur le fichier)
	{
		matrice[briques[i].first][briques[i].second] = 1;
	}

	for (int i = 0; i <= hauteur - 1; i++)									//Affichage de la matrice
	{
		for (int j = 0; j <= largeur - 1; j++)
		{
			cout << matrice[i][j] << " ";
		}
		cout << endl;
	}
}

int Batiment::getLargeur()
{
	return largeur;
}

int Batiment::getHauteur()
{
	return hauteur;
}

int Batiment::getSpecificite() const
{
	return specificite;
}

vector<pair<int, int>> Batiment::getBriques() const
{
	return briques;
}