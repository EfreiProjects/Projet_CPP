#include <string>
#include <iostream>
#include <limits>
#include <conio.h>
#include <windows.h>
#include "Emprunteur.h"
#include "Emprunteurs.h"
#include "Vehicule.h"
#include "Vehicules.h"
#include "Exemplaire.h"
#include "Flotte.h"
#include "Location.h"
#include "Locations.h"

using namespace std;

//déclarations des fonctions du main chargées de l'ergonomie du programme
void CommandesDispo();
void PrintStatistiques();
void NouvelEx(Flotte *Hash3);
void NouveauVehicule(Vehicules *Hash2);
void Nouveau(Vehicules *Hash2, Flotte *Hash3);
void PrintFlotte(Vehicules *Hash2, Flotte *Hash3);
void PrintVehicules(Vehicules *Hash2, Flotte *Hash3);
void RetourDeLocation(Flotte *Hash3, Locations *Hash4);
void ListeEmprunteurs(Emprunteurs *Hash1, Flotte *Hash3, Locations *Hash4);
void NouvelleLocation(Emprunteurs *Hash1, Vehicules *Hash2, Flotte *Hash3, Locations *Hash4);
void EditionDevisFactures(Emprunteurs *Hash1, Vehicules *Hash2, Flotte *Hash3, Locations *Hash4);

//déclaration de l'objet console
HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

int main ()
{
    system("color F1");

    //On créée tous les conteneurs qui vont charger les fichiers grâce à leurs constructeurs
    Emprunteurs Hash1;
    Vehicules Hash2;
    Flotte Hash3;
    Locations Hash4;

    int touche, touche2;
    while(1){//Boucle infinie du menu principal
        system("cls");
        cout << endl<< "\t\tThibaut Labouret - Charles Millequant - Jennifer Benatar" << endl << endl;
        SetConsoleTextAttribute(hConsole, 244);
        cout << "\t\t\t     Projet 2013 de C++ et d'UML" << endl << endl;
        cout << "\t\t\t  Logiciel de location de vehicules" << endl << endl << endl;
        SetConsoleTextAttribute(hConsole, 241);
        cout << "\t   F1.  Nouvel Emprunteur." << endl;
        cout << "\t   F2.  Liste des emprunteurs / Consultation des emprunteurs." << endl;
        cout << "\t   F3.  Edition des Devis/Factures." << endl;
        cout << "\t   F4.  Liste des vehicules/Consultation des vehicules." << endl;
        cout << "\t   F5.  Saisie d'une nouvelle location." << endl;
        cout << "\t   F6.  Retour de location / Modifier Check-in." << endl;
        cout << "\t   F7.  Consultation des locations." << endl;
        cout << "\t   F8.  Statistiques sur les vehicules les plus empruntes." << endl;
        cout << "\t   F9.  Nouveau vehicule." << endl;
        cout << "\t   F10. Commandes disponibles." << endl;
        cout << endl << "\t  [ECHAP] Quitter\n\n" << endl;

        touche=getch();
        if (touche==0 || touche==224){
            touche=getch();
            switch (touche){
            case 59:{
                system("cls");
                Emprunteur toto;
                int id = toto.NouvelEmprunteur(Hash1.GiveID());
                cout << "\nF1. Pour confirmer l'enregistrement. Sinon appuyez sur une touche pour continuer" << endl;
                touche2=getch();
                if (touche2==0 || touche2==224){
                    touche2=getch();
                    if (touche2==59){
                        Hash1.EnregistrerEmprunteur(id, toto);
                        cout << "Enregistrement effectue" << endl;}
                }
                system("pause");
            }break;

            case 60:{
                system("cls");
                Hash1.PrintEmprunteurs();
                ListeEmprunteurs(&Hash1, &Hash3, &Hash4);
            }break;

            case 61:{
                system("cls");
                EditionDevisFactures(&Hash1, &Hash2, &Hash3, &Hash4);
            }break;

            case 62:{
                system("cls");
                PrintVehicules(&Hash2, &Hash3);
            }break;

            case 63:{
                system("cls");
                NouvelleLocation(&Hash1, &Hash2, &Hash3, &Hash4);
            }break;

            case 64:{
                system("cls");
                RetourDeLocation(&Hash3, &Hash4);
            }break;

            case 65:{
                system("cls");
                Hash4.PrintLocations();
            }break;

            case 66:{
                system("cls");
                Hash4.Statistiques(&Hash3);
            }break;

            case 67:{
                system("cls");
                Nouveau(&Hash2, &Hash3);
            }break;

            case 68:{
                system("cls");
                CommandesDispo();
            }break;
            }
        }
        if (touche==27) break;
    }
}

