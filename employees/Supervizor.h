#include "Angajat.h"
 class Supervizor:public Angajat{
    public:
    Supervizor() = default;
    Supervizor(const string n,const string p,const string c,const string d,const string o);
    void afiseaza()const override;
 };