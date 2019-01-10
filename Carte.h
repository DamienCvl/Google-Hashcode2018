#pragma once
#include "Batiment.h"
#include "BatimentPlace.h"

#include <vector>

using namespace std;

class Carte																						//Un objet "Carte" est un objet possèdant une matrice (vecteur de vecteurs) permettant sa représentation
																								//grâce aux batiments (nombres de l'objet "Batiment") qui les constituent, une liste d'objet "Batiment"
																								//rescencant chaque batiment qui peut être placé sur celle-ci ainsi qu'une liste d'objet "BatimentPlace"
																								//rescencant chaque batiment qui a été placé sur celle-ci.
{
  private:
	vector<vector<int>>				schema;
	vector<Batiment>				listeBatiments;												//Liste d'objets "Batiments" plaçables sur la carte (provenant de la lecture du fichier en question)
	vector<BatimentPlace>			listeBatimentsPlaces;										//Liste d'objets "BatimentPlace" placés sur la carte (provenant de la liste ci-dessus)
	vector<pair<Batiment,float>>	listeCoeffResidentiel;										//Liste des coefficients de chaque batiment pour mesurer leur utilité
	vector<pair<Batiment, float>>	listeCoeffUtilitaire;										//Liste des coefficients de chaque batiment pour mesurer leur utilité

	int cote;

  public:
	Carte();																					//Constructeur par défaut
	Carte(int cote);																			//Constructeur
	Carte(const Carte &);																		//Constructeur de recopie
	~Carte();																					//Destructeur par défaut
	
	void toString();																			//Affichage de la Carte

	vector<Batiment>				getListeBatiments();
	void							setListeBatiments(vector<Batiment> lBatiments);				

	vector<BatimentPlace>			getListeBatimentsPlaces();

	void							ajouterBatimentPlace(BatimentPlace bp);						//Permet d'ajouter un objet "BatimentPlace" à la listeBatimentsPlaces

	void							placerBatiment(Batiment b, pair<int, int> coord);			//Permet de placer un objet "Batiment" à une certaine coordonnée sur la carte.
																								//Ajoute automatique un objet "BatimentPlace" à la listeBatimentsPlaces en fonction
																								//en fonction de l'objet "Batiment" passé en argument.
	
	void							calculCoeff(vector<Batiment> a);												//Calcul le score que pourrait rapporter chaque batiment. 

	void							afficherBatCoeff();
	void							triBatimentUti();
};