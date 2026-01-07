#include "Masina_Spalat.h"

string Masina_Spalat::get_tip() const {
        return "Masina_Spalat";
    }

Masina_Spalat::Masina_Spalat(const string brand,const string mod,int an,double price,int c)
:Electrocasnic(brand,mod,an,price),capacitate(c){};

void Masina_Spalat::afiseaza(ostream& file) const{
    Electrocasnic::afiseaza(file);
    file<<" ,"<<capacitate;
}
