#if !defined(_FLOTTE_H)
#define _FLOTTE_H
#include <Exemplaire.h>
#include <unordered_map>
#include <Vehicules.h>


class Flotte {//Classe containeur pour la flotte
private:
    unordered_map<string, Exemplaire>* hashflotte;
public:
    Flotte();
    void EnregistrerExemplaire(Exemplaire newex);//Permet d'enregistrer un nouvel exemplaire dans la table de hash correspondante et dans le fichier
    void PrintFlotte(Vehicules *Hash2);//Afficher toute la flotte
    int CheckExemplaire(string exemplaire);//Verifier si un exemplaire est bien dans la table de hash
    int GetKM(string immat);//Retourne le kilométrage en fonction de l'immatriculation du véhicule
    void AddDommages(string immat, string dommages);//Permet d'ajouter des dommages à un véhicule en particulier
    void FindPrint(string immat, Vehicules *Hash2);//Permet de rechercher et d'afficher un exemplaire particulier
    void SupprimerExemplaire();//Permet de supprimer un exemplaire de la flotte
    string GetModele(string immat);// Permet de retourner le modele en fonction de la plaque d'immatriculation
    void PrintFlotteAuto(Vehicules *Hash2);//Permet d'afficher seulement les autos de luxe
    void PrintFlotteAutoStandard(Vehicules *Hash2);//Permet d'afficher seulement les autos standard
    void PrintFlotteMotos(Vehicules *Hash2);//permet d'afficher seulement les motos
    void RechercherVehiculesParMarque(Vehicules *Hash2);//Permet de rechercher des véhicule en fonction d'une marque
    void RechercherVehiculesParKm(Vehicules *Hash2);//Permet de rechercher tous les véhicules dans un interval de kilométrage
};

#endif  //_FLOTTE_H
