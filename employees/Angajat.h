#pragma once
#include <string>
#include <ctime>
#include <fstream>
#include<iostream>
using namespace std;
class Angajat
{
protected:
    const int id;
    static int nextid;
    string nume{};
    string prenume{};
    string CNP{}; 
    string data_angajare{}; //ZZ.LL.AAAA
    string oras_domiciliu{};

    int get_vechime() const;
    void verify_angajat() const;

public:
    Angajat();
    Angajat(const string name,const string pronum,const string code,const string date ,const string city);
    void change_name(const string buff);
    virtual ~Angajat() = default;
    double virtual get_Salariu();
    void virtual afiseaza() const;
    string get_CNP() const;
    string get_nume() const;
    string get_prenume() const;
    virtual string get_tip() const = 0;
};


void verify_name(const string sir);
void verify_CNP(string CNP);
void verify_cifra_control(string CNP);
int get_varsta(const string cod);
