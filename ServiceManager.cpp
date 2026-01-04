#include "ServiceManager.h"

void ServiceManager::proceseazaCerereNoua(CerereReparatie& cr) {
    string tip = cr.get_aparat()->get_tip();
    string marca = cr.get_aparat()->get_marca();
    
    bool esteInCatalog = electrocasnice().esteModelReparabil(tip, marca, cr.get_aparat()->get_model());

    if (!esteInCatalog) {
        cout << "[Receptioner] Cerere respinsa: Modelul nu este in catalog.\n";
        cereri_respinse.push_back(make_unique<CerereReparatie>(cr));
        return;
    }


    Tehnician* tehnician_alocat = CelMaiBunTehnician(tip,marca,(angajati().get_lista_angajati()));
      if ( tehnician_alocat != nullptr) {
        cr.alocaTehnician(tehnician_alocat);
        tehnician_alocat->addCerere(cr);
        cereri_active.push_back(make_unique<CerereReparatie>(cr));
        cout << "[Receptioner] Cererea " << cr.getID() << " asignata tehnicianului: " 
             << tehnician_alocat->get_nume() << endl;
    } else {
        coada_asteptare.push(make_unique<CerereReparatie>(cr));
        cout << "[Receptioner] Niciun tehnician disponibil pentru " << marca 
             << ". Cererea " << cr.getID() << " ramane in asteptare." << endl;
    }
  
}

   

Tehnician* CelMaiBunTehnician(string tipCautat,string marcaCautata,const vector<unique_ptr<Angajat>>& lista_angajati){
    Tehnician* celMaiBunTehnician = nullptr;
    int minim_cereri_total= -1;

    for (auto angajat = lista_angajati.begin(); angajat != lista_angajati.end(); angajat++) {
        Tehnician* t;
        if( (*angajat)->get_tip() == "Tehnician")
            t = (Tehnician*) ((*angajat).get());
        else 
            t = nullptr;
        
        if (t && t->CanRepair(tipCautat, marcaCautata)) {
            if (t->get_nr_cereri_active() < 3) {

                if (celMaiBunTehnician == nullptr || t->get_nr_cereri_total() < minim_cereri_total) {
                    minim_cereri_total = t->get_nr_cereri_total();
                    celMaiBunTehnician = t;
                }
            }
        }
    }
    return celMaiBunTehnician;
};

void ServiceManager::updateSimulare(int TIC) {

    for (auto it = cereri_active.begin(); it != cereri_active.end(); ) {
        (*it)->proceseazaTic();

        if ((*it)->esteFinalizata()) {
            cout << " Finalizat ID: " << (*it)->getID() <<" de tehnician "<<(*it)->get_tehnician_alocat()->get_nume()<<endl;
            (*it)->get_tehnician_alocat()->finishCerere();
            
            cereri_finalizate.push_back(move(*it));
            it = cereri_active.erase(it);
            
            if (!coada_asteptare.empty()) {
                auto cerereDinCoada = move(coada_asteptare.front());
                coada_asteptare.pop();
                
                this->proceseazaCerereNoua(*(cerereDinCoada));
            }
        } else {
            ++it;
        }
    }
}