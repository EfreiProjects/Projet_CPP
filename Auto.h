#if !defined(_AUTO_H)
#define _AUTO_H
#include <string>
#include "Vehicule.h"

class Auto : public Vehicule {//Classe destinée au type de véhicule Auto.
protected:
	int places;
    string luxe;
    string boite;
	string carburant;
    friend class Vehicules;//Les deux classes conteneurs Véhicules et Flotte sont déclarées amies pour pouvoir accèder plus facilement aux données
    friend class Flotte;
public:
    Auto();
    void SetAuto();//Méthode pour créer un véhicule de type Auto
};

#endif  //_AUTO_H
