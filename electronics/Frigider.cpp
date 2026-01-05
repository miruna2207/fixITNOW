#include "Frigider.h"

Frigider::Frigider(const string brand,const string mod,int an,double price,bool c)
                    :Electrocasnic(brand,mod,an,price),congelator(c){};

void Frigider::afiseaza() const{
    Electrocasnic::afiseaza();
    if(congelator)
        cout<<" are congelator\n";
    else
        cout<<"n-are congelator\n";
}

string  Frigider::get_tip() const{
        return "Frigider";
    }