#pragma once
#include "Angajat.h"
#include <vector>
#include <memory>

class CerereReparatie;
class Receptioner:public Angajat{

protected:
    vector<int> id_cereri_gestionate;

    bool is_id_cerere(int);

public:
    Receptioner() = default;

    Receptioner(const string,const string,const string,const string,const string);

    void inregistreazaCerere(std::unique_ptr<CerereReparatie> cr);

    double get_Salariu() override ;

    void afiseaza(ostream&) const override;

    string get_tip() const override;

};

