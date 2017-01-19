#include <iostream>
#include <limits>
#include "Adresse.h"

Adresse::Adresse(){

}

void Adresse::SetAdresse() {//demande à l'utilisateur d'entrer les informations concernant l'adresse de l'utilisateur
    cout << "Entrez le numero de voie :" << endl;
    while(!(cin >> numero)) {//Saisie sécurisée pour un nombre
           cout << "Le numero de voie doit etre un nombre, Entrez le numero de voie :" << endl ;
           cin.clear();//vide le buffer clavier
           cin.ignore( numeric_limits<streamsize>::max(), '\n' );//vide le buffer cin
    }

    cout << "Entrez le nom de la rue :" << endl;
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    getline(cin, rue);
    cout << "Code postal :" << endl;
    getline(cin, cp);
    cout << "Ville :" << endl;
    getline(cin, ville);
}
