#pragma once
#include "Batimen.hpp"
#include <vector>

using namespace std;

class Carte
{

  private:
	vector<vector<int>> schema;
	int cote;

  public:
	Carte();			  //Constructeur par d�faut
	Carte(int cote);	  //Constructeur
	Carte(const Carte &); //Constructeur de recopie
	~Carte();			  //Destructeur par d�faut

	void toString(); //Affichage de la Carte
	void ajouterBatiment(vector<Batiment> v);
};