#pragma once
#include <vector>

using namespace std;

class Batiment
{
	private:
	  int											specificite;															//Capacité Residentielle ou Type Utilitaire
	  int											hauteur;																	//Hauteur du Batiment dans le fichier d'entrée
	  int											largeur;																	//Largeur du Batiment dans le fichier d'entrée
	  int											ligne;																		//Position du Batiment dans le fichier d'entrée
	  vector<pair<int, int>>	briques;																	//Vecteur constitué uniquement des briques (un # dans le fichier) du batiment

	public:
	  Batiment();																												//Constructeur par défaut
	  Batiment(const int spe, const int haut, const int larg);					//Constructeur
	  Batiment(const Batiment &);																				//Constructeur de recopie
	  ~Batiment();																											//Destructeur par défaut

	  Batiment operator=(const Batiment &b);														//Operateur d'affectation
	  bool operator==(Batiment const& b);																//Operateur de comparaison

	  virtual void						ajouterBrique(pair<int, int>);						//Ajoute un # du fichier de lecture

	  virtual void						toString();																//Affichage du batiment

		int											getSpecificite() const;
	  int											getHauteur();															//Getter de Hauteur
	  int											getLargeur();															//Getter de largeur
	  int											getLigne();																//Getter de ligne
	  vector<pair<int, int>>	getBriques();															//Getter de briques

	  void										setLigne(int li);													//Setter de ligne
};
