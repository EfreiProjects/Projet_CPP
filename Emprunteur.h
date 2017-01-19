#if !defined(_EMPRUNTEUR_H)
#define _EMPRUNTEUR_H
#include <string>
#include <Adresse.h>

using namespace std;

class Emprunteur {//Classe qui définit l'élément emprunteur
private:
	int id;
	string nom;
	string prenom;
    Adresse adresse;
    friend class Emprunteurs;//La classe conteneur emprunteur est déclarée en amie
public:
    Emprunteur();
    int NouvelEmprunteur(int hashsize);//création d'un nouvel emprunteur
};

#endif  //_EMPRUNTEUR_H
