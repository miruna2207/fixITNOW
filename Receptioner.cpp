#include "Receptioner.h"
void Receptioner::inregistreazaCerere(int id) {
        if(is_id_cerere(id))
            throw std::invalid_argument("Id-ul e deja inregistrat, id:"+id);
        id_cereri_gestionate.push_back(id);
    }

bool Receptioner::is_id_cerere(int val){
    for( vector<int>::iterator i = id_cereri_gestionate.begin() ; i != id_cereri_gestionate.end(); i++){
        if ( *i == val )
            return true;
    }
    return false;
};

double Receptioner::get_Salariu()  {
        return Angajat::get_Salariu();
    };