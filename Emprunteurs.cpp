#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <limits>
#include "Emprunteurs.h"
#include "Locations.h"

Emprunteurs::Emprunteurs()
{
    string chainepoubelle, numero, id;
    stringstream stream;
    Emprunteur emprunteurpoubelle;
    hashemprunteurs = new unordered_map<int, Emprunteur>;//Allocation mémoire pour notre table de hashage
    ifstream Fichier;
    Fichier.open("Emprunteurs.txt");//On ouvre le fichier

    while (getline(Fichier, chainepoubelle)){//Oncopie une ligne dans une string jusqu'à ce que le fichier soit vide
        stream << chainepoubelle;
        getline(stream, id, ':');//On extrait les champs séparés par des ":" pour remplir la table de hash
        getline(stream, emprunteurpoubelle.nom, ':');
        getline(stream, emprunteurpoubelle.prenom, ':');
        getline(stream, numero, ':');
        getline(stream, emprunteurpoubelle.adresse.rue, ':');
        getline(stream, emprunteurpoubelle.adresse.cp, ':');
        getline(stream, emprunteurpoubelle.adresse.ville, ':');
        emprunteurpoubelle.adresse.numero = atoi(numero.c_str());
        emprunteurpoubelle.id = atoi(id.c_str());
        hashemprunteurs->emplace(atoi(id.c_str()), emprunteurpoubelle);
        stream.clear();
    }
}

int Emprunteurs::GiveID(){//on regarde quel est le plus grand ID existant et on retourne le nombre+1
    int plusgrandid=1;
    for (auto itr = hashemprunteurs->begin(); itr != hashemprunteurs->end(); itr++){
        if((itr->first)>plusgrandid){
            plusgrandid=(itr->first);
        }
    }
    return plusgrandid+1;
}

void Emprunteurs::EnregistrerEmprunteur(int id, Emprunteur totonew){
    hashemprunteurs->emplace(id, totonew);//On enregistre le nouvel utilisateur dans le conteneur

    FILE *fp = fopen("Emprunteurs.txt", "a");//On ouvre le fichier pour écrire dedans à la suite

    auto itr = hashemprunteurs->find(id);//on recherche dans le conteneur l'élément nouvellement créé, cela nous retourne un itérateur
    //on écrit dans le fichier le contenu
    fprintf(fp, "%u:%s:%s:%u:%s:%s:%s\n", id, itr->second.nom.c_str(), itr->second.prenom.c_str(), itr->second.adresse.numero, itr->second.adresse.rue.c_str(), itr->second.adresse.cp.c_str(), itr->second.adresse.ville.c_str());
    fclose(fp);//on ferme le fichier
}

void Emprunteurs::PrintEmprunteurs(){
    int i=-1;
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "\t\t\t  Liste des emprunteurs par ID :"<< endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "id: nom    prenom,       adresse                  code postal    ville\n" << endl;
    for (auto itr = hashemprunteurs->begin(); itr != hashemprunteurs->end(); itr++){//on parcours la table de hash grâce aux itérateurs
        i=i*(-1);
        SetConsoleTextAttribute(hConsole2, 242+i);//affichage
        cout << itr->first << ": " << itr->second.nom << " " << itr->second.prenom << ", " << itr->second.adresse.numero << " " << itr->second.adresse.rue << " " << itr->second.adresse.cp << " " << itr->second.adresse.ville << endl;
    }
    SetConsoleTextAttribute(hConsole2, 241);
    cout << endl;
}

void Emprunteurs::PrintEmprunteursAlpha(){
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    map<string, Emprunteur> alphaemprunteurs;
    int i=-1;
    cout << "\t\t  Liste des empruteurs par ordre Alphabetique :"<< endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "id: nom    prenom,       adresse                  code postal    ville\n" << endl;

    for (auto itr2 = hashemprunteurs->begin(); itr2 != hashemprunteurs->end(); itr2++){//on classe le contenu de la map non ordonnée dans une map ordonnée en fonction du nom
        alphaemprunteurs.insert(make_pair(itr2->second.nom, itr2->second));//Le tri alphabétique se fait donc automatiquement
    }
    for (auto itr = alphaemprunteurs.begin(); itr != alphaemprunteurs.end(); itr++){//on parcours cette nouvelle map avec des itérateurs pour en afficher le contenu
        i=i*(-1);
        SetConsoleTextAttribute(hConsole2, 242+i);
        cout << itr->second.id << ": " << itr->second.nom << " " << itr->second.prenom << ", " << itr->second.adresse.numero << " " << itr->second.adresse.rue << " " << itr->second.adresse.cp << " " << itr->second.adresse.ville << endl;
    }
    SetConsoleTextAttribute(hConsole2, 241);
    cout << endl;
}

