#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>

#include "Carte.h"

using namespace std;

Carte::Carte()
{

}

Carte::Carte(int h, int l, int wD)
{
	this->hauteur = h;
	this->largeur = l;
	this->walkDis = wD;

	vector<int> donnees(l, 0);					//Creation de la matrice
	vector<vector<int>> matrice(h, donnees);

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

	for (int i = 0; i <= this->hauteur - 1; i++)		//Affichage de la matrice
	{
		for (int j = 0; j <= largeur - 1; j++) {
			cout << schema[i][j] << " ";
		}
		cout << endl;
	}
}

void Carte::toFile(string chemin_sortie)
{
	string chemin = chemin_sortie + ".visu";
	ofstream fichier(chemin, ios::out | ios::trunc);

	if (fichier)
	{
		for (int i = 0; i <= this->hauteur - 1; i++)		//Affichage de la matrice
		{
			for (int j = 0; j <= largeur - 1; j++) {
				if (schema[i][j] == 0) {
					fichier << "[" << 666 << "]";
				}
				else
				{
					fichier << "[" << schema[i][j] << "]";
				}
			}
			fichier << endl;
		}

		fichier.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

void Carte::toOut(string chemin_sortie)
{
	string chemin = chemin_sortie + ".out";
	ofstream fichier(chemin, ios::out | ios::trunc);

	if (fichier)
	{
		fichier << listeBatimentsPlaces.size() << endl;
		for (unsigned int i = 0; i < listeBatimentsPlaces.size(); i++)
		{
			fichier << listeBatimentsPlaces[i].getBatiment().getLigne() - 1
				<< " " << listeBatimentsPlaces[i].getCoordonnees().first
				<< " " << listeBatimentsPlaces[i].getCoordonnees().second << endl;
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
	this->ajouterLignes();
}

void Carte::ajouterLignes()
{
	for (unsigned int i = 0; i < listeBatiments.size(); i++)
	{
		listeBatiments[i].setLigne(i + 1);
	}
}

vector<BatimentPlace> Carte::getListeBatimentsPlaces()
{
	return this->listeBatimentsPlaces;
}

void Carte::ajouterBatimentPlace(BatimentPlace bp)
{
	this->listeBatimentsPlaces.push_back(bp);
}

bool Carte::placerBatiment(Batiment b, pair<int, int> c)
{
	bool condition = true;
	if (c.first < 0 || c.second < 0 || c.first > 999 || c.second > 999)
	{
		cout << "Hors Carte" << endl;
		return false;
	}
	else {
		BatimentPlace bp(b, c);

		int x, y;
		vector<pair<int, int>> briques = bp.getBatiment().getBriques();

		for (unsigned int i = 0; i < briques.size(); i++)
		{
			x = briques[i].first + c.first;
			y = briques[i].second + c.second;

			if (this->schema[x][y] != 0) {
				condition = false;
			}
		}

		if (condition == true) {
			for (unsigned int i = 0; i < briques.size(); i++)
			{
				x = briques[i].first + c.first;
				y = briques[i].second + c.second;

				if (bp.getBatiment().getSpecificite() < 0) {
					if (bp.getBatiment().getSpecificite() > -10)
					{
						this->schema[x][y] = bp.getBatiment().getSpecificite() * 10;
					}
					else
					{
						this->schema[x][y] = bp.getBatiment().getSpecificite();
					}
				}
				else {
					if (bp.getBatiment().getSpecificite() < 10)
					{
						this->schema[x][y] = bp.getBatiment().getSpecificite() * 100;
					}
					else
					{
						this->schema[x][y] = bp.getBatiment().getSpecificite() * 10;
					}
				}
			}
			this->ajouterBatimentPlace(bp);
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Carte::placerResidentiel()
{
	Batiment bestBat = listeCoeffResidentiel[0].first;

	int decLarg = this->calculLargMax();
	int decHaut = this->calculHautMax();
	int nbr = 0;

	for (int x = 0; x < hauteur - bestBat.getHauteur(); x = x + walkDis + bestBat.getHauteur())
	{
		for (int y = 0; y < (largeur - bestBat.getLargeur()); y = y  + walkDis + bestBat.getLargeur()) {
			this->placerBatiment(bestBat, pair<int, int>(x, y));
			nbr++;
		}
	}

	for (int x = decHaut - 1; x < hauteur - decHaut; x = x + walkDis + bestBat.getHauteur())
	{
		for (int y = decLarg - 1; y < largeur - decLarg; y = y + walkDis + bestBat.getLargeur()) {
			this->placerBatiment(bestBat, pair<int, int>(x, y));
			nbr++;
		}
	}
	cout << "Nombre de batiments residentiels places : " << nbr << endl;
	return true;
}


void Carte::calculCoeff(vector<Batiment> listeBatiments)
{
	for (unsigned int i = 0; i < listeBatiments.size(); i++)
	{
		float sizeBatiment = listeBatiments[i].getBriques().size();
		float hauteur = listeBatiments[i].getHauteur();
		float largeur = listeBatiments[i].getLargeur();

		if (listeBatiments[i].getSpecificite() < 0)
		{
			float spe = -listeBatiments[i].getSpecificite();
			float coeff = sizeBatiment / (hauteur * largeur)*spe;
			listeCoeffResidentiel.push_back(pair<Batiment, float>(listeBatiments[i], coeff));
		}
		else {
			float coeff = sizeBatiment / (hauteur * largeur);
			listeUtilitaire.push_back(listeBatiments[i]);
		}
	}

	this->triBatimentRes();
	this->triBatimentUti();
}

void Carte::triBatimentRes()
{
	for (unsigned int i = 0; i < listeCoeffResidentiel.size(); i++)
	{
		for (unsigned int j = i; j < listeCoeffResidentiel.size(); j++)
		{
			if (listeCoeffResidentiel[j].second > listeCoeffResidentiel[i].second)	//Tri des Batiments Résidentiels par ordre décroissant de coefficients
			{
				auto valeurtemporaire = listeCoeffResidentiel[i];
				listeCoeffResidentiel[i] = listeCoeffResidentiel[j];
				listeCoeffResidentiel[j] = valeurtemporaire;
			}
		}
	}
}

int Carte::calculLargMax()
{
	int largMax = 0;

	for (unsigned int i = 0; i < listeBatiments.size(); i++)
	{
		if (listeBatiments[i].getLargeur() > largMax)
		{
			largMax = listeBatiments[i].getLargeur();															//Calcul de la hauteur max des Batiments Résidentiels
		}
	}
	return largMax;
}

int Carte::calculHautMax()
{
	int hautMax = 0;

	for (unsigned int i = 0; i < listeBatiments.size(); i++)
	{
		if (listeBatiments[i].getLargeur() > hautMax)
		{
			hautMax = listeBatiments[i].getLargeur();															//Calcul de la hauteur max des Batiments Utilitaires
		}
	}
	return hautMax;
}

void Carte::afficherBatCoeff()
{
	for (unsigned int i = 0; i < listeCoeffResidentiel.size(); i++) {
		cout << "Batiment : " << i << " - Spe : " << listeCoeffResidentiel[i].first.getSpecificite() << " - Coeff : " << listeCoeffResidentiel[i].second << endl;			//Affichage des coefficients des Batiments Residentiels
	}

	for (unsigned int i = 0; i < listeCoeffUtilitaire.size(); i++) {
		cout << "Batiment : " << i << " - Spe : " << listeCoeffUtilitaire[i].first.getSpecificite() << " - Coeff : " << listeCoeffUtilitaire[i].second << endl;				//Affichage des coefficients des Batiments Utilitaires
	}
}

void Carte::triBatimentUti()
{
	for (unsigned int i = 0; i < listeUtilitaire.size(); i++)
	{
		for (unsigned int j = i; j < listeUtilitaire.size(); j++)
		{
			if (listeUtilitaire[j].getSpecificite() < listeUtilitaire[i].getSpecificite())		//Tri des Batiments Utilitaires par ordre croissant de type
			{
				auto valeurtemporaire = listeUtilitaire[i];
				listeUtilitaire[i] = listeUtilitaire[j];
				listeUtilitaire[j] = valeurtemporaire;

			}
		}
	}

	int specificite = 0;
	vector<Batiment> bat;

	for (unsigned int i = 0; i < listeUtilitaire.size(); i++)
	{
		if (listeUtilitaire[i].getSpecificite() != specificite)
		{
			vector<Batiment> bat;
			specificite++;
			bat.push_back(listeUtilitaire[i]);
			listeBatimentUtilitaireTriee.push_back(bat);
		}
		else
		{
			listeBatimentUtilitaireTriee[specificite - 1].push_back(listeUtilitaire[i]);
		}
	}

	for (vector<Batiment> vb : listeBatimentUtilitaireTriee)
	{
		for (unsigned int i = 0; i < vb.size(); i++)
		{
			for (unsigned int j = i; j < vb.size(); j++)
			{
				if (vb[j].getLargeur() > vb[i].getLargeur())		//Tri des Batiments Utilitaire par ordre croissant de taille
				{
					auto valeurtemporaire = vb[i];
					vb[i] = vb[j];
					vb[j] = valeurtemporaire;
				}
			}
		}
	}
}

void Carte::placerUtilitaire()
{
	unsigned int typeUtilitaire = 0;
	unsigned int ancienTypeUtilitaire = 0;
	unsigned int nbrUtilitairePlace = 0;
	bool is_batimentPlace = false;

	for (int i = 0; i < hauteur; i++) 																																									//Double boucle de parcours de la carte
	{
		vector<int> temp = schema[i];
		for (int j = 0; j < largeur; j++)
		{
			int brique = temp[j];
			pair<int, int> coordBrique;
			coordBrique.first = i;
			coordBrique.second = j;
			is_batimentPlace = false;
			if (brique == 0)
			{
				for (typeUtilitaire = ancienTypeUtilitaire + 1; !(is_batimentPlace); typeUtilitaire++) 												//Ceci est la boucle de parcours des batiments utilitaires. Elle demarre par le prochain type suivant le dernier batiment place
				{
					if (typeUtilitaire == listeBatimentUtilitaireTriee.size()) typeUtilitaire = 0;															//On recommence avec les premiers types une fois arrive au dernier type de la liste de batiment utilitaire.
					for (unsigned int k = 0; k < listeBatimentUtilitaireTriee[typeUtilitaire].size(); k++) 											//Boucle simple de parcours de batiment de type k
					{
						if (coordBrique.first + listeBatimentUtilitaireTriee[typeUtilitaire][k].getHauteur() - 1 < hauteur &&
							coordBrique.second + listeBatimentUtilitaireTriee[typeUtilitaire][k].getLargeur() - 1 < largeur)				//Condition pour ne pas placer de batiment qui deborde de la carte
						{
							if (placerBatiment(listeBatimentUtilitaireTriee[typeUtilitaire][k], coordBrique)) {											//On essaye de placer le batiment
								is_batimentPlace = true;
								ancienTypeUtilitaire = typeUtilitaire;
								nbrUtilitairePlace++;
								break;																																																//Sortie de la boucle simple de parcours de batiment k
							}
						}
					}																																																						//On sort de la boucle liee a tous les batiments utilitaires quand on a place un batiment
					if (ancienTypeUtilitaire == typeUtilitaire) {																																//Ou quand on a fait tout les batiments utilitaires
						break;
					}
				}
			}
		}
	}
	cout << "Nombre de batiments utilitaires places : " << nbrUtilitairePlace << endl;
}
