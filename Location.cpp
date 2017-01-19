#include <iostream>
#include <limits>
#include <conio.h>
#include <windows.h>
#include "Location.h"
#include "Locations.h"
#include "Emprunteurs.h"
#include "Flotte.h"

void Location::NouvelleLocation(int num, Emprunteurs *Hash1, Flotte *Hash3){//fonction pour créer une nouvelle location
    int touche;
    numero = num;
    cout << "Entrez l'ID de l'emprunteur :" << endl;
    while((!(cin >> id)) or (Hash1->CheckEmprunteurs(id)==0)) {//Saisie sécurisée pour un nombre
        cout << "L'emprunteur n'existe pas ! (L'ID doit etre un nombre), Entrez l'ID :" << endl ;
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    cout << "L'emprunteur est bien dans la base de donnees,\nEntrez la plaque d'immatriculation du vehicule a louer :" << endl;
    cin.clear();
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    getline(cin, immatriculation);
    while(Hash3->CheckExemplaire(immatriculation)==0) {//Saisie sécurisée pour un nombre
        cout << "Aucun exemplaire de ce vehicule n'est disponible dans la flotte\nEntrez la plaque d'immatriculation du vehicule a louer :" << endl ;
        getline(cin, immatriculation);
    }
    cout << "Souscription a l'assurance ?\nF1. OUI    sinon appuyez sur une touche pour continuer" << endl;
    touche=getch();
    if (touche==0 || touche==224){
        touche=getch();
        if (touche==59){
            assurance = true;
            cout << "Assurance ajoute !" << endl;}
    }
    cout << "Entrez une date de debut de location :" << endl;
    debut.SetDate();
    cout << "Entrez une date de fin de location :" << endl;
    fin.SetDate();
    fineffective = fin;//on initialise la fin effective à la même date que la fin prévue
}

void Location::RetourLocation(Flotte *Hash3){
    int touche;
    string dommages;
    cout << "Entrez une date de retour effective de location :" << endl;
    fineffective.SetDate();
    cout << "Entrez le niveau d'essence a la jauge (en quart de reservoir 1 2 3 ou 4):" << endl;
    while((!(cin >> jauge)) or jauge<0 or jauge>4) {//Saisie sécurisée pour un nombre
        cout << "Niveau incorrect ! (doit etre un nombre 0<n<4), Recommencez :" << endl ;
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    cin.clear();
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    cout << "Accident a signaler ?\nF1. OUI    sinon appuyez sur une touche pour continuer" << endl;
    touche=getch();
    if (touche==0 || touche==224){
        touche=getch();
        if (touche==59){
            cout << "Veuillez saisir les dommages (en texte en forme abregee):" << endl;
            getline(cin, dommages);
            Hash3->AddDommages(immatriculation, dommages);
            if(assurance==true){
                cout << "l'emprunteur avait souscrit une assurance : Rien a payer" << endl;
                montantreparations=0;
            }
            else{
                cout << "Veuillez entrer le montant des reparattions a inclure dans la facture" << endl;
                while((!(cin >> montantreparations)) or montantreparations<0) {//Saisie sécurisée pour un nombre
                    cout << "Prix incorrect ! (doit etre un nombre >0), Recommencez :" << endl ;
                    cin.clear();
                    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
                }
            }
        }
    }
    cin.clear();
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
}

void Location::PrintDevisFacture(Emprunteurs *Hash1, Vehicules *Hash2, Flotte *Hash3){//fonction d'affichage pour le devis et la facture
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    int ass=0, prix2=0, km, duree, dureeeffective, fraisess;
    double reduc=0, prix3=0;
    system("cls");
    cout << "\t\t\t\tDevis/Facture" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "Emprunteur :" << endl;
    SetConsoleTextAttribute(hConsole2, 242);
    Hash1->FindPrint(id);
    SetConsoleTextAttribute(hConsole2, 241);
    cout << "\nExemplaire de vehicule loue :" << endl;
    Hash3->FindPrint(immatriculation, Hash2);
    duree = debut.DateDiff(fin);
    dureeeffective = fin.DateDiffRetard(fineffective);
    SetConsoleTextAttribute(hConsole2, 241);
    if(assurance==1){
        ass=duree*23;
        cout << "\nAssurance souscrise: ";
        SetConsoleTextAttribute(hConsole2, 242);
        cout << "OUI";
        SetConsoleTextAttribute(hConsole2, 241);
        cout << "(prix : 23 euros/Jour) soit: ";
        SetConsoleTextAttribute(hConsole2, 242);
        cout << ass;
        SetConsoleTextAttribute(hConsole2, 241);
        cout << " Euros"<< endl;}
    if(assurance==0){//on regarde si le conducteur a une assurance
        ass=0;
        cout << "\nAssurance souscrise :";
        SetConsoleTextAttribute(hConsole2, 244);
        cout << "NON" << endl;}
    prix2 = Hash2->getprix(Hash3->GetModele(immatriculation));
    SetConsoleTextAttribute(hConsole2, 241);
    cout << "Prix de base du vehicule : ";
    SetConsoleTextAttribute(hConsole2, 244);
    cout << prix2;
    SetConsoleTextAttribute(hConsole2, 241);
    cout << "E/jour" << endl;

    km=Hash3->GetKM(immatriculation);
    if(km>50000 and km<100000){reduc=0.1;}//on défini la réduction lié au kilomètrage
    if(km>100000 and km<150000){reduc=0.2;}
    if(km>150000 and km<180000){reduc=0.3;}
    double stotal = prix2*duree-prix2*duree*reduc;
    if(reduc==0){stotal=prix2*duree;}
    cout << "Reduction (Km eleve): ";
    SetConsoleTextAttribute(hConsole2, 244);
    cout << reduc*100 << "% ";
    SetConsoleTextAttribute(hConsole2, 241);
    cout << "Donc le vehicule est a ";
    SetConsoleTextAttribute(hConsole2, 244);
    cout << prix2 << "*" << duree << "-" << prix2*duree*reduc << "=";
    SetConsoleTextAttribute(hConsole2, 242);
    cout << stotal;
    SetConsoleTextAttribute(hConsole2, 241);
    cout << " Euros" <<endl;
    prix3=prix2*(1.33);
    cout << "Overdue: ";
    SetConsoleTextAttribute(hConsole2, 244);
    cout << prix3;
    SetConsoleTextAttribute(hConsole2, 241);
    cout << "E/jour (Base majore a 30% par jour) soit ";
    SetConsoleTextAttribute(hConsole2, 244);
    cout << prix3 << "*" << dureeeffective << "=";
    SetConsoleTextAttribute(hConsole2, 28);
    cout << prix3*dureeeffective;
    SetConsoleTextAttribute(hConsole2, 241);
    cout << " Euros" << endl;
    cout << "Jauge: ";
    SetConsoleTextAttribute(hConsole2, 244);
    cout << jauge << "/4 ";
    SetConsoleTextAttribute(hConsole2, 241);
    cout <<  "Frais d'essence: ";
    SetConsoleTextAttribute(hConsole2, 28);
    fraisess=(4-jauge)*20;
    cout << fraisess;
    SetConsoleTextAttribute(hConsole2, 241);
    cout << " Euros.\nFrais de Reparations: ";
    SetConsoleTextAttribute(hConsole2, 28);
    cout << montantreparations;
    SetConsoleTextAttribute(hConsole2, 241);
    cout << " Euros" << endl;
    stotal+=(prix3*dureeeffective);
    cout << "\nAu TOTAL, La location s'elevera a : ";
    SetConsoleTextAttribute(hConsole2, 244);
    cout << stotal+ass+montantreparations+fraisess;
    SetConsoleTextAttribute(hConsole2, 241);
    cout << " Euros" << endl;
}
