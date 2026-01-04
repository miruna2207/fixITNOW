#include "cerereReparatie.h"
int CerereReparatie::nextID = 1;
time_t t = time(nullptr);
tm *now = localtime(&t);
int anul_curent = now->tm_year + 1900;
CerereReparatie::CerereReparatie(Electrocasnic* e,const string nume,int complexitate):
    cerereID(nextID),aparat(e), numeClient(nume){
        int vechime = anul_curent - e->get_an_fabricatie();
        if( complexitate != 0){
            timp_ramas = durata_reparatie = vechime * complexitate ;
            pret_reparatie = e->get_pret_catalog() * durata_reparatie;
        }
        else{
            timp_ramas =durata_reparatie = pret_reparatie = 0;
        }
        

}

bool CerereReparatie::esteProcesata() const{
    return tehnician_alocat != nullptr;
};

void CerereReparatie::alocaTehnician(Tehnician* t){
    tehnician_alocat = t;
};

 void CerereReparatie::proceseazaTic(){
    if(!esteFinalizata())
        timp_ramas--;
 };

  bool CerereReparatie::esteFinalizata() const{
    return timp_ramas == 0 && esteProcesata(); 
  };

  int CerereReparatie::getID() const{
    return cerereID;
  };

   int CerereReparatie::get_timp_ramas() const{
    return timp_ramas;
   };

   int CerereReparatie::get_pret_reparatie() const{
    return pret_reparatie;
   };

   Tehnician* CerereReparatie::get_tehnician_alocat() const{
        if(tehnician_alocat == nullptr)
            cout<<" nu este asignat un tehnician!\n";
            
        return tehnician_alocat;
   };

   Electrocasnic* CerereReparatie::get_aparat() const{
        return aparat;
   }


   void CerereReparatie::modifica_depunere_cerere(time_t acum){
        depunerere_cerere = acum;
   };