#pragma once
#include "Electrocasnic.h"

class Frigider:public Electrocasnic{
    bool congelator;
    public:
    Frigider() = default;
    Frigider(const string brand,const string mod,int an,double price,bool c);
    void afiseaza(ostream&) const override;
    string  get_tip() const override;
};