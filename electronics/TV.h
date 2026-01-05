#pragma once
#include "Electrocasnic.h"

class TV: public Electrocasnic{
    double diag = 0;
    string unitate;
    public:
    TV() = default;
    TV(const string brand,const string mod,int an,double price,double d,string u);
    string get_tip() const override;
    void afiseaza(ostream&) const override;
};