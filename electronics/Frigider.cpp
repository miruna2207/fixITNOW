#include "Frigider.h"

Frigider::Frigider(const string brand,const string mod,int an,double price,bool c)
                    :Electrocasnic(brand,mod,an,price),congelator(c){};

void Frigider::afiseaza(ostream& file) const{
    Electrocasnic::afiseaza(file);
    file<<" ,"<<congelator;
}

string  Frigider::get_tip() const{
        return "Frigider";
    }