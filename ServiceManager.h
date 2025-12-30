#pragma once
#include "GestiuneElectrocasnice/GestiuneElectrocasnice.h"
#include "GestiuneAngajati/GestiuneAngajati.h"
#include<memory>

class ServiceManager {
private:
    unique_ptr<IGestiuneAngajati> ordinAngajati;
    unique_ptr<IGestiuneElectrocasnice> ordinElectrocasnice;
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
};

