#pragma once
#include "Angajat.h"
#include "../electronics/cerereReparatie.h"
#include "../ServiceManager.h"
class Receptioner:public Angajat{

protected:
    vector<int> id_cereri_gestionate;

    bool is_id_cerere(int);

public:
    Receptioner() = default;

    Receptioner(const string,const string,const string,const string,const string);

    void Receptioner::inregistreazaCerere(CerereReparatie& cr);

    double get_Salariu() override ;

    void afiseaza() const override;

    string get_tip() const override;

};

