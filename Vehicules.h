#if !defined(_VEHICULES_H)
#define _VEHICULES_H
#include <unordered_map>
#include "Auto.h"
#include "Moto.h"

class Vehicules {
private:
    unordered_map<string, Auto>* hashvehicules;
    unordered_map<string, Moto>* hashvehicules2;

    friend class Flotte;

public:
    Vehicules();
    void EnregistrerVehicule(Auto titine);//Enregistre un nouveau véhicule de type Auto dans la table de has et dans le fichier véhicules.txt
    void EnregistrerVehicule(Moto petrolette);//surcharge de fonction pour une moto ;-)
    void PrintVehicules();//Permet d'afficher tous les véhicules
    void PrintTypesMoto();//Permet d'afficher tous les nom de modeles de Motos
    void PrintTypesAuto();//Permet d'afficher tous les noms de modèles d'Auto
    void SupprimerVehicule();//Permet de supprimer un véhicule de la table de Hash et du fichier vehicules.txt
    int getprix(string modele);//Permet d'obtenir le prix en fonction d'un modele de véhicule
    int CheckAuto(string modele);//Permet de vérifier si une auto est présente dans la table de has
    int CheckMoto(string modele);//Pareil pour une moto

};

#endif  //_VEHICULES_H
