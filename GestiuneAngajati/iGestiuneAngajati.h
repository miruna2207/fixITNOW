#pragma once
#include <string>

class IGestiuneAngajati {
public:
    virtual ~IGestiuneAngajati() = default;
    virtual const vector<unique_ptr<Angajat>>& get_lista_angajati() const  = 0;
    virtual void adaugaAngajat() = 0; 
    virtual void incarcaDinFisier(const std::string& numeFisier) = 0;
    virtual void afisareToti() const = 0;
    virtual void stergeAngajat(const std::string& cnp) = 0;
    virtual void modificaNume(const std::string& cnp, const std::string& numeNou) = 0;
};