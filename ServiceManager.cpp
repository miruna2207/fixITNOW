#include "ServiceManager.h"

void ServiceManager::proceseazaCerereNoua(unique_ptr<CerereReparatie> cr) {

    if (!cr || cr->get_aparat() == nullptr || !angajati().echipaCompleta()) return;

    string tip = cr->get_aparat()->get_tip();
    string marca = cr->get_aparat()->get_marca();
    
    bool esteInCatalog = electrocasnice().esteModelReparabil(tip, marca, cr->get_aparat()->get_model());

    if (!esteInCatalog) {
        cout << "[Receptioner] Cerere respinsa: Modelul nu este in catalog.\n";
        cereri_respinse.push_back(std::move(cr)); 
        return;
    }

    Tehnician* tehnician_alocat = CelMaiBunTehnician(tip, marca, angajati().get_lista_angajati());
    
    if (tehnician_alocat != nullptr) {
        cr->alocaTehnician(tehnician_alocat);
        tehnician_alocat->addCerere(*cr);
        cout << "[Receptioner] Cererea " << cr->getID() << " asignata lui: " << tehnician_alocat->get_nume() << endl;
        cereri_active.push_back(std::move(cr)); 
    } else {
        cout << "[Receptioner] Niciun tehnician disponibil. Cererea " << cr->getID() << " in asteptare.\n";
        coada_asteptare.push_back(std::move(cr)); 
    }
}

void ServiceManager::updateSimulare() {
    cout << "\n=== UPDATE SIMULARE ===" << endl;
    
    for (auto it = cereri_active.begin(); it != cereri_active.end(); ) {
        (*it)->proceseazaTic();

        if ((*it)->esteFinalizata()) {
            Tehnician* t_liber = (*it)->get_tehnician_alocat();
            cout << "[TERMINAT] Tehnicianul " << t_liber->get_nume() 
                 << " a terminat ID " << (*it)->getID() 
                 << ". Acum are " << t_liber->get_nr_cereri_active() - 1 << " cereri active." << endl;
            
            t_liber->finishCerere();
            cereri_finalizate.push_back(std::move(*it));
            it = cereri_active.erase(it);

        
            if (!coada_asteptare.empty()) {
                cout << "[COADA] " << coada_asteptare.size() << " cereri in asteptare" << endl;
                

                for (auto it_coada = coada_asteptare.begin(); it_coada != coada_asteptare.end(); ) {
                    string tip = (*it_coada)->get_aparat()->get_tip();
                    string marca = (*it_coada)->get_aparat()->get_marca();
                    
                    Tehnician* tehnician_disponibil = CelMaiBunTehnician(
                        tip, marca, angajati().get_lista_angajati()
                    );
                    
                    if (tehnician_disponibil != nullptr) {
                        cout << "[ALOCARE] Tehnician " << tehnician_disponibil->get_nume()
                             << " poate prelua ID " << (*it_coada)->getID()
                             << " (" << tip << " " << marca << ")" << endl;
                        
                        unique_ptr<CerereReparatie> cerereDeAlocat = std::move(*it_coada);
                        it_coada = coada_asteptare.erase(it_coada);
                        
                        cerereDeAlocat->alocaTehnician(tehnician_disponibil);
                        tehnician_disponibil->addCerere(*cerereDeAlocat);
                        cout << "[ALOCAT] " << tehnician_disponibil->get_nume() 
                             << " a preluat ID " << cerereDeAlocat->getID() << endl;
                        cereri_active.push_back(std::move(cerereDeAlocat));
                    } else {
                        ++it_coada;
                    }
                }
            }
        } else {
            cout << "Tehnician " << (*it)->get_tehnician_alocat()->get_nume() 
                 << " lucreaza la ID " << (*it)->getID() 
                 << " timp ramas:" << (*it)->get_timp_ramas() << endl;
            ++it;
        }
    }
    afiseaza_coada_asteptare();
}
 


Tehnician* CelMaiBunTehnician(const string tip, const string marca, const vector<unique_ptr<Angajat>>& lista) {
    Tehnician* ales = nullptr;
    int minim_timp = -1;

    for (auto a = lista.begin(); a!= lista.end() ; a++) {
        if ((*a)->get_tip() == "Tehnician") {
            Tehnician* t = static_cast<Tehnician*>((*a).get());
            if (t->CanRepair(tip, marca) && t->get_nr_cereri_active() < 3) {
                if (ales == nullptr || t->get_timp_total() < minim_timp) {
                    minim_timp = t->get_timp_total();
                    ales = t;
                }
            }
        }
    }
    return ales;
}

bool ServiceManager::cereriInSistem() const {
    if( cereri_active.empty() && !coada_asteptare.empty() )
        cout<<"Vezi ca ai in catalog un aparat pe care tehnicienii nu stiu sa ti-l repare verfica raport cereri in asteptare sa vezi cartita\n";
    return cereri_active.empty() ;
}

void ServiceManager::afiseaza_coada_asteptare() const{
    cout<<"Id Cereri in asteptare : ";
    for( auto cerere = coada_asteptare.begin(); cerere != coada_asteptare.end(); cerere++ )
        cout<<(*cerere)->getID()<<" ";
    cout<<endl;
};