#include <iostream>
#include <limits>
#include "Emprunteur.h"

using namespace std;

Emprunteur::Emprunteur(){

}

int Emprunteur::NouvelEmprunteur(int hashsize) {//on demande à l'utilisateur d'entrer les infos du nouvel emprunteur
    cout << "Entrez le nom du nouvel emprunteur :" << endl;
    getline(cin, nom);
    cout << "Entrez son prenom :" << endl;
    getline(cin, prenom);

    adresse.SetAdresse();
    id = hashsize;
    return id;
}
