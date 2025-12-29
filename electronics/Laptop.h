#include "Electrocasnic.h"

class Laptop:public Electrocasnic{
    int RAM;
    public:
        string get_tip() const override{
            return "laptop";
        }
};