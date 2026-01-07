#pragma once
#include <deque>
#include <vector>
#include <memory>
#include "../GestiuneCereri/GestiuneCereri.h"
#include "../GestiuneAngajati/GestiuneAngajati.h"
#include "../GestiuneElectrocasnice/GestiuneElectrocasnice.h"
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

    ServiceManager() ;

public:
    static ServiceManager& getInstance() ;

    IGestiuneAngajati& angajati();
    IGestiuneElectrocasnice& electrocasnice() ;
    IGestiuneCereri& cereri() ;
    IGestiuneRaportari& raport() ;
    
    void proceseazaCerereNoua(unique_ptr<CerereReparatie> cr);
    void updateSimulare(); 
    void afiseaza_coada_asteptare() const;
    bool cereriInSistem() const;
    const vector<unique_ptr<CerereReparatie>>& getFinalizate() ;
    const vector<unique_ptr<CerereReparatie>>& getRejectate() ;
    const vector<unique_ptr<CerereReparatie>>& getActive() ;
    const deque<unique_ptr<CerereReparatie>>& getAsteptare() ;
    
};

Tehnician* CelMaiBunTehnician(const string tipCautat, const string marcaCautata,
                            const vector<unique_ptr<Angajat>>& lista_angajati);