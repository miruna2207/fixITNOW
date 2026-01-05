#include "Supervizor.h"

Supervizor::Supervizor(const string n,const string p,const string c,const string d,const string o):Angajat(n,p,c,d,o){

};

void Supervizor::afiseaza(ostream& file) const{
    Angajat::afiseaza(file);
}

 string Supervizor::get_tip() const{
    return "Supervizor";
 }

 double Supervizor::get_Salariu() {
    return Angajat::get_Salariu() + 4000/5;
 };