int Emprunteurs::CheckEmprunteurs(int id){//on verifie qu'un emprunteur est bien dans la table de hash.
    return hashemprunteurs->count(id);
}

void Emprunteurs::FindPrint(int id){//On recherche un emprunteur particulier et on l'affiche
    auto itr = hashemprunteurs->find(id);
    cout << itr->first << ": " << itr->second.nom << " " << itr->second.prenom << ", " << itr->second.adresse.numero << " " << itr->second.adresse.rue << " " << itr->second.adresse.cp << " " << itr->second.adresse.ville << endl;
}

void Emprunteurs::SupprimerEmprunteur(){//suppression d'un emprunteur
    int id2;
    cout << "Saisissez l'ID de l'emprunteur a supprimer :" << endl;

    while(!(cin >> id2)) {//Saisie sécurisée pour un nombre
        cout << "Invalide, Saisissez l'ID de l'emprunteur a supprimer :" << endl ;
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    cin.clear();
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );

    hashemprunteurs->erase(id2);//on élimine l'emprunteur de la table de hash
    FILE *fp = fopen("Emprunteurs.txt", "w");//On ouvre le fichier pour écrire dedans en effaçant les données précédentes
    for (auto itr = hashemprunteurs->begin(); itr != hashemprunteurs->end(); itr++){
        //on écrit dans le fichier le contenu de toute la table de hash
        fprintf(fp, "%u:%s:%s:%u:%s:%s:%s\n", itr->first, itr->second.nom.c_str(), itr->second.prenom.c_str(), itr->second.adresse.numero, itr->second.adresse.rue.c_str(), itr->second.adresse.cp.c_str(), itr->second.adresse.ville.c_str());
    }
    fclose(fp);//on ferme le fichier
    system("cls");
}


void Emprunteurs::FindByName(){//on parcours la table de hash pour trouver les utilisateurs dont le nom correspond et on l'affiche
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    string name;
    SetConsoleTextAttribute(hConsole2, 244);
    cout << "Entrez le nom de la personne que vous recherchez: (Sensible a la casse)" << endl;
    SetConsoleTextAttribute(hConsole2, 241);
    getline(cin, name);
    SetConsoleTextAttribute(hConsole2, 249);
    for (auto itr = hashemprunteurs->begin(); itr != hashemprunteurs->end(); itr++){
        if(itr->second.nom==name){//Grâce à un itérateur on verifie le champs nom
            cout << itr->first << ": " << itr->second.nom << " " << itr->second.prenom << ", " << itr->second.adresse.numero << " " << itr->second.adresse.rue << " " << itr->second.adresse.cp << " " << itr->second.adresse.ville << endl;
        }
    }
    SetConsoleTextAttribute(hConsole2, 241);
    cout << "\nSi rien n'aparait c'est qu'il n'y a aucun emprunteur avec ce nom" << endl;
    system("pause");
    system ("cls");
}

void Emprunteurs::PrintEmprunteursByLoc(Locations *Hash4){//On parcours la table de hash et on verifie que tel utilisateurs à bien une location en cours et on l'affiche
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "\t    Liste des emprunteurs qui ont une location en cours:"<< endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "id: nom    prenom,       adresse                  code postal    ville\n" << endl;
    SetConsoleTextAttribute(hConsole2, 249);
    for (auto itr = hashemprunteurs->begin(); itr != hashemprunteurs->end(); itr++){
        if(Hash4->FindEmprunteursByLoc(itr->first)==true){//fonction dispo dans Locations.cpp
            cout << itr->first << ": " << itr->second.nom << " " << itr->second.prenom << ", " << itr->second.adresse.numero << " " << itr->second.adresse.rue << " " << itr->second.adresse.cp << " " << itr->second.adresse.ville << endl;
        }
    }
    SetConsoleTextAttribute(hConsole2, 241);
    cout << endl;

}
