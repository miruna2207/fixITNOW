#pragma once
#include <deque>
#include <vector>
#include <memory>
#include "../GestiuneCereri/GestiuneCereri.h"
#include "../Raportari/GestiuneRaportari.h"
class ServiceManager {
private:
    unique_ptr<IGestiuneAngajati> ordinAngajati;
    unique_ptr<IGestiuneElectrocasnice> ordinElectrocasnice;
    unique_ptr<IGestiuneCereri> ordinCereri;
    unique_ptr<IGestiuneRaportari> ordinRaport;
    
    vector<unique_ptr<CerereReparatie>> cereri_active;
    deque<unique_ptr<CerereReparatie>> coada_asteptare;
    vector<unique_ptr<CerereReparatie>> cereri_finalizate;
    vector<unique_ptr<CerereReparatie>> cereri_respinse;

    ServiceManager() {
        ordinAngajati = make_unique<GestiuneAngajati>();
        ordinElectrocasnice = make_unique<GestiuneElectrocasnice>();
        ordinCereri = make_unique<GestiuneCereri>();
        ordinRaport = make_unique<GestiuneRaportari>();
    }

public:
    static ServiceManager& getInstance() {
        static ServiceManager instance;
        return instance;
    }

    IGestiuneAngajati& angajati() { return *ordinAngajati; }
    IGestiuneElectrocasnice& electrocasnice() { return *ordinElectrocasnice;};
    IGestiuneCereri& cereri() { return *ordinCereri;};
    IGestiuneRaportari& raport() { return *ordinRaport;};
    
    void proceseazaCerereNoua(unique_ptr<CerereReparatie> cr);
    void updateSimulare(); 
    void afiseaza_coada_asteptare() const;
    bool cereriInSistem() const;
    const vector<unique_ptr<CerereReparatie>>& getFinalizate() { return cereri_finalizate; }
    const vector<unique_ptr<CerereReparatie>>& getRejectate() { return cereri_respinse; }
    const vector<unique_ptr<CerereReparatie>>& getActive() { return cereri_active; }
    const deque<unique_ptr<CerereReparatie>>& getAsteptare() { return coada_asteptare;};
    
};

Tehnician* CelMaiBunTehnician(const string tipCautat,const string marcaCautata,const vector<unique_ptr<Angajat>>& lista_angajati);