//Toutes les fonctions qui suivent gèrent les actions de lorsque l'on appuie sur une touche elles ne sont pas intéressantes à étudier dans le cadre du projet.
void Nouveau(Vehicules *Hash2, Flotte *Hash3) {
    int touche;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\t  F1. Nouveau type de Vehicule."<< endl;
    cout << "\t  F2. Nouvel Exemplaire de Vehicule a inclure dans la Flotte.\n\n" << endl;
    cout << "\t  [ECHAP] Menu Principal.\n" << endl;
    touche=getch();
    if (touche==0 || touche==224){
        touche=getch();
        switch (touche){
        case 59:{
            system("cls");
            NouveauVehicule(Hash2);
        }break;

        case 60:{
            system("cls");
            NouvelEx(Hash3);
        }break;
        }
    }
}

void NouveauVehicule(Vehicules *Hash2) {
    int touche, touche2;
    cout << "\t\tEnregsistrement d'un nouveau vehicule :\n" << endl;
    cout << "\n\n\n\n\n\n\n\n\t\t\t  F1. Auto"<< endl;
    cout << "\t\t\t  F2. Moto\n\n" << endl;
    cout << "\t\t\t  [ECHAP] Menu Principal.\n" << endl;
    touche=getch();
    if (touche==0 || touche==224){
        touche=getch();
        switch (touche){
        case 59:{
            system("cls");
            Auto newauto;
            newauto.SetAuto();
            cout << "\nF1. Pour confirmer l'enregistrement. Sinon appuyez sur une touche pour continuer" << endl;
            touche2=getch();
            if (touche2==0 || touche2==224){
                touche2=getch();
                if (touche2==59){
                    Hash2->EnregistrerVehicule(newauto);
                    cout << "Enregistrement effectue" << endl;}
            }
            system("pause");
        }break;

        case 60:{
            system("cls");
            Moto newmoto;
            newmoto.SetMoto();
            cout << "\nF1. Pour confirmer l'enregistrement. Sinon appuyez sur une touche pour continuer" << endl;
            touche2=getch();
            if (touche2==0 || touche2==224){
                touche2=getch();
                if (touche2==59){
                    Hash2->EnregistrerVehicule(newmoto);
                    cout << "Enregistrement effectue" << endl;}
            }
            system("pause");
        }break;
        }
    }
}

void NouvelEx(Flotte *Hash3) {
    int touche, touche2;
    cout << "\t\t   Enregsistrement d'un nouvel exemplaire :\n" << endl;
    cout << "\n\n\n\n\n\n\n\n\t\t\t  F1. Auto"<< endl;
    cout << "\t\t\t  F2. Moto\n\n" << endl;
    cout << "\t\t\t  [ECHAP] Menu Principal.\n" << endl;
    touche=getch();
    if (touche==0 || touche==224){
        touche=getch();
        switch (touche){
        case 59:{
            Exemplaire newexauto;
            system("cls");
            newexauto.NouvelExemplaire("Auto");
            cout << "\nF1. Pour confirmer l'enregistrement. Sinon appuyez sur une touche pour continuer" << endl;
            touche2=getch();
            if (touche2==0 || touche2==224){
                touche2=getch();
                if (touche2==59){
                    Hash3->EnregistrerExemplaire(newexauto);
                    cout << "Enregistrement effectue" << endl;}
            }
        }break;

        case 60:{
            Exemplaire newexmoto;
            system("cls");
            newexmoto.NouvelExemplaire("Moto");
            cout << "\nF1. Pour confirmer l'enregistrement. Sinon appuyez sur une touche pour continuer" << endl;
            touche2=getch();
            if (touche2==0 || touche2==224){
                touche2=getch();
                if (touche2==59){
                    Hash3->EnregistrerExemplaire(newexmoto);
                    cout << "Enregistrement effectue" << endl;}
            }
        }break;
        }
    }
}

