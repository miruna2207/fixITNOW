#pragma once
#include<iostream>
#include<string>
using namespace std;

class Angajat{
    protected:
    int static nr;
    string nume;
    string prenume;
    string CNP;
    string data_angajare;
    string oras_domiciliu;
    public:
    Angajat() ;
    virtual ~Angajat() ;

};

bool isValid_CNP(string cod){
    if(cod.length() != 13)
        return 0;
}