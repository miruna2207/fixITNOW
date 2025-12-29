#include "Supervizor.h"

Supervizor::Supervizor(const string n,const string p,const string c,const string d,const string o):Angajat(n,p,c,d,o){

};

void Supervizor::afiseaza() const{
    Angajat::afiseaza();
}