void PrintVehicules(Vehicules *Hash2, Flotte *Hash3) {
    int touche, touche2;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\t\tF1. Afficher la Flotte"<< endl;
    cout << "\t\tF2. Afficher seulement les types de vehicules.\n" << endl;
    cout << "\t\t[ECHAP] Menu Principal.\n" << endl;
    touche=getch();
    if (touche==0 || touche==224){
        touche=getch();
        switch (touche){
        case 59:{
            system("cls");
            Hash3->PrintFlotte(Hash2);
            PrintFlotte(Hash2, Hash3);
        }break;

        case 60:{
            system("cls");
            Hash2->PrintVehicules();
            cout << "F3. Supprimer modele" << endl;
            touche2=getch();
            if (touche2==0 || touche2==224){
                touche2=getch();
                if (touche2==61){
                    Hash2->SupprimerVehicule();
                    Hash2->PrintVehicules();
                    system("pause");
                }
            }
        }break;
        }
    }
}

void PrintStatistiques() {

}

void NouvelleLocation(Emprunteurs *Hash1, Vehicules *Hash2, Flotte *Hash3, Locations *Hash4){
    Location loc;
    int touche2, num;
    num = Hash4->GiveNumero();
    loc.NouvelleLocation(num, Hash1, Hash3);
    loc.PrintDevisFacture(Hash1, Hash2, Hash3);
    cout << "\nF1. Pour confirmer l'enregistrement. Sinon appuyez sur une touche pour continuer" << endl;
    touche2=getch();
    if (touche2==0 || touche2==224){
        touche2=getch();
        if (touche2==59){
            Hash4->EnregistrerLocation(loc);
            cout << "Enregistrement effectue" << endl;}
    }
    system("pause");
}

