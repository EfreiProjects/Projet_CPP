#include <iostream>
#include <conio.h>
#include <limits>
#include "Auto.h"


Auto::Auto(){


}

void Auto::SetAuto() {//Permet à l'utilisateur d'entrer les infos sur la nouvelle auto
    int touche;
    cout << "Est-ce une voiture de luxe ? F1:OUI F2:NON" << endl;
    touche=getch();
    if (touche==0 || touche==224){
        touche=getch();
        switch (touche){
        case 59:{
            luxe = "luxe";
        }break;

        case 60:{
            luxe = "standard";
        }break;
        }
    }

    cout << "Entrez la marque :" << endl;
    getline(cin, marque);

    cout << "Entrez le nom du modele:" << endl;
    getline(cin, modele);

    cout << "Entrez le nombre de places :" << endl;
    while(!(cin >> places)) {//Saisie sécurisée pour un nombre
        cout << "Le nombre de places doit etre un nombre, Entrez le nombre de places :" << endl ;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n' );
    }

    cout << "Type de carburant :" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n' );
    getline(cin, carburant);
    cout << "Type de boite de vitesse :" << endl;
    getline(cin, boite);
    cout << "Entrez le prix par jour pour ce modele :" << endl;
    while(!(cin >> prixjour)) {//Saisie sécurisée pour un nombre
           cout << "Le prix doit etre un nombre, Entrez la prix/jour :" << endl ;
           cin.clear();
           cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    cin.clear();
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
}
