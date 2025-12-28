#include "Angajat.h"
 class Supervizor:public Angajat{
    public:
    Supervizor() = default;
    friend ostream& operator<<(ostream&,const Supervizor s);
 };