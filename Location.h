#if !defined(_LOCATION_H)
#define _LOCATION_H
#include <string>
#include "Date.h"
#include "Emprunteurs.h"
#include "Flotte.h"

using namespace std;

class Location {
private:
    int numero, id, jauge=4, montantreparations=0;
    string immatriculation;
	Date debut;
	Date fin;
    Date fineffective;
    bool assurance=false;
    friend class Locations;
public:
    void NouvelleLocation(int num, Emprunteurs *Hash1, Flotte *Hash3);//création d'une nouvelle location
    void PrintDevisFacture(Emprunteurs *Hash1, Vehicules *Hash2, Flotte *Hash3);//Aficher le devis ou facture en fonction d'un ID
    void RetourLocation(Flotte *Hash3);//Gère le retour de location
};

#endif  //_LOCATION_H
