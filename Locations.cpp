#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>
#include <windows.h>
#include "Locations.h"
#include "Location.h"

Locations::Locations (){
    string chainepoubelle, numero, id, dday, dmois, dyear, eday, emois, eyear, assu, jauge, feday, femois, feyear, montrep;
    stringstream stream;
    ifstream Fichier;
    Location locpoubelle;

    hashlocations = new unordered_map<int, Location>;//Allocation mémoire pour notre table de hashage
    Fichier.open("Locations.txt");//On ouvre le fichier

    while (getline(Fichier, chainepoubelle)){//Oncopie une ligne dans une string jusqu'à ce que le fichier soit vide
        stream << chainepoubelle;
        getline(stream, numero, ':');//On extrait les champs séparés par des ":" pour remplir la table de hash
        getline(stream, id, ':');
        getline(stream, locpoubelle.immatriculation, ':');
        getline(stream, dday, ':');
        getline(stream, dmois, ':');
        getline(stream, dyear, ':');
        getline(stream, eday, ':');
        getline(stream, emois, ':');
        getline(stream, eyear, ':');
        getline(stream, assu, ':');
        getline(stream, jauge, ':');
        getline(stream, feday, ':');
        getline(stream, femois, ':');
        getline(stream, feyear, ':');
        getline(stream, montrep, ':');
        locpoubelle.numero = atoi(numero.c_str());
        locpoubelle.id = atoi(id.c_str());
        locpoubelle.debut.jour = atoi(dday.c_str());
        locpoubelle.debut.mois = atoi(dmois.c_str());
        locpoubelle.debut.annee = atoi(dyear.c_str());
        locpoubelle.fin.jour = atoi(eday.c_str());
        locpoubelle.fin.mois = atoi(emois.c_str());
        locpoubelle.fin.annee = atoi(eyear.c_str());
        locpoubelle.assurance = atoi(assu.c_str());
        locpoubelle.jauge = atoi(jauge.c_str());
        locpoubelle.fineffective.jour = atoi(feday.c_str());
        locpoubelle.fineffective.mois = atoi(femois.c_str());
        locpoubelle.fineffective.annee = atoi(feyear.c_str());
        locpoubelle.montantreparations = atoi(montrep.c_str());
        hashlocations->emplace(locpoubelle.numero, locpoubelle);
        stream.clear();
    }
}

void Locations::EnregistrerLocation(Location newloc) {
    hashlocations->emplace(newloc.numero, newloc);//On enregistre la nouvelle location dans le conteneur

    FILE *fp = fopen("Locations.txt", "a");//On ouvre le fichier pour écrire dedans à la suite

    auto itr = hashlocations->find(newloc.numero);//on recherche dans le conteneur l'élément nouvellement créé, cela nous retourne un itérateur
    //on écrit dans le fichier le contenu
    fprintf(fp, "%u:%u:%s:%u:%u:%u:%u:%u:%u:%u:%u:%u:%u:%u:%u\n", newloc.numero, itr->second.id, itr->second.immatriculation.c_str(), itr->second.debut.jour, itr->second.debut.mois, itr->second.debut.annee, itr->second.fin.jour, itr->second.fin.mois, itr->second.fin.annee, itr->second.assurance, itr->second.jauge, itr->second.fineffective.jour, itr->second.fineffective.mois, itr->second.fineffective.annee, itr->second.montantreparations);
    fclose(fp);//on ferme le fichier
}

void Locations::PrintLocations() {//on affiche toutes les locations en parcourant la table de hashage
    cout << " La liste des locations dans la table hash4 des Emprunteurs est la suivante :"<< endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Numero, id,  immatriculation,      debut,    fin,     assurance, jauge depart" << endl;
    for (auto itr = hashlocations->begin(); itr != hashlocations->end(); itr++){
        cout << itr->first << "\t" << itr->second.id << "\t" << itr->second.immatriculation << "\t  " << itr->second.debut.jour << "/" << itr->second.debut.mois << "/" << itr->second.debut.annee << " " << itr->second.fin.jour << "/" << itr->second.fin.mois << "/" << itr->second.fin.annee << "\t" << itr->second.assurance << "\t\t" << itr->second.jauge << "/4" << endl;
    }
    cout << endl;
    system("pause");
}

Location Locations::GetLocation(int numero){//on récupère l'objet location en fonction du numéro de la location
    Location loki = hashlocations->at(numero);
    return loki;
}

void Locations::ModifLocation(int numero, Location loc){
    hashlocations->at(numero)=loc;
    FILE *fp = fopen("Locations.txt", "w");//On ouvre le fichier pour écrire dedans à la suite

    for (auto itr = hashlocations->begin(); itr != hashlocations->end(); itr++){
    fprintf(fp, "%u:%u:%s:%u:%u:%u:%u:%u:%u:%u:%u:%u:%u:%u:%u\n", itr->first, itr->second.id, itr->second.immatriculation.c_str(), itr->second.debut.jour, itr->second.debut.mois, itr->second.debut.annee, itr->second.fin.jour, itr->second.fin.mois, itr->second.fin.annee, itr->second.assurance, itr->second.jauge, itr->second.fineffective.jour, itr->second.fineffective.mois, itr->second.fineffective.annee, itr->second.montantreparations);
    }
    fclose(fp);//on ferme le fichier
}

bool Locations::FindEmprunteursByLoc(int id){//on determine si un emprunteur dont on a l'ID possède une location en cours et on renvoie vraix ou faux
    bool pouet=false;
    for (auto itr = hashlocations->begin(); itr != hashlocations->end(); itr++){
        if(itr->second.id==id)
        {
            pouet=true;
        }
    }
    return pouet;
}

void Locations::FindEmprunteursByModele(Emprunteurs *Hash1, Flotte *Hash3){//on recherche tous les emprunteurs qui louent un modèle particulier et on les affiche
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    string modele;
    SetConsoleTextAttribute(hConsole2, 244);
    cout << "Entrez le nom du modele: (Sensible a la casse)" << endl;
    SetConsoleTextAttribute(hConsole2, 241);
    getline(cin, modele);
    SetConsoleTextAttribute(hConsole2, 249);
    cout << endl;
    for (auto itr = hashlocations->begin(); itr != hashlocations->end(); itr++){
        if(Hash3->GetModele(itr->second.immatriculation)==modele)
        {
          Hash1->FindPrint(itr->second.id);
        }
    }
    SetConsoleTextAttribute(hConsole2, 241);
    cout << "\nUn nom apparait plusieurs fois c'est qu'il a loue plusieurs vehicules de ce typeSi rien n'apparait c'est qu'il ny a aucune location de ce type de vehicule\n" << endl;
    system("pause");
    system("cls");
}

void Locations::Statistiques(Flotte *Hash3){//on determine les types de véhicules les plus empruntés en ayant recours à une map pour les trier, puis on affiche le contenu
    string modele;
    map<string, int> stats;
    cout << "\t\tStatistiques des vehicules les plus empruntes:"<< endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Nombres d'emprunts par type de vehicules:\n" << endl;
    for (auto itr = hashlocations->begin(); itr != hashlocations->end(); itr++){
        modele = Hash3->GetModele(itr->second.immatriculation);
        stats.insert(make_pair(modele, 0));
    }
    for (auto itr = hashlocations->begin(); itr != hashlocations->end(); itr++){
        modele = Hash3->GetModele(itr->second.immatriculation);
        stats[modele]+=1;
    }
    for (auto itr = stats.begin(); itr != stats.end(); itr++){
        cout << itr->first << ": " << itr->second << endl;
    }

    cout << endl;
    system("pause");
}
