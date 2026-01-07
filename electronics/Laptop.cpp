#include "Laptop.h"

string Laptop::get_tip() const {
            return "Laptop";
        }

 Laptop::Laptop(const string ma,const string mo, int an, double p,int r):Electrocasnic(ma,mo,an,p),RAM(r){};
 
 void Laptop::afiseaza(ostream& file) const{
    Electrocasnic::afiseaza(file);
    file<<" ,"<<RAM;
 };