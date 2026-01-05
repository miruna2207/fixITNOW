#include "ServiceManager.h"

void ServiceManager::proceseazaCerereNoua(unique_ptr<CerereReparatie> cr) {
    if (!cr || cr->get_aparat() == nullptr) return;

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
        cereri_active.push_back(std::move(cr)); // Mutam in active
    } else {
        cout << "[Receptioner] Niciun tehnician disponibil. Cererea " << cr->getID() << " in asteptare.\n";
        coada_asteptare.push(std::move(cr)); // Mutam in coada
    }
}

void ServiceManager::updateSimulare() {
    for (auto it = cereri_active.begin(); it != cereri_active.end(); ) {
        (*it)->proceseazaTic();

        if ((*it)->esteFinalizata()) {
            Tehnician* t_liber = (*it)->get_tehnician_alocat();
            cout << "Tehnicianul " << t_liber->get_nume() << " a terminat ID " << (*it)->getID() << endl;
            
            t_liber->finishCerere();
            cereri_finalizate.push_back(std::move(*it));
            it = cereri_active.erase(it);

            if (!coada_asteptare.empty()) {
                auto& prima = coada_asteptare.front();
                if (t_liber->CanRepair(prima->get_aparat()->get_tip(), prima->get_aparat()->get_marca())) {
                    unique_ptr<CerereReparatie> cerereDeAlocat = std::move(coada_asteptare.front());
                    coada_asteptare.pop();
                    
                    cerereDeAlocat->alocaTehnician(t_liber);
                    t_liber->addCerere(*cerereDeAlocat);
                    cout << "[SIM] " << t_liber->get_nume() << " a preluat ID " << cerereDeAlocat->getID() << endl;
                    cereri_active.push_back(std::move(cerereDeAlocat));
                }
            }
        } else {
            cout << "Tehnician " << (*it)->get_tehnician_alocat()->get_nume() << " lucreaza la ID " <<
             (*it)->getID() <<"timp ramas:"<<(*it)->get_timp_ramas() << endl;
            ++it;
        }
    }
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