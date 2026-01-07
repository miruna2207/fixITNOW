#pragma once
#include <vector>
#include <memory>
#include <deque>

class CerereReparatie;
class Angajat;

class IGestiuneRaportari {
public:
    virtual ~IGestiuneRaportari() = default;

    virtual void raportAparateRespinse(const std::vector<std::unique_ptr<CerereReparatie>>& respinse) = 0;
    virtual void raportTopSalariuAngajati(const std::vector<std::unique_ptr<Angajat>>& angajati) = 0;
    virtual void Cereri_Asteptare_Ordonate(const std::deque<std::unique_ptr<CerereReparatie>>& cereriAsteptare) = 0;
    virtual void Angajat_Longest_Reparatie(
        const std::vector<std::unique_ptr<CerereReparatie>>& cereriFinalizate,
        const std::vector<std::unique_ptr<CerereReparatie>>& cereriActive,
        const std::deque<std::unique_ptr<CerereReparatie>>& cereriAsteptare) = 0;
};