void EditionDevisFactures(Emprunteurs *Hash1, Vehicules *Hash2, Flotte *Hash3, Locations *Hash4){
    int num, touche2;
    Location loc;
    system("cls");
    cout << "Entrez le numero de location:" << endl;
    while(!(cin >> num)) {//Saisie sécurisée pour un nombre
        cout << "Cette location n'existe pas ! (Le numero doit etre un nombre), Entrez le numero de location :" << endl ;
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    cin.clear();
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    loc = Hash4->GetLocation(num);
    loc.PrintDevisFacture(Hash1, Hash2, Hash3);
    cout << "\nF1. Pour modifier le retour. Ou appuyez sur une touche pour continuer" << endl;
    touche2=getch();
    if (touche2==0 || touche2==224){
        touche2=getch();
        if (touche2==59){
            RetourDeLocation(Hash3, Hash4);
        }
    }

}

void RetourDeLocation(Flotte *Hash3, Locations *Hash4){
    int num;
    Location loc;
    system("cls");
    cout << "Entrez le numero de location:" << endl;
    while(!(cin >> num)) {//Saisie sécurisée pour un nombre
        cout << "Cette location n'existe pas ! (Le numero doit etre un nombre), Entrez le numero de location :" << endl ;
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    cin.clear();
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    loc = Hash4->GetLocation(num);
    loc.RetourLocation(Hash3);
    Hash4->ModifLocation(num, loc);
    system("pause");
}

void ListeEmprunteurs(Emprunteurs *Hash1, Flotte *Hash3,Locations *Hash4){
    int touche;
    cout << "F1. Classement ID | F2. Alphabetique | F3. Emprunteur avec location en cours\nF4. Rechercher emprunteur par nom | F5. Par modele de vehicule | F6. Supprimer\nAppuyez sur une touche pour continuer" << endl;
    touche=getch();
    if (touche==0 || touche==224){
        touche=getch();
        switch (touche){
        case 59:{
            system("cls");
            Hash1->PrintEmprunteurs();
            ListeEmprunteurs(Hash1, Hash3, Hash4);
        }break;

        case 60:{
            system("cls");
            Hash1->PrintEmprunteursAlpha();
            ListeEmprunteurs(Hash1, Hash3, Hash4);
        }break;

        case 61:{
            system("cls");
            Hash1->PrintEmprunteursByLoc(Hash4);
            ListeEmprunteurs(Hash1, Hash3, Hash4);
        }break;

        case 62:{
            Hash1->FindByName();
            Hash1->PrintEmprunteurs();
            ListeEmprunteurs(Hash1, Hash3, Hash4);
        }break;

        case 63:{
            Hash4->FindEmprunteursByModele(Hash1, Hash3);
            Hash1->PrintEmprunteurs();
            ListeEmprunteurs(Hash1, Hash3, Hash4);
        }break;

        case 64:{
            Hash1->SupprimerEmprunteur();
            Hash1->PrintEmprunteurs();
            ListeEmprunteurs(Hash1, Hash3, Hash4);
        }break;


        }
    }
}

void PrintFlotte(Vehicules *Hash2, Flotte *Hash3){
    int touche;
    cout << "F1. Tous les vehicules | F2. Autos Luxe | F3. Autos Standard | F4. Motos\nF5. Rechercher par marque | F6. Rechercher par Km | F7. Supprimer Vehicule" << endl;
    touche=getch();
    if (touche==0 || touche==224){
        touche=getch();
        switch (touche){
        case 59:{
            system("cls");
            Hash3->PrintFlotte(Hash2);
            PrintFlotte(Hash2, Hash3);
        }break;

        case 60:{
            system("cls");
            Hash3->PrintFlotteAuto(Hash2);
            PrintFlotte(Hash2, Hash3);
        }break;

        case 61:{
            system("cls");
            Hash3->PrintFlotteAutoStandard(Hash2);
            PrintFlotte(Hash2, Hash3);
        }break;

        case 62:{
            system("cls");
            Hash3->PrintFlotteMotos(Hash2);
            PrintFlotte(Hash2, Hash3);
        }break;

        case 63:{
            Hash3->RechercherVehiculesParMarque(Hash2);
            Hash3->PrintFlotte(Hash2);
            PrintFlotte(Hash2, Hash3);
        }break;

        case 64:{
            Hash3->RechercherVehiculesParKm(Hash2);
            Hash3->PrintFlotte(Hash2);
            PrintFlotte(Hash2, Hash3);
        }break;

        case 65:{
            Hash3->SupprimerExemplaire();
            Hash3->PrintFlotte(Hash2);
            system("pause");
        }break;
        }
    }
}

void CommandesDispo(){
    cout << "\t\t\tListe des commandes disponibles:"<< endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "En plus des commandes dont vous avez acces sur l'ecran d'acceuil vous avez\n" << endl;
    cout << "Menu Liste des emprunteurs:" << endl;
    cout << "F1. Classement ID | F2. Alphabetique | F3. Emprunteur avec location en cours\nF4. Rechercher emprunteur par nom | F5. Par modele de vehicule | F6. Supprimer\n" << endl;
    cout << "Menu Vehicules:\nFlotte:" << endl;
    cout << "F1. Tous les vehicules | F2. Autos Luxe | F3. Autos Standard | F4. Motos\nF5. Rechercher par marque | F6. Rechercher par Km | F7. Supprimer Vehicule\n\nVehicules" << endl;
    cout << "F3. Supprimer type de vehicule" << endl;
    system("pause");
}
