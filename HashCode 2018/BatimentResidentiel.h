#include <vector>

#include "Batiment.h"

using namespace std;

class BatimentResidentiel : Batiment {

private:
	int capacite;

public:
	BatimentResidentiel(const int hauteur, const int largeur, pair<int, int> coord, const int capacite);		//Constructeur par d�faut
	BatimentResidentiel(const BatimentResidentiel &);		//Constructeur de recopie
	~BatimentResidentiel();									//Destructeur par d�faut
};