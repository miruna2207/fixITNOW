#include "TV.h"

TV::TV(const string brand,const string mod,int an,double price,double d,string u)
:Electrocasnic(brand,mod,an,price),diag(d),unitate(u){};

string TV::get_tip() const{
    return "TV";
}

void TV::afiseaza(ostream& file) const{
    Electrocasnic::afiseaza(file);
    cout<<" "<<diag<<" "<<unitate;
};