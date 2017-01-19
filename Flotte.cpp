#include "Flotte.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <limits>
#include "Vehicules.h"

Flotte::Flotte() {
    string chainepoubelle, km;
    stringstream stream;
    ifstream Fichier;
    Exemplaire exemplairepoubelle;
    hashflotte = new unordered_map<string, Exemplaire>;

    Fichier.open("Flotte.txt");//On ouvre le fichier en lecture

    while (getline(Fichier, chainepoubelle)){//Oncopie une ligne dans une string jusqu'à ce que le fichier soit vide
        stream << chainepoubelle;
        getline(stream, exemplairepoubelle.modele, ':');//On extrait les champs séparés par des ":" pour remplir la table de hash
        getline(stream, exemplairepoubelle.couleur, ':');
        getline(stream, exemplairepoubelle.immatriculation, ':');
        getline(stream, km, ':');
        getline(stream, exemplairepoubelle.accident, ':');
        exemplairepoubelle.kilometres = atoi(km.c_str());
        hashflotte->emplace(exemplairepoubelle.immatriculation, exemplairepoubelle);
        stream.clear();
    }
}

void Flotte::EnregistrerExemplaire(Exemplaire newex) {
    hashflotte->emplace(newex.immatriculation, newex);//On enregistre le nouvel exemplaire dans le conteneur

    FILE *fp = fopen("Flotte.txt", "a");//On ouvre le fichier pour écrire dedans à la suite

    auto itr = hashflotte->find(newex.immatriculation);//on recherche dans le conteneur l'élément nouvellement créé, cela nous retourne un itérateur
    //on écrit dans le fichier le contenu
    fprintf(fp, "%s:%s:%s:%u:%s\n", itr->second.modele.c_str(),itr->second.couleur.c_str(), newex.immatriculation.c_str(), itr->second.kilometres, itr->second.accident.c_str());
    fclose(fp);//on ferme le fichier
}

void Flotte::PrintFlotte(Vehicules *Hash2) {//on affiche la flotte
    int i=1;
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "La liste da la flotte complete dans les tables hash3 et hash2 est la suivante :"<< endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Modele couleur immat kilometrage | infos vehicule\n" <<endl;
    Auto autopoubelle;
    Moto motopoubelle;

    for (auto itr = hashflotte->begin(); itr != hashflotte->end(); itr++)
    {
        i=i*(-1);
        try{//on essaie de trouver le véhicule dans les autos
            SetConsoleTextAttribute(hConsole2, 241+i);
            autopoubelle = Hash2->hashvehicules->at(itr->second.modele);
            cout << itr->second.modele << " " << itr->second.couleur << " " << itr->second.immatriculation << " " << itr->second.kilometres << "Km";
            cout << " | " << autopoubelle.marque << " " << autopoubelle.luxe << " " << autopoubelle.places << "pl " << autopoubelle.carburant << " " << autopoubelle.boite << " " << autopoubelle.prixjour << "E" << endl;
            cout << "\t-> Dommages: " << itr->second.accident << endl;
        }//si le véhicule n'est pas dans auto alors on catch l'erreur et on le recherche dans motos
        catch(const out_of_range& oor) {
            SetConsoleTextAttribute(hConsole2, 241+i);
            motopoubelle = Hash2->hashvehicules2->at(itr->second.modele);
            cout << itr->second.modele << " " << itr->second.couleur << " " << itr->second.immatriculation << " " << itr->second.kilometres << "Km";
            cout << " | " << motopoubelle.marque << " " << motopoubelle.cylindree << "cm3 " << " " << motopoubelle.prixjour << "E"<< endl;
            cout << "\t-> Dommages: " << itr->second.accident << endl;
        }
    }
    SetConsoleTextAttribute(hConsole2, 241);
    cout << endl;
}

int Flotte::CheckExemplaire(string exemplaire){//On verifie qu'un exemplaire fait bien partie de la flotte
    return hashflotte->count(exemplaire);
}

void Flotte::FindPrint(string immat, Vehicules *Hash2) {//on recherche et on affiche un exemplairre de la flotte
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    Auto autopoubelle;
    Moto motopoubelle;

    cout << "Modele couleur immat kilometrage | infos vehicule" <<endl;
    SetConsoleTextAttribute(hConsole2, 242);

    auto itr = hashflotte->find(immat);
    try{//on essaie de trouver le véhicule dans les autos
        autopoubelle = Hash2->hashvehicules->at(itr->second.modele);
        cout << itr->second.modele << " " << itr->second.couleur << " " << itr->second.immatriculation << " " << itr->second.kilometres << "Km";
        cout << " | " << autopoubelle.marque << " " << autopoubelle.luxe << " " << autopoubelle.places << "pl " << autopoubelle.carburant << " " << autopoubelle.boite << " " << autopoubelle.prixjour << "E" << endl;
        cout << "\t-> Dommages: " << itr->second.accident << endl;
    }
    catch(const out_of_range& oor) {//si le véhicule n'est pas dans auto alors on catch l'erreur et on le recherche dans motos
        motopoubelle = Hash2->hashvehicules2->at(itr->second.modele);
        cout << itr->second.modele << " " << itr->second.couleur << " " << itr->second.immatriculation << " " << itr->second.kilometres << "Km";
        cout << " | " << motopoubelle.marque << " " << motopoubelle.cylindree << "cm3 " << motopoubelle.prixjour << "E" << endl;
        cout << "\t-> Dommages: " << itr->second.accident << endl;
    }
    cout << endl;
    SetConsoleTextAttribute(hConsole2, 241);
}

