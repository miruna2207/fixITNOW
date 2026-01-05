#pragma once
#include<iostream>
#include<vector>
using namespace std;

class Electrocasnic{
    protected:
    string marca{};
    string model{};
    int an_fabricatie = 0;
    double pret_catalog = 0;

    public:
    Electrocasnic() = default;
    Electrocasnic(const string brand,const string mod,int an,double price);
    virtual ~Electrocasnic() = default;

    string get_marca() const;
    string get_model() const;
    int get_an_fabricatie() const;
    double get_pret_catalog() const;
    virtual string get_tip() const = 0;
    virtual void afiseaza(ostream&) const;
};