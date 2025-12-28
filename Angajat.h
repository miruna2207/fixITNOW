#pragma once
#include <string>
#include <ctime>
#include <fstream>
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
    bool isCNPValid() const;
    void verify_angajat() const;

public:
    Angajat();
    Angajat(const string name,const string pronum,const string code,const string date ,const string city);
    void change_name(const string buff);
    virtual ~Angajat() = default;
    double virtual get_Salariu();
  //  void virtual afisare() const = 0;
};
