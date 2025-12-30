#pragma once
#include "Electrocasnic.h"

class Masina_Spalat:public Electrocasnic{
    int capacitate;
    public:
    string get_tip() const override;

    Masina_Spalat() = default;
    Masina_Spalat(const string brand,const string mod,int an,double price,int c);
    void afiseaza() const override;
};