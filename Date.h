#if !defined(_DATE_H)
#define _DATE_H

using namespace std;

class Date {//Classe pour la gestion des dates
private:
    int jour;
    int mois;
    int annee;
    friend class Locations;
public:
    Date();
    void SetDate();
    int DateDiff(Date datefin);//Calcul des différences de dates pour le devis
    int DateDiffRetard(Date datefin);//Calcul du retard en fontion de la date effective pour la facture
};

#endif  //_DATE_H
