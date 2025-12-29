#pragma once
#include "Angajat.h"
#include<vector>
class Receptioner:public Angajat{

protected:
    vector<int> id_cereri_gestionate;

    bool is_id_cerere(int);

public:
    Receptioner() = default;

    Receptioner(const string,const string,const string,const string,const string);

    void inregistreazaCerere(int id) ;

    double get_Salariu() override ;

    void afiseaza() const override;
};
