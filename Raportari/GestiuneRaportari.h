#pragma once
#include "iRaport.h"
#include <deque>
class GestiuneRaportari:public IGestiuneRaportari{
   public: 
   void raportAparateRespinse(const vector<unique_ptr<CerereReparatie>>& respinse) override;

   void raportTopSalariuAngajati(const vector<unique_ptr<Angajat>>& lista_angajati) override;

   void Cereri_Asteptare_Ordonate(const deque<unique_ptr<CerereReparatie>>& cereriAsteptare ) override;

   void Angajat_Longest_Reparatie(const vector<unique_ptr<CerereReparatie>>& cereriFinalizate,
      const vector<unique_ptr<CerereReparatie>>& cereriActive, const deque<unique_ptr<CerereReparatie>>& cereriAsteptare) override; 
};
