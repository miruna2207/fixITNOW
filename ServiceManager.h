#pragma once
#include <queue>
#include <vector>
#include <memory>
#include "electronics/cerereReparatie.h"
#include "GestiuneElectrocasnice/GestiuneElectrocasnice.h"
class ServiceManager {
private:
    unique_ptr<IGestiuneAngajati> ordinAngajati;
    unique_ptr<IGestiuneElectrocasnice> ordinElectrocasnice;
    
    vector<unique_ptr<CerereReparatie>> cereri_active;
    queue<unique_ptr<CerereReparatie>> coada_asteptare;
    vector<unique_ptr<CerereReparatie>> cereri_finalizate;
    vector<unique_ptr<CerereReparatie>> cereri_respinse;

    ServiceManager() {
        ordinAngajati = make_unique<GestiuneAngajati>();
        ordinElectrocasnice = make_unique<GestiuneElectrocasnice>();
    }

public:
    static ServiceManager& getInstance() {
        static ServiceManager instance;
        return instance;
    }

     IGestiuneAngajati& angajati() { return *ordinAngajati; }
    IGestiuneElectrocasnice& electrocasnice() { return *ordinElectrocasnice;};
    
    void proceseazaCerereNoua(CerereReparatie& cr);
    void updateSimulare(int TIC); 

    
    const vector<unique_ptr<CerereReparatie>>& getFinalizate() { return cereri_finalizate; }
    
};

Tehnician* CelMaiBunTehnician(string tipCautat,string marcaCautata,vector<unique_ptr<Angajat>>& lista_angajati);