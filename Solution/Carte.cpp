#include <iostream>
#include "Batiment.h"
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

void Carte::ajouterBatiment(vector<Batiment> v)
{
	Batiment b;
	pair<int, int> c;
	int x, y;
	for (int i = 0; i < v.size(); i++) {
		b = v[i];
		c = b.getCoordonees();
		cout << "Coor" << c.first << "   " << c.second << endl;
		vector<pair<int, int>> briques = b.GetBriques();
		for (int j = 0; j < briques.size(); j++) {
			x = briques[j].first + c.first;
			y = briques[j].second + c.second;
			
			this->schema[x][y] = b.getSpecificite();

		}
	}
}
