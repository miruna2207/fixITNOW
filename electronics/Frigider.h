#pragma once
#include "Electrocasnic.h"

class Frigider:public Electrocasnic{
    bool congelator;
    public:
    string  get_tip() const override{
        return "frigider";
    }
};