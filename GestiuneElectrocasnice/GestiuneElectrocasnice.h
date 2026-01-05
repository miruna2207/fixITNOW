#pragma once
#include "IGestiuneElectrocasnice.h"
#include <vector>
#include <memory>
#include<map>

class GestiuneElectrocasnice : public IGestiuneElectrocasnice {
private:
    map<string,vector<unique_ptr<Electrocasnic>>> catalog;

public:
    void incarcaModeleDinFisier(const std::string& numeFisier) override;
    void adaugaModelManual() override;
    void afisareCatalog() const override;
    bool esteModelReparabil(const string& tip, const string& marca, const string& model) const override;
    void stergeModel(const string& tip,const string& marca, const string& model) override;
};
