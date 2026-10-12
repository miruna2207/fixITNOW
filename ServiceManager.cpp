#include "ServiceManager.h"
#include <iostream>

using namespace std;

/* ================= Constructor & Singleton ================= */

ServiceManager::ServiceManager()
{
    ordinAngajati = make_unique<GestiuneAngajati>();
    ordinElectrocasnice = make_unique<GestiuneElectrocasnice>();
    ordinCereri = make_unique<GestiuneCereri>();
    ordinRaport = make_unique<GestiuneRaportari>();
}

ServiceManager &ServiceManager::getInstance()
{
    static ServiceManager instance;
    return instance;
}

/* ================= Getteri ================= */

IGestiuneAngajati &ServiceManager::angajati()
{
    return *ordinAngajati;
}

IGestiuneElectrocasnice &ServiceManager::electrocasnice()
{
    return *ordinElectrocasnice;
}

IGestiuneCereri &ServiceManager::cereri()
{
    return *ordinCereri;
}

IGestiuneRaportari &ServiceManager::raport()
{
    return *ordinRaport;
}

const vector<unique_ptr<CerereReparatie>> &ServiceManager::getFinalizate()
{
    return cereri_finalizate;
}

const vector<unique_ptr<CerereReparatie>> &ServiceManager::getRejectate()
{
    return cereri_respinse;
}

const vector<unique_ptr<CerereReparatie>> &ServiceManager::getActive()
{
    return cereri_active;
}

const deque<unique_ptr<CerereReparatie>> &ServiceManager::getAsteptare()
{
    return coada_asteptare;
}

/* ================= Simulare ================= */

void ServiceManager::proceseazaCerereNoua(unique_ptr<CerereReparatie> cr)
{

    if (!cr || cr->get_aparat() == nullptr || !angajati().echipaCompleta())
        return;

    string tip = cr->get_aparat()->get_tip();
    string marca = cr->get_aparat()->get_marca();

    bool esteInCatalog =
        electrocasnice().esteModelReparabil(
            tip,
            marca,
            cr->get_aparat()->get_model());

    if (!esteInCatalog)
    {
        cout << "[Receptioner] Cerere respinsa: Modelul nu este in catalog.\n";
        cereri_respinse.push_back(move(cr));
        return;
    }

    Tehnician *tehnician_alocat =
        CelMaiBunTehnician(tip, marca, angajati().get_lista_angajati());

    if (tehnician_alocat != nullptr)
    {
        cr->alocaTehnician(tehnician_alocat);
        tehnician_alocat->addCerere(*cr);
        cout << "[Receptioner] Cererea " << cr->getID()
             << " asignata lui: " << tehnician_alocat->get_nume() << endl;
        cereri_active.push_back(move(cr));
    }
    else
    {
        cout << "[Receptioner] Niciun tehnician disponibil. Cererea "
             << cr->getID() << " in asteptare.\n";
        coada_asteptare.push_back(move(cr));
    }
}

void ServiceManager::updateSimulare()
{
    cout << "\n=== UPDATE SIMULARE ===" << endl;

    for (auto it = cereri_active.begin(); it != cereri_active.end();)
    {
        (*it)->proceseazaTic();

        if ((*it)->esteFinalizata())
        {
            Tehnician *t_liber = (*it)->get_tehnician_alocat();

            cout << "[TERMINAT] Tehnicianul "
                 << t_liber->get_nume()
                 << " a terminat ID " << (*it)->getID() << endl;

            t_liber->finishCerere();
            cereri_finalizate.push_back(move(*it));
            it = cereri_active.erase(it);

            for (auto it_coada = coada_asteptare.begin();
                 it_coada != coada_asteptare.end();)
            {

                string tip = (*it_coada)->get_aparat()->get_tip();
                string marca = (*it_coada)->get_aparat()->get_marca();

                Tehnician *t =
                    CelMaiBunTehnician(
                        tip, marca, angajati().get_lista_angajati());

                if (t != nullptr)
                {
                    unique_ptr<CerereReparatie> c = move(*it_coada);
                    it_coada = coada_asteptare.erase(it_coada);

                    c->alocaTehnician(t);
                    t->addCerere(*c);
                    cereri_active.push_back(move(c));
                }
                else
                {
                    ++it_coada;
                }
            }
        }
        else
        {
            cout << "Tehnician "
                 << (*it)->get_tehnician_alocat()->get_nume()
                 << " lucreaza la ID " << (*it)->getID()
                 << " timp ramas:" << (*it)->get_timp_ramas() << endl;
            ++it;
        }
    }

    afiseaza_coada_asteptare();
}

/* ================= Utilitare ================= */

Tehnician *CelMaiBunTehnician(const string tip, const string marca,
                              const vector<unique_ptr<Angajat>> &lista)
{
    Tehnician *ales = nullptr;
    int minim_timp = 100;
    for (auto a = lista.begin(); a != lista.end(); a++)
    {
        if ((*a)->get_tip() == "Tehnician")
        {
            Tehnician *t = static_cast<Tehnician *>((*a).get());
            if (t->CanRepair(tip, marca) && t->get_nr_cereri_active() < 3)
            {
                if (ales == nullptr || t->get_timp_total() < minim_timp)
                {
                    minim_timp = t->get_timp_total();
                    ales = t;
                }
            }
        }
    }
    return ales;
}

bool ServiceManager::cereriInSistem() const
{
    if (cereri_active.empty() && !coada_asteptare.empty())
        cout << "Vezi ca ai cereri blocate in asteptare(motiv: catalog contine modele pentru care nu exista tehnicieni specializati)\n";

    return cereri_active.empty();
}

void ServiceManager::afiseaza_coada_asteptare() const
{
    cout << "Id Cereri in asteptare: ";
    for (auto c = coada_asteptare.begin(); c != coada_asteptare.end(); c++)
        cout << (*c)->getID() << " ";
    cout << endl;
}
