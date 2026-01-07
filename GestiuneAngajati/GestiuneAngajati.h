#pragma once
#include "IGestiuneAngajati.h"
#include <vector>
#include <memory>

class GestiuneAngajati : public IGestiuneAngajati {
private:
    vector<unique_ptr<Angajat>> lista;

public:
    const vector<unique_ptr<Angajat>>& get_lista_angajati() const override;
    void adaugaAngajat() override; 
    void incarcaDinFisier(const string& numeFisier) override;
    void afisareToti() const override;
    void stergeAngajat(const string& cnp) override;
    void modificaNume(const string& cnp, const string& numeNou) override;
    Angajat* gasesteDupaCNP(const std::string& cnp) const override;
    bool echipaCompleta() const override;
};