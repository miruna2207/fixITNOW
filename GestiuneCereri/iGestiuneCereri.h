#pragma once
#include <memory>
#include <string>
#include "cerereReparatie.h"

class IGestiuneCereri {
public:
    virtual ~IGestiuneCereri() = default;
    virtual void incarcaDinFisier(const std::string& numeFisier) = 0;
    virtual void adaugaManual() = 0;
};