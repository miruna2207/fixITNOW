#include "Tehnician.h"
 
bool Tehnician::is_there_competenta(const string t,const string m) const{
    for( auto i = specializari.begin() ; i !=specializari.end(); i++){
        if( (*i).tip == t && (*i).marca == m){
            return true;
        }
    }
    return false;
};

void Tehnician::addSpecializari(string tip, string marca) {
        if(is_there_competenta(tip,marca))
            throw std::invalid_argument(tip+" si "+marca+" este deja la tehnician\n");
        specializari.push_back({tip, marca});
    }

bool Tehnician::CanRepair(string tip, string marca) const {
       if(is_there_competenta(tip,marca))
            return true;
        else
            return false;
}

 double Tehnician::get_Salariu() {
        double baza = Angajat::get_Salariu(); 
        baza += (0.02 * valoare_reparatii); 
        return baza;
    }

void Tehnician::updateReparatii(double valoare) {
    valoare_reparatii += valoare;
    }

    Tehnician::Tehnician(const string n,const string p,const string c,const string d,const string o,vector<Competenta> co)
    :Angajat(n,p,c,d,o),specializari(co){

};

 void Tehnician::afiseaza() const {
    Angajat::afiseaza();
    for( auto i = specializari.begin();i != specializari.end();i++){
        cout<<"tip="<<i->tip<<" marca="<<i->marca<<endl;
    }
 };

    