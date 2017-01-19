#include <iostream>
#include <limits>
#include "Moto.h"

Moto::Moto(){

}

void Moto::SetMoto() {//Fonction qui demande à l'utilisateur les renseignement pour enregistrer une nouvelle moto
    cout << "Entrez la marque :" << endl;
    getline(cin, marque);
    cout << "Entrez le nom du modele" << endl;
    getline(cin, modele);
    cout << "Entrez la cylindree :" << endl;
    while(!(cin >> cylindree)) {//Saisie sécurisée pour un nombre
           cout << "La cylindrée doit etre un nombre, Entrez la cylindrée :" << endl ;
           cin.clear();
           cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    cout << "Entrez le prix par jour pour ce modele :" << endl;
    while(!(cin >> prixjour)) {//Saisie sécurisée pour un nombre
           cout << "Le prix doit etre un nombre, Entrez la prix/jour :" << endl ;
           cin.clear();
           cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    cin.clear();
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
}

