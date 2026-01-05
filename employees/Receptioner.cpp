#include "Receptioner.h"
#include "../ServiceManager.h"

string Receptioner::get_tip() const{
    return "Receptioner";
}

bool Receptioner::is_id_cerere(int val){
    for( vector<int>::iterator i = id_cereri_gestionate.begin() ; i != id_cereri_gestionate.end(); i++){
        if ( *i == val )
            return true;
    }
    return false;
};

double Receptioner::get_Salariu()  {
        return Angajat::get_Salariu();
    };

Receptioner::Receptioner(const string n,const string p,const string c,const string d,const string o):Angajat(n,p,c,d,o){

};

void Receptioner::afiseaza() const {
    Angajat::afiseaza(); // Aici e corect cum ai scris
}

void Receptioner::inregistreazaCerere(std::unique_ptr<CerereReparatie> cr) {
    if (!cr) return; // Verificare de siguranță

    // 1. Reținem ID-ul în lista recepționerului înainte de a muta obiectul
    id_cereri_gestionate.push_back(cr->getID());

    // 2. Modificăm data (asigură-te că metoda există în CerereReparatie.h)
    // Dacă nu ai apucat să o adaugi, folosește cr->get_aparat() etc.
    // cr->modifica_depunere_cerere(time(nullptr)); 

    // 3. TRANSFERĂM cererea către ServiceManager
    // După acest apel, 'cr' devine null în această funcție!
    ServiceManager::getInstance().proceseazaCerereNoua(std::move(cr));
}


