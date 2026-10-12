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

Receptioner::Receptioner(const string n,const string p,const string c,const string d,const string o)
                                                                :Angajat(n,p,c,d,o){

};

void Receptioner::afiseaza(ostream& dev) const {
    Angajat::afiseaza(dev); 
}

void Receptioner::inregistreazaCerere(std::unique_ptr<CerereReparatie> cr) {
    if (!cr) return; 

    id_cereri_gestionate.push_back(cr->getID());
    cr->add_timp_reparatie();

    ServiceManager::getInstance().proceseazaCerereNoua(std::move(cr));
}


