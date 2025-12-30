#pragma once
#include <string>

class IGestiuneElectrocasnice {
public:
    virtual ~IGestiuneElectrocasnice() = default;
    virtual void incarcaModeleDinFisier(const std::string& numeFisier) = 0;
    virtual void adaugaModelManual() = 0;
    virtual void stergeModel(const std::string& tip,const std::string& marca, const std::string& model) = 0;
    virtual void afisareCatalog() const = 0;
    virtual bool esteModelReparabil(const std::string& tip, const std::string& marca, const std::string& model) const = 0;
};