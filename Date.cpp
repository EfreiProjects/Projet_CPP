#include <iostream>
#include <limits>
#include <ctime>
#include <windows.h>
#include "Date.h"

Date::Date(){

}

void Date::SetDate(){
    cout << "Jour : (JJ) : ";
    while(!(cin >> jour) or (jour<1) or (jour >31)) {//Saisie sécurisée pour un nombre
           cout << "Le jour doit etre un nombre compris entre 1 et 31\nJour : (JJ) : ";
           cin.clear();
           cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    cin.clear();
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    cout << "Mois (MM) : ";
    while(!(cin >> mois) or (mois<1) or (mois>12)) {//Saisie sécurisée pour un nombre
           cout << "Le mois doit etre un nombre compris entre 1 et 12\nMois : (MM) : ";
           cin.clear();
           cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    cin.clear();
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    cout << "Annee (YYYY): ";
    while(!(cin >> annee) or (annee<2013) or (annee>2050)) {//Saisie sécurisée pour un nombre et on sécurise l'annee
        cout << "L'anee doit etre comprise entre 2013 et 2050\nAnnee : (YYYY) : ";
           cin.clear();
           cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    cin.clear();
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
}

int Date::DateDiff(Date datefin){//calcule la différence entre deux dates
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    struct tm d = {0, 0, 0, jour, mois-1, annee-1900,0,0,0};//on utilise la structure date de la STL
    struct tm f = {0, 0, 0, datefin.jour, datefin.mois-1, datefin.annee-1900,0,0,0};
        time_t x = mktime(&d);//On convertit la date
        time_t y = mktime(&f);
        if ( x != (time_t)(-1) && y != (time_t)(-1) ){
            double difference = difftime(y, x)/(86400);
            cout << "Date de depart en location : ";
            SetConsoleTextAttribute(hConsole2, 249);
            cout << ctime(&x);
            SetConsoleTextAttribute(hConsole2, 241);
            cout << "Date de retour de location : ";
            SetConsoleTextAttribute(hConsole2, 249);
            cout << ctime(&y);
            SetConsoleTextAttribute(hConsole2, 241);
            cout << "Duree de location: ";
            SetConsoleTextAttribute(hConsole2, 249);
            cout << difference;
            SetConsoleTextAttribute(hConsole2, 241);
            cout << " Jours" << endl;
            return difference;
        }else{return 0;}
}

int Date::DateDiffRetard(Date datefin){//calcule la différence entre deux dates
    HANDLE hConsole2=GetStdHandle(STD_OUTPUT_HANDLE);
    struct tm d = {0, 0, 0, jour, mois-1, annee-1900,0,0,0};//on utilise la structure date de la STL
    struct tm f = {0, 0, 0, datefin.jour, datefin.mois-1, datefin.annee-1900,0,0,0};
        time_t x = mktime(&d);//On convertit la date
        time_t y = mktime(&f);
        if ( x != (time_t)(-1) && y != (time_t)(-1) ){
            double difference = difftime(y, x)/(86400);
            cout << "Date de retour Effective : ";
            SetConsoleTextAttribute(hConsole2, 249);
            cout << ctime(&y);
            SetConsoleTextAttribute(hConsole2, 241);
            cout << "Jours de penalite: ";
            SetConsoleTextAttribute(hConsole2, 249);
            cout << difference;
            SetConsoleTextAttribute(hConsole2, 241);
            cout << " Jours" << endl;
            return difference;
        }else{return 0;}
}
