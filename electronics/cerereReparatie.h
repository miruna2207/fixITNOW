#pragma once
#include "../GestiuneElectrocasnice/GestiuneElectrocasnice.h"
#include "../GestiuneAngajati/GestiuneAngajati.h"
#include<time.h>
#include<memory>


class CerereReparatie{
    protected:
    const int cerereID;
    Electrocasnic* aparat;
    string numeClient;
    time_t depunerere_cerere;
    int complexitate;
    int durata_reparatie;
    double pret_reparatie;
    Tehnician* tehnician_alocat = nullptr; 
    static int nextID;
    int timp_ramas = 0;

    public:
    CerereReparatie(Electrocasnic* e,const string,int);
    bool esteProcesata() const;
    void alocaTehnician(Tehnician* t);
    void proceseazaTic();
    bool esteFinalizata() const;
    void modifica_depunere_cerere(time_t);
    int getID() const;
    int get_timp_ramas() const;
    int get_pret_reparatie() const;
    Electrocasnic* get_aparat() const;
    Tehnician* get_tehnician_alocat() const;


};