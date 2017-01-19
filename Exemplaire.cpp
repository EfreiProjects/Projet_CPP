#include <iostream>
#include <limits> //numeric_limits
#include <algorithm>    //remove_if
#include "Exemplaire.h"
#include "Vehicules.h"

void Exemplaire::NouvelExemplaire(string type) {//on ajoute un nouvel exemplaire de véhicule
    if(type=="Auto"){
        Vehicules monster;
        monster.PrintTypesAuto();
        cout << "\nPour lequel des ces modeles souhaitez-vous creer un vehicule ?\n\nEntrez scrupuleusement le nom du modele disponible ci-dessus.\nSi votre modele n'est pas disponible revenez au menu principal pour l'ajouter !\n\n\n" <<endl;
        getline(cin,modele);
        while(monster.CheckAuto(modele)==0) {//Saisie sécurisée
            cout << "Modele inconnu, recommencez :" << endl ;
            getline(cin,modele);
        }
    }
    if(type=="Moto"){
        Vehicules monster;
        monster.PrintTypesMoto();
        cout << "\nPour lequel des ces modeles souhaitez-vous creer un vehicule ?" << endl << endl << "Entrez scrupuleusement le nom du modele disponible ci-dessus." << endl <<"Si votre modele n'est pas disponible revenez au menu principal pour l'ajouter !\n\n\n" <<endl;
        getline(cin,modele);
        while(monster.CheckMoto(modele)==0) {//Saisie sécurisée
            cout << "Modele inconnu, recommencez :" << endl ;
            getline(cin,modele);
        }
    }

    system("cls");
    cout << "Veuillez saisir le numero d'immatriculation (forme AA-666-AA, chiffres & lettres supportes)" << endl;
    getline(cin,immatriculation);
    cout << "Couleur :" << endl;
    getline(cin,couleur);
    cout << "Kilometrage actuel (nombre entier) :" << endl;
    while(!(cin >> kilometres) || kilometres>180000) {//Saisie sécurisée
        cout << "Le kilometrage doit etre un nombre inférieur a 180000, Entrez le kilometrage :" << endl ;
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    cout << "Nouveau vehicule : Pas de dommages a enregistrer (Description vide)" << endl;
    accident = "";
}
