#pragma once
#include "Angajat.h"
#include <vector>

struct Competenta {
    string tip;   
    string marca; 
};

class Tehnician : public Angajat {
protected:
    vector<Competenta> specializari;
    double valoare_reparatii = 0; 
    bool is_there_competenta(const string t,const string m) const;

public:
    Tehnician() = default;

    void addSpecializari(string tip, string marca) ;
    bool CanRepair(string tip, string marca) const ;
    double get_Salariu() override ;
    void updateReparatii(double valoare);
};