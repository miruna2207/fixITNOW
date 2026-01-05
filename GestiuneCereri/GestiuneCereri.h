#pragma once
#include "IGestiuneCereri.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>


unique_ptr<Electrocasnic> citesteAparat(stringstream& ss, string tip,int nr_linie);

class GestiuneCereri : public IGestiuneCereri {
public:
    void incarcaDinFisier(const std::string& numeFisier) override;
    void adaugaManual() override;

};