#if !defined(_LOCATIONS_H)
#define _LOCATIONS_H
#include <unordered_map>
#include <string>
#include "Locations.h"
#include "Location.h"

using namespace std;


class Locations {
private:
    unordered_map<int, Location>* hashlocations;//Numero de location, id de l'eprunteur, immatriculation, Objet de type location

public:
    Locations();
    inline int GiveNumero(){return hashlocations->size()+1;}//la taille de la Table de Hashage +1 correspond au nouveau numero de location
    void EnregistrerLocation(Location newloc);//Permet d'enregistrer une location dans la table de hashage correspondante et dans le fichier
    void PrintLocations();//Permet d'afficher toutes les locations en cours (F7)
    bool FindEmprunteursByLoc(int id);//Determine si un utilisateur a une location en cours
    Location GetLocation(int numero);//Retourne la location en fonction de son numéro
    void FindEmprunteursByModele(Emprunteurs *Hash1, Flotte *Hash3);//Permet de trouver tous les utilisateurs qui empruntent un modèle de véhicule particulier
    void ModifLocation(int numero, Location loc);//Permet de modifier une location
    void Statistiques(Flotte *Hash3);//Affiche les statistiques des véhicules les plus empruntés.
};

#endif  //_LOCATIONS_H
