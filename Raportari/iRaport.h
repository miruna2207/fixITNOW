#pragma once
#include <vector>
#include <memory>
#include "../GestiuneCereri/GestiuneCereri.h"


class IGestiuneRaportari {
public:
    virtual ~IGestiuneRaportari() = default;
    
    virtual void raportAparateRespinse(const vector<unique_ptr<CerereReparatie>>& respinse) = 0;

    virtual void raportTopSalarii(const vector<unique_ptr<Angajat>>& angajati) = 0;
};