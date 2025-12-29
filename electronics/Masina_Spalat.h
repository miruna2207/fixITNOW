#pragma once
#include "Electrocasnic.h"

class Masina_Spalat:public Electrocasnic{
    int capacitate;
    public:
    string get_tip() const override{
        return "Masina_Spalat";
    }
};