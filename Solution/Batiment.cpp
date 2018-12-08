#include <iostream>

#include "Batiment.h"

using namespace std;

Batiment::Batiment()
{
	this->hauteur = 0;
	this->largeur = 0;
}

Batiment::Batiment(const int h, const int l, pair<int, int> c)
{
	this->specificite = 1;
	this->hauteur = h;
	this->largeur = l;
	this->coordonees = c;
	this->briques = vector<pair<int, int>>(0);
}

Batiment::Batiment(const Batiment & b)
{
	this->briques = b.briques;
	this->specificite = b.specificite;
	this->hauteur = b.hauteur;
	this->largeur = b.largeur;
	this->coordonees = b.coordonees;

}

Batiment::~Batiment()
{

}

void Batiment::ajouterBrique(pair<int, int> br)
{
	auto it = this->briques.end();
	it = this->briques.insert(it, br);
}

void Batiment::setCoordonees(pair<int, int> c)
{
	this->coordonees = c;
}

void Batiment::toString()
{
	cout << "\\Affichage du Batiment : \n";

	vector<int> donnees(this->largeur, 0);
	vector<vector<int>> matrice(this->hauteur, donnees);	//Creation de la matrice

	for (int i = 0; i <= this->briques.size() - 1; i++)	//Ajout des briques
	{
		matrice[this->briques[i].first][this->briques[i].second] = 1;
	}
	
	for (int i = 0; i <= this->hauteur - 1; i++)		//Affichage de la matrice
	{
		for (int j = 0; j <= largeur - 1; j++) {
			cout << matrice[i][j] << " ";
		}
		cout << endl;
	}
}

int Batiment::getLargeur()
{
	return this->hauteur;
}

int Batiment::getHauteur()
{
	return this->largeur;
}

pair<int, int> Batiment::getCoordonees()
{
	return this->coordonees;
}

int Batiment::getSpecificite()
{
	return this->specificite;
}

vector<pair<int, int>> Batiment::GetBriques()
{
	return this->briques;
}
