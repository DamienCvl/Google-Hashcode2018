#include <iostream>

#include "Batiment.h"
#include "BatimentResidentiel.h"
#include "BatimentUtilitaire.h"
#include "Carte.h"

#include <utility>

using namespace std;

Carte carte;
//Liste des Batiments
vector<Batiment> listeBatiments;
//BatimentResidentiel * tableauBatiments;
//BatimentUtilitaire * tableauBatiments;

int main() {

	Carte carte(10);
	carte.toString();

	cout << endl;

	Batiment b1(3, 3, pair<int, int>(0, 1));
	b1.ajouterBrique(pair<int, int>(0, 0));
	b1.ajouterBrique(pair<int, int>(1, 0));
	b1.ajouterBrique(pair<int, int>(1, 1));
	b1.ajouterBrique(pair<int, int>(1, 2));
	b1.ajouterBrique(pair<int, int>(2, 2));
	b1.toString();

	b1.setCoordonees(pair<int, int>(0, 0));
	listeBatiments.push_back(b1);
	//Creer la fonction permettant d'ajouter un batiment à la liste de batiment
	//tableauBatiments.insert(b1);

	//Creer la fonction permettant de placer nos batiments dans la liste de batiments sur la carte
}