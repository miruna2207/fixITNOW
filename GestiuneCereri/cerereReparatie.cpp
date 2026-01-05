#include "cerereReparatie.h"

int CerereReparatie::nextID = 1;

CerereReparatie::CerereReparatie(unique_ptr<Electrocasnic> e, const string nume, int comp) :
    cerereID(nextID++), aparat(std::move(e)), numeClient(nume), complexitate(comp) {
    
    time_t t = time(nullptr);
    tm *now = localtime(&t);
    int anul_curent = now->tm_year + 1900;

    if (aparat) { 
        int vechime = anul_curent - aparat->get_an_fabricatie();
        if (complexitate > 0) {
            durata_reparatie = vechime * complexitate;
            timp_ramas = durata_reparatie;
            pret_reparatie = aparat->get_pret_catalog() * (durata_reparatie / 10.0 + 1); // Exemplu calcul pret
        } else {
            durata_reparatie = timp_ramas = pret_reparatie = 0;
        }
    } else {
        durata_reparatie = timp_ramas = pret_reparatie = 0;
    }
}

int CerereReparatie::getID() const { return cerereID; }
int CerereReparatie::get_timp_ramas() const { return timp_ramas; }
int CerereReparatie::get_durata_reparatie() const { return durata_reparatie; }
double CerereReparatie::get_pret_reparatie() const { return pret_reparatie; }
bool CerereReparatie::esteProcesata() const { return tehnician_alocat != nullptr; }
void CerereReparatie::alocaTehnician(Tehnician* t) { tehnician_alocat = t; }
void CerereReparatie::proceseazaTic() { if(timp_ramas > 0) timp_ramas--; }
bool CerereReparatie::esteFinalizata() const { return esteProcesata() && timp_ramas <= 0; }
Electrocasnic* CerereReparatie::get_aparat() const { return aparat.get(); }
Tehnician* CerereReparatie::get_tehnician_alocat() const { return tehnician_alocat; }