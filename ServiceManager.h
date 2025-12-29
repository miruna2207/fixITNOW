#pragma once
#include "GestiuneAngajati.h"

class ServiceManager {
private:
    unique_ptr<IGestiuneAngajati> ordinAngajati;

    ServiceManager() {
        ordinAngajati = make_unique<GestiuneAngajati>();
    }

public:
    static ServiceManager& getInstance() {
        static ServiceManager instance;
        return instance;
    }

    IGestiuneAngajati& angajati() { return *ordinAngajati; }

    
    //IGestiuneElectrocasnice& electrocasnice();
};