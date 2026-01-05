#pragma once
#include "Electrocasnic.h"

class Laptop:public Electrocasnic{
    int RAM;
    public:
        Laptop() = default;
        Laptop(const string ma,const string mo, int an, double p,int r);
        string get_tip() const override;
        void afiseaza() const override;

};