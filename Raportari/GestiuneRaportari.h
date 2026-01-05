#pragma once
#include "iRaport.h"

class GestiuneRaportari:public IGestiuneRaportari{
   public: 
   void raportAparateRespinse(const vector<unique_ptr<CerereReparatie>>& respinse);
   void raportTopSalariuAngajati(const vector<unique_ptr<Angajat>>& lista_angajati);
};
