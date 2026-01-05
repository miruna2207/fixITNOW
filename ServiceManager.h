#pragma once
#include <queue>
#include <vector>
#include <memory>
#include "../GestiuneCereri/GestiuneCereri.h"

class ServiceManager {
private:
    unique_ptr<IGestiuneAngajati> ordinAngajati;
    unique_ptr<IGestiuneElectrocasnice> ordinElectrocasnice;
    unique_ptr<IGestiuneCereri> ordinCereri;
    
    vector<unique_ptr<CerereReparatie>> cereri_active;
    queue<unique_ptr<CerereReparatie>> coada_asteptare;
    vector<unique_ptr<CerereReparatie>> cereri_finalizate;
    vector<unique_ptr<CerereReparatie>> cereri_respinse;

    ServiceManager() {
        ordinAngajati = make_unique<GestiuneAngajati>();
        ordinElectrocasnice = make_unique<GestiuneElectrocasnice>();
        ordinCereri = make_unique<GestiuneCereri>();
    }

public:
    static ServiceManager& getInstance() {
        static ServiceManager instance;
        return instance;
    }

     IGestiuneAngajati& angajati() { return *ordinAngajati; }
    IGestiuneElectrocasnice& electrocasnice() { return *ordinElectrocasnice;};
    IGestiuneCereri& cereri() { return *ordinCereri;};
    
    void proceseazaCerereNoua(unique_ptr<CerereReparatie> cr);
    void updateSimulare(); 

    
    const vector<unique_ptr<CerereReparatie>>& getFinalizate() { return cereri_finalizate; }
    
};

Tehnician* CelMaiBunTehnician(const string tipCautat,const string marcaCautata,const vector<unique_ptr<Angajat>>& lista_angajati);