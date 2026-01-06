#pragma once
#include <vector>
#include <memory>
#include "../GestiuneCereri/GestiuneCereri.h"


class IGestiuneRaportari {
public:
    virtual ~IGestiuneRaportari() = default;
    
    virtual void raportAparateRespinse(const vector<unique_ptr<CerereReparatie>>& respinse) = 0;

    virtual void raportTopSalariuAngajati(const vector<unique_ptr<Angajat>>& angajati) = 0;

    virtual void Angajat_Longest_Reparatie(const vector<unique_ptr<CerereReparatie>>& cereriFinalizate,
      const vector<unique_ptr<CerereReparatie>>& cereriActive, const deque<unique_ptr<CerereReparatie>>& cereriAsteptare) = 0; 

    virtual void Cereri_Asteptare_Ordonate(const deque<unique_ptr<CerereReparatie>>& cereriAsteptare ) = 0;

};
