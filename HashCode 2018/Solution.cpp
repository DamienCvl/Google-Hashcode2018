#include "Batiment.h"
#include "BatimentResidentiel.h"
#include "BatimentUtilitaire.h"

#include <utility>

using namespace std;

//Liste des Batiments
Batiment * tableauBatiments;
//BatimentResidentiel * tableauBatiments;
//BatimentUtilitaire * tableauBatiments;

int main() {
	Batiment b(3, 3, pair<int, int>(0, 1));
	b.ajouterBrique(pair<int, int>(0, 0));
	b.ajouterBrique(pair<int, int>(1, 0));
	b.ajouterBrique(pair<int, int>(1, 1));
	b.ajouterBrique(pair<int, int>(1, 2));
	b.ajouterBrique(pair<int, int>(2, 2));
	b.toString();
}
