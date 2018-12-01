#include <iostream>

#include "Batiment.h"

using namespace std;

Batiment::Batiment(const int & h, const int & l, int * c)
{
	this->hauteur = h;
	this->largeur = l;
	this->coordonees = c;

	vector<bool> donnees(l, 0);
	vector<vector<bool>> s(h, donnees);

	this->schema = s;
}

Batiment::Batiment(const Batiment & b)
{
	this->schema = b.schema;
}

Batiment::~Batiment()
{
}

void Batiment::ajouterBrique(const int & posH, const int & posL, const bool & b)
{

}

void Batiment::toString()
{
		cout << "\n Printing Matrix : \n";
		for (int i = 0; i <= this->hauteur - 1; i++)
		{
			for (int j = 0; j <= largeur - 1; j++)
				cout << schema[i][j] << " ";
			cout << endl;
		}
		cout << endl;
}
