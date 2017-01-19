#if !defined(_MOTO_H)
#define _MOTO_H
#include "Vehicule.h"

class Moto : public Vehicule{
private:
    int cylindree;
    friend class Vehicules;
    friend class Flotte;
public:
    Moto();
    void SetMoto();//Défini les caractéristiques d'une nouvelle moto
};

#endif  //_MOTO_H
