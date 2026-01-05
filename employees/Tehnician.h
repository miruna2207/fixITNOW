#pragma once
#include "Angajat.h"
#include <vector>

class CerereReparatie;

struct Competenta {
    string tip;   
    string marca; 
};

class Tehnician : public Angajat {
protected:
    vector<Competenta> specializari;
    double valoare_reparatii = 0; 
    int nr_cereri_active = 0;
    int timp_total = 0;
    bool is_there_competenta(const string t,const string m) const;

public:
    Tehnician() = default;
    Tehnician(const string,const string,const string,const string,const string, vector<Competenta>);
    void addSpecializari(string tip, string marca) ;
    bool CanRepair(string tip, string marca) const ;
    double get_Salariu() override ;
    int get_nr_cereri_active() const;
    int get_timp_total() const;
    string get_tip() const override;
    void updateReparatii(double valoare);
    void afiseaza(ostream&) const override;
    void addCerere(const CerereReparatie& cr);
    void finishCerere();
};