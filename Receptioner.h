#pragma once
#include "Angajat.h"
#include<vector>
class Receptioner:public Angajat{

protected:
    vector<int> id_cereri_gestionate;

    bool is_id_cerere(int);

public:
    Receptioner() = default;

    void inregistreazaCerere(int id) ;

    double get_Salariu() override ;
};
