#pragma once
#include <vector>
using namespace std;

class Batiment
{

  /*
Avec l'implementation courante les données des batiments sont multiplier
par le nombre de batiment placée alors qu'il est possible de faire 
référence à un batiment Général et alors éviter de stocker x fois 
briques, hauteur, largeur, specificité

Peut être faire 2 classes différentes pour un batiment placé et 
le type général d'un batiment

Réglé avec l'ajout de batimentPlace

*/
private:
  vector<pair<int, int>> briques;
  int hauteur;
  int largeur;
  int specificite; //  capacite ou type de batimnent utilitaire

public:
  Batiment();                                    //Constructeur par d�faut
  Batiment(const int spe, const int, const int); //Constructeur
  Batiment(const Batiment &);                    //Constructeur de recopie
  Batiment operator=(const Batiment &b);
  ~Batiment(); //Destructeur par d�faut

  virtual void ajouterBrique(pair<int, int>); //Ajoute un # du fichier de lecture
  virtual void toString();                    //Affichage du batiment
  int getLargeur();
  int getHauteur();
  int getSpecificite() const;
  vector<pair<int, int>> GetBriques() const;
};

class BatimentPlace
{

private:
  pair<int, int> coordonnees;
  const Batiment *refBatiment;

public:
  BatimentPlace(const Batiment *bat, int x, int y);
  pair<int, int> getCoordonnees();
  vector<pair<int, int>> GetBriques() { return refBatiment->GetBriques(); };
  int getSpecificite() { return refBatiment->getSpecificite(); };
};