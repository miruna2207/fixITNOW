#pragma once
#include <string>
#include <memory>
#include <ctime>
#include <iostream>

class Electrocasnic;
class Tehnician;
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
    time_t timp_inregistrare;
    Tehnician* tehnician_alocat = nullptr;
    static int nextID;

public:
    
    CerereReparatie(unique_ptr<Electrocasnic> e, const string nume, int comp);
    
   
    CerereReparatie(const CerereReparatie&) = delete;
    CerereReparatie& operator=(const CerereReparatie&) = delete;

    
    CerereReparatie(CerereReparatie&&) = default;
    void add_timp_reparatie();
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