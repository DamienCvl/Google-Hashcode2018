#pragma once
#include <iostream>

#include "Batiment.hpp"

using namespace std;

Batiment::Batiment()
{
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
	briques = b.briques;
	specificite = b.specificite;
	hauteur = b.hauteur;
	largeur = b.largeur;
	briques = b.briques;
}

Batiment Batiment::operator=(const Batiment &b)
{
	return Batiment(b);
}

Batiment::~Batiment()
{
}

void Batiment::ajouterBrique(pair<int, int> br)
{
	auto it = briques.end();
	briques.insert(it, br);
}

void Batiment::toString()
{
	cout << "\\Affichage du Batiment : \n";

	vector<int> donnees(largeur, 0);
	vector<vector<int>> matrice(hauteur, donnees); //Creation de la matrice

	for (int i = 0; i <= briques.size() - 1; i++) //Ajout des briques
	{
		matrice[briques[i].first][briques[i].second] = 1;
	}

	for (int i = 0; i <= hauteur - 1; i++) //Affichage de la matrice
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

vector<pair<int, int>> Batiment::GetBriques() const
{
	return briques;
}

BatimentPlace ::BatimentPlace(const Batiment *bat, int x, int y)
{
	refBatiment = bat;
	coordonnees = pair<int, int>(x, y);
}

pair<int, int> BatimentPlace ::getCoordonnees()
{
	return coordonnees;
}