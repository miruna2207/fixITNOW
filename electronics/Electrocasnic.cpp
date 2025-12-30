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

void Electrocasnic::afiseaza() const{
    cout<<"marca:"<<marca;
    cout<<" model:"<<model;
    cout<<" an:"<<an_fabricatie<<" pret_catalog:"<<pret_catalog;
};