string Flotte::GetModele(string immat){//on retourne le modele en fonction de l'immat
    auto itr = hashflotte->find(immat);
    return itr->second.modele;
}

int Flotte::GetKM(string immat){//on retourne la kilométrage en fonction de l'immat
    auto itr = hashflotte->find(immat);
    return itr->second.kilometres;
}

void Flotte::AddDommages(string immat, string dommages){//fonction pour ajouter des dommages au véhicule (enregistrement dans table de hash et fichier)
    auto itr2 = hashflotte->find(immat);
    itr2->second.accident=dommages;

    FILE *fp = fopen("Flotte.txt", "w");//On ouvre le fichier pour écrire dedans à la suite

    for (auto itr = hashflotte->begin(); itr != hashflotte->end(); itr++){
    //on écrit dans le fichier le contenu
    fprintf(fp, "%s:%s:%s:%u:%s\n", itr->second.modele.c_str(),itr->second.couleur.c_str(), itr->first.c_str(), itr->second.kilometres, itr->second.accident.c_str());
    }
    fclose(fp);//on ferme le fichier

}

void Flotte::SupprimerExemplaire(){//on supprime un exemplaire de la table de hash et du fichier
    string immat;
    cout << "Saisissez la plaque d'immatriculation du vehicule a supprimer" << endl;
    getline(cin, immat);

    hashflotte->erase(immat);

    FILE *fp = fopen("Flotte.txt", "w");//On ouvre le fichier pour écrire dedans à la suite

    for (auto itr = hashflotte->begin(); itr != hashflotte->end(); itr++){
    //on écrit dans le fichier le contenu
    fprintf(fp, "%s:%s:%s:%u:%s\n", itr->second.modele.c_str(),itr->second.couleur.c_str(), itr->first.c_str(), itr->second.kilometres, itr->second.accident.c_str());
    }
    fclose(fp);//on ferme le fichier
    system("cls");
}

void Flotte::PrintFlotteAuto(Vehicules *Hash2) {//on affiche seulement les autos de luxe
    int i=1;
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "\t\t\t liste des voitures de luxe :"<< endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Modele couleur immat kilometrage | infos vehicule\n" <<endl;
    Auto autopoubelle;

    for (auto itr = hashflotte->begin(); itr != hashflotte->end(); itr++)
    {

        try{

            autopoubelle = Hash2->hashvehicules->at(itr->second.modele);
            if(autopoubelle.luxe=="luxe"){
            i=i*(-1);
            SetConsoleTextAttribute(hConsole2, 241+i);
            cout << itr->second.modele << " " << itr->second.couleur << " " << itr->second.immatriculation << " " << itr->second.kilometres << "Km";
            cout << " | " << autopoubelle.marque << " " << autopoubelle.luxe << " " << autopoubelle.places << "pl " << autopoubelle.carburant << " " << autopoubelle.boite << " " << autopoubelle.prixjour << "E" << endl;
            cout << "\t-> Dommages: " << itr->second.accident << endl;
            }
        }
        catch(const out_of_range& oor) {

        }
    }
    SetConsoleTextAttribute(hConsole2, 241);
    cout << endl;
}

void Flotte::PrintFlotteAutoStandard(Vehicules *Hash2) {//on affiche seulement les autos standard
    int i=1;
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "\t\t\tListe des voitures standard :"<< endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Modele couleur immat kilometrage | infos vehicule\n" <<endl;
    Auto autopoubelle;

    for (auto itr = hashflotte->begin(); itr != hashflotte->end(); itr++)
    {
        try{
            autopoubelle = Hash2->hashvehicules->at(itr->second.modele);
            if(autopoubelle.luxe=="standard"){
            i=i*(-1);
            SetConsoleTextAttribute(hConsole2, 241+i);
            cout << itr->second.modele << " " << itr->second.couleur << " " << itr->second.immatriculation << " " << itr->second.kilometres << "Km";
            cout << " | " << autopoubelle.marque << " " << autopoubelle.luxe << " " << autopoubelle.places << "pl " << autopoubelle.carburant << " " << autopoubelle.boite << " " << autopoubelle.prixjour << "E" << endl;
            cout << "\t-> Dommages: " << itr->second.accident << endl;
            }
        }
        catch(const out_of_range& oor) {

        }
    }SetConsoleTextAttribute(hConsole2, 241);
    cout << endl;
}

void Flotte::PrintFlotteMotos(Vehicules *Hash2) {//on affiche seulement les motos
    int i=1;
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "\t\t\t\tListe des motos:"<< endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Modele couleur immat kilometrage | infos vehicule\n" <<endl;
    Moto motopoubelle;

    for (auto itr = hashflotte->begin(); itr != hashflotte->end(); itr++)
    {

        try{
            i=i*(-1);
            SetConsoleTextAttribute(hConsole2, 241+i);
            motopoubelle = Hash2->hashvehicules2->at(itr->second.modele);
            cout << itr->second.modele << " " << itr->second.couleur << " " << itr->second.immatriculation << " " << itr->second.kilometres << "Km";
            cout << " | " << motopoubelle.marque << " " << motopoubelle.cylindree << "cm3 " << motopoubelle.prixjour << "Euros" << endl;
            cout << "\t-> Dommages: " << itr->second.accident << endl;
        }
        catch(const out_of_range& oor) {
            i=i*(-1);
        }
    }
    cout << endl;
    SetConsoleTextAttribute(hConsole2, 241);
}

void Flotte::RechercherVehiculesParMarque(Vehicules *Hash2){//on effectue une recherche de véhicules par marque
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    string marque;
    cout << "Veuillez saisir la marque: (sensible a la casse)" << endl;
    getline(cin, marque);
    Auto autopoubelle;
    Moto motopoubelle;

    SetConsoleTextAttribute(hConsole2, 244);
    for (auto itr = hashflotte->begin(); itr != hashflotte->end(); itr++)//on parcours la table de hash grâce aux itérateurs
    {
        try{//on essaie de trouver le véhicules dans les autos
            autopoubelle = Hash2->hashvehicules->at(itr->second.modele);
            if(autopoubelle.marque==marque){
            cout << itr->second.modele << " " << itr->second.couleur << " " << itr->second.immatriculation << " " << itr->second.kilometres << "Km";
            cout << " | " << autopoubelle.marque << " " << autopoubelle.luxe << " " << autopoubelle.places << "pl " << autopoubelle.carburant << " " << autopoubelle.boite << " " << autopoubelle.prixjour << "E" << endl;
            cout << "\t-> Dommages: " << itr->second.accident << endl;
            }
        }//sinon on essaie de trouver le véhicule dans les motos
        catch(const out_of_range& oor) {
            motopoubelle = Hash2->hashvehicules2->at(itr->second.modele);
            if(motopoubelle.marque==marque){
            cout << itr->second.modele << " " << itr->second.couleur << " " << itr->second.immatriculation << " " << itr->second.kilometres << "Km";
            cout << " | " << motopoubelle.marque << " " << motopoubelle.cylindree << "cm3 " << " " << motopoubelle.prixjour << "E"<< endl;
            cout << "\t-> Dommages: " << itr->second.accident << endl;
            }
        }
    }
    SetConsoleTextAttribute(hConsole2, 241);
    cout << endl;
    system("pause");
    system("cls");
}

void Flotte::RechercherVehiculesParKm(Vehicules *Hash2){//on recherche un vehicule dans un interval de kilomètres
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    int kmmin, kmmax;
    cout << "Veuillez saisir le kilometrage maximum: ";
    while(!(cin >> kmmax)) {//Saisie sécurisée pour un nombre
           cout << "Le km doit etre un nombre, Ecommencez :" << endl ;
           cin.clear();
           cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    cin.clear();
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    cout << "Veuillez saisir le kilometrage minimum: ";
    while(!(cin >> kmmin)) {//Saisie sécurisée pour un nombre
           cout << "Le km doit etre un nombre, Recommencez :" << endl ;
           cin.clear();
           cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    cin.clear();
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );

    Auto autopoubelle;
    Moto motopoubelle;

    cout << endl;
    SetConsoleTextAttribute(hConsole2, 244);

    for (auto itr = hashflotte->begin(); itr != hashflotte->end(); itr++)
    {
        try{//on le recherche dans les autos
            if((itr->second.kilometres<kmmax) and (itr->second.kilometres>kmmin)){//verification du kilométrage si il correspond
            autopoubelle = Hash2->hashvehicules->at(itr->second.modele);
            cout << itr->second.modele << " " << itr->second.couleur << " " << itr->second.immatriculation << " " << itr->second.kilometres << "Km";
            cout << " | " << autopoubelle.marque << " " << autopoubelle.luxe << " " << autopoubelle.places << "pl " << autopoubelle.carburant << " " << autopoubelle.boite << " " << autopoubelle.prixjour << "E" << endl;
            cout << "\t-> Dommages: " << itr->second.accident << endl;
            }
        }
        catch(const out_of_range& oor) {//on le recherche dans les motos
            if((itr->second.kilometres<kmmax) and (itr->second.kilometres>kmmin)){//verification du kilométrage si il correspond
            motopoubelle = Hash2->hashvehicules2->at(itr->second.modele);
            cout << itr->second.modele << " " << itr->second.couleur << " " << itr->second.immatriculation << " " << itr->second.kilometres << "Km";
            cout << " | " << motopoubelle.marque << " " << motopoubelle.cylindree << "cm3 " << " " << motopoubelle.prixjour << "E"<< endl;
            cout << "\t-> Dommages: " << itr->second.accident << endl;
            }
        }
    }
    SetConsoleTextAttribute(hConsole2, 241);
    cout << endl;
    system("pause");
    system("cls");
}
