#include "Electrocasnic.h"

Electrocasnic::Electrocasnic(const string brand,const string mod,int an,double price):marca(brand)
                                                        ,model(mod),an_fabricatie(an),pret_catalog(price){};

string Electrocasnic::get_marca() const{
    return marca;
};

string Electrocasnic::get_model() const{
    return model;
};

int Electrocasnic::get_an_fabricatie() const{
    return an_fabricatie;
};

double Electrocasnic::get_pret_catalog() const{
    return pret_catalog;
}

void Electrocasnic::afiseaza(ostream& file) const{
    file<<marca<<" "<<model<<" "<<an_fabricatie<<" "<<pret_catalog;
};