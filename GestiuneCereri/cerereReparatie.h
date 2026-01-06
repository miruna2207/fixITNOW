#pragma once
#include <string>
#include <memory>
#include <ctime>
#include <iostream>
#include "../GestiuneElectrocasnice/GestiuneElectrocasnice.h"
#include "../GestiuneAngajati/GestiuneAngajati.h"

using namespace std;

class CerereReparatie {
private:
    const int cerereID;
    unique_ptr<Electrocasnic> aparat; 
    string numeClient;
    int complexitate;
    int durata_reparatie;
    int timp_ramas;
    double pret_reparatie;
    Tehnician* tehnician_alocat = nullptr;
    static int nextID;

public:
    
    CerereReparatie(unique_ptr<Electrocasnic> e, const string nume, int comp);
    
   
    CerereReparatie(const CerereReparatie&) = delete;
    CerereReparatie& operator=(const CerereReparatie&) = delete;

    
    CerereReparatie(CerereReparatie&&) = default;

    int getID() const;
    string get_nume_client() const { return numeClient; }
    int get_timp_ramas() const;
    int get_durata_reparatie() const;
    double get_pret_reparatie() const;
    void alocaTehnician(Tehnician* t);
    void proceseazaTic();
    bool esteFinalizata() const;
    bool esteProcesata() const;
    Electrocasnic* get_aparat() const;
    Tehnician* get_tehnician_alocat() const;

    void afisare(ostream&);
    
};