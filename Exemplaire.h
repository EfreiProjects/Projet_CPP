#if !defined(_EXEMPLAIRE_H)
#define _EXEMPLAIRE_H
#include <string>

using namespace std;

class Exemplaire {//Défini un objet de type exemplaire
private:
	string modele;
    string immatriculation;
	string couleur;
	string accident;
    int kilometres;
    friend class Flotte;
public:
    void NouvelExemplaire(string type);//Méthode pour la crétion d'un nouvel exemplaire
};

#endif  //_EXEMPLAIRE_H
