#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <windows.h>
#include "Vehicules.h"
#include "Auto.h"
#include "Moto.h"

using namespace std;

Vehicules::Vehicules (){
    string chainepoubelle, places, type, cylindree, prix;
    stringstream stream;
    Auto Autopoubelle;
    Moto Motopoubelle;

    hashvehicules = new unordered_map<string, Auto>;//Allocation mémoire pour notre table de hashage des Autos
    hashvehicules2 = new unordered_map<string, Moto>;//Allocation mémoire pour notre table de hashage des Motos

    ifstream Fichier;
    Fichier.open("Vehicules.txt");//On ouvre le fichier

    while (getline(Fichier, chainepoubelle)){//Oncopie une ligne dans une string jusqu'à ce que le fichier soit vide
    stream << chainepoubelle;

    getline(stream, type, ':');
    if(type=="Auto"){
        getline(stream, Autopoubelle.modele, ':');
        getline(stream, Autopoubelle.luxe, ':');
        getline(stream, Autopoubelle.marque, ':');
        getline(stream, places, ':');
        getline(stream, Autopoubelle.carburant, ':');
        getline(stream, Autopoubelle.boite, ':');
        getline(stream, prix, ':');
        Autopoubelle.places = atoi(places.c_str());
        Autopoubelle.prixjour = atoi(prix.c_str());
        hashvehicules->emplace(Autopoubelle.modele, Autopoubelle);
    }
    if(type=="Moto"){
        getline(stream, Motopoubelle.modele, ':');
        getline(stream, Motopoubelle.marque, ':');
        getline(stream, cylindree, ':');
        getline(stream, prix, ':');
        Motopoubelle.cylindree = atoi(cylindree.c_str());
        Motopoubelle.prixjour = atoi(prix.c_str());
        hashvehicules2->emplace(Motopoubelle.modele, Motopoubelle);
    }
    stream.clear();
    }
}



void Vehicules::EnregistrerVehicule(Auto titine) {
    hashvehicules->emplace(titine.modele, titine);//On enregistre la nouvelle Auto dans le conteneur

    FILE *fp = fopen("Vehicules.txt", "a");//On ouvre le fichier pour écrire dedans à la suite

    auto itr = hashvehicules->find(titine.modele);//on recherche dans le conteneur l'élément nouvellement créé, cela nous retourne un itérateur
    //on écrit dans le fichier le contenu
    fprintf(fp, "%s:%s:%s:%s:%u:%s:%s:%u\n", "Auto",titine.modele.c_str(), itr->second.luxe.c_str(), itr->second.marque.c_str(), itr->second.places, itr->second.carburant.c_str(), itr->second.boite.c_str(), itr->second.prixjour);
    fclose(fp);//on ferme le fichier
}

void Vehicules::EnregistrerVehicule(Moto petrolette) {
    hashvehicules2->emplace(petrolette.modele, petrolette);//On enregistre la nouvelle Moto dans le conteneur

    FILE *fp = fopen("Vehicules.txt", "a");//On ouvre le fichier pour écrire dedans à la suite

    auto itr = hashvehicules2->find(petrolette.modele);//on recherche dans le conteneur l'élément nouvellement créé, cela nous retourne un itérateur
    //on écrit dans le fichier le contenu
    fprintf(fp, "%s:%s:%s:%u:%u\n", "Moto",petrolette.modele.c_str(), itr->second.marque.c_str(), itr->second.cylindree, itr->second.prixjour);
    fclose(fp);//on ferme le fichier

}

void Vehicules::PrintVehicules() {//on affiche tous les types de véhicules de la table de hash
    int i=1;
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "\t  La liste des vehicules dans la table hash2 est la suivante :"<< endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Autos :" << endl;
    cout << "Modele  luxe  marque  places  carburant  boite de vitesse Prix/jour\n" << endl;
    for (auto itr = hashvehicules->begin(); itr != hashvehicules->end(); itr++){
        i=i*(-1);
        SetConsoleTextAttribute(hConsole2, 241+i);
        cout << itr->first << " " << itr->second.luxe << " " << itr->second.marque << " " << itr->second.places << "places " << itr->second.carburant << " " << itr->second.boite << " " << itr->second.prixjour << "Euros" << endl;
    }
    SetConsoleTextAttribute(hConsole2, 241);
    i=1;
    cout << "\n--------------------------------------------------------------------------------" << endl;
    cout << "Motos :" << endl;
    cout << "modele marque cylindree Prix/Jour\n"  << endl;
    for (auto itr = hashvehicules2->begin(); itr != hashvehicules2->end(); itr++){
        i=i*(-1);
        SetConsoleTextAttribute(hConsole2, 241+i);
        cout << itr->first << " " << itr->second.marque << " " << itr->second.cylindree << "cm3" << " " << itr->second.prixjour << "Euros" << endl;
    }
    SetConsoleTextAttribute(hConsole2, 241);
    cout << endl;
}

void Vehicules::PrintTypesAuto() {// <on affiches tous les noms de modèles d'Auto
    cout << "\nLes modeles d'Auto disponibles sont les suivant :\n"<< endl;
    for (auto itr = hashvehicules->begin(); itr != hashvehicules->end(); itr++){
        cout  << " - " << itr->first;
    }
    cout << "-" << endl;
}

void Vehicules::PrintTypesMoto() {//On affiche tous les noms de modèle de moto
    cout << "\nLes modeles de Moto disponibles sont les suivant :\n"<< endl;

    for (auto itr = hashvehicules2->begin(); itr != hashvehicules2->end(); itr++){
        cout  << " - " << itr->first;
    }
    cout << "-" << endl;
}

int Vehicules::CheckAuto(string modele){//on verifie que le modele d'auto existe bien bien dans (fonction pour la saisie sécurisée)
    return hashvehicules->count(modele);
}

int Vehicules::CheckMoto(string modele){
    return hashvehicules2->count(modele);
}

int Vehicules::getprix(string modele){//on retourne le prix en fonction du modèle
    try{
        Auto poubelle1 = hashvehicules->at(modele);
        return poubelle1.prixjour;
    }
    catch(const out_of_range& oor) {
        Moto poubelle2 = hashvehicules2->at(modele);
        return poubelle2.prixjour;
    }
    cout << endl;
}

void Vehicules::SupprimerVehicule(){//on supprime un véhicule à la foi de la table de hash mais aussi du fichier
    string modele;
    cout << "Entrez le nom du modele de vehicule que vous souhaitez supprimer:" << endl;
    getline(cin, modele);

    hashvehicules->erase(modele);
    hashvehicules2->erase(modele);

    FILE *fp = fopen("Vehicules.txt", "w");//On ouvre le fichier pour écrire dedans à la suite
    for (auto itr = hashvehicules->begin(); itr != hashvehicules->end(); itr++){
    //on écrit dans le fichier le contenu
    fprintf(fp, "%s:%s:%s:%s:%u:%s:%s:%u\n", "Auto",itr->first.c_str(), itr->second.luxe.c_str(), itr->second.marque.c_str(), itr->second.places, itr->second.carburant.c_str(), itr->second.boite.c_str(), itr->second.prixjour);
    }
    for (auto itr = hashvehicules2->begin(); itr != hashvehicules2->end(); itr++){
    //on écrit dans le fichier le contenu
    fprintf(fp, "%s:%s:%s:%u:%u\n", "Moto",itr->first.c_str(), itr->second.marque.c_str(), itr->second.cylindree, itr->second.prixjour);
    }
    fclose(fp);//on ferme le fichier
    system("cls");
}
