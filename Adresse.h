#if !defined(_ADRESSE_H)
#define _ADRESSE_H
#include <string>

using namespace std;

class Adresse {//C'est la classe qui gère les adresses des emprunteurs.
private:
	int numero;
	string rue;
    string cp;
	string ville;
    friend class Emprunteurs;
public:

    Adresse();
    void SetAdresse();//Méthode pour définir l'adresse d'un utilisateur.
};

#endif  //_ADRESSE_H
