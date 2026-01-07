#pragma once
#include "iRaport.h"
#include <vector>
#include <memory>
#include <deque>

class CerereReparatie;
class Angajat;

class GestiuneRaportari : public IGestiuneRaportari {
public: 
    GestiuneRaportari() = default;
    ~GestiuneRaportari() override = default;

    
    void raportAparateRespinse(const std::vector<std::unique_ptr<CerereReparatie>>& respinse) override;
    void raportTopSalariuAngajati(const std::vector<std::unique_ptr<Angajat>>& angajati) override;
    void Cereri_Asteptare_Ordonate(const std::deque<std::unique_ptr<CerereReparatie>>& cereriAsteptare) override;
    void Angajat_Longest_Reparatie(const std::vector<std::unique_ptr<CerereReparatie>>& cereriFinalizate,
        const std::vector<std::unique_ptr<CerereReparatie>>& cereriActive, 
        const std::deque<std::unique_ptr<CerereReparatie>>& cereriAsteptare) override; 
};