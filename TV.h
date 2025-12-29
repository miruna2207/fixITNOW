#pragma once
#include "Electrocasnic.h"

class TV: public Electrocasnic{
    double diag = 0;
    string unitate;
    public:
    string get_tip() const override{
        return "TV";
    };
};