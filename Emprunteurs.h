#if !defined(_EMPRUNTEURS_H)
#define _EMPRUNTEURS_H
#include <unordered_map>
#include <Emprunteur.h>

class Locations;

class Emprunteurs {//Classe pour la gestion du stockage des emprunteurs dans la table de Hash
private:
    unordered_map<int, Emprunteur>* hashemprunteurs;
public:
    Emprunteurs();
    int GiveID();//Retourne un nouvel id pour l'utilisateur
    void EnregistrerEmprunteur(int id1, Emprunteur totonew);//enregistrement du nouvel emprunteur dans la table de hash et dans le fichier Emprunteurs.txt
    void FindByName();//Méthode pour rechercher un utilisateur en fonction de son nom et l'afficher
    void PrintEmprunteurs();//méthode pour afficher tous les emprunteurs de la table de hash
    void PrintEmprunteursAlpha();//Afficher tous les utilisateurs par ordre alphabétique
    void SupprimerEmprunteur();//Méthode pour supprimer un emprunteur de la table de hash et du fichier.
    void PrintEmprunteursByLoc(Locations *Hash4);//Méthode pour afficher tous les utilisateurs ayant une location en cours
    int CheckEmprunteurs(int id);//Méthode pour verifier si l'emprunteur dont l'ID est fourni est bien dans la table de hash
    void FindPrint(int id);//Méthode pour aficher un emprunteur en particulier (Dont l'Id est fourni
};

#endif  //_EMPRUNTEURS_H
