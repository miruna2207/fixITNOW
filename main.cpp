#include <iostream>
#include <string>
#include <algorithm>
#include "ServiceManager.h"

using namespace std;

void meniuAngajati(ServiceManager &manager)
{
    int opt;
    do
    {
        cout << "\n--- GESTIUNE ANGAJATI ---" << endl;
        cout << "1. Adaugare angajat Fisier\n2. Modificare nume (dupa CNP)\n3. Stergere angajat\n";
        cout << "4. Cautare dupa CNP (Date + Salariu)\n5. Afisare lista completa\n6.Adaugare angajat manual\n0. Revenire\nAlegeti: ";
        cin >> opt;
        string cnp, nume;
        switch (opt)
        {
        case 1:
            manager.angajati().incarcaDinFisier("tests/set7/angajati_7.csv");
           //manager.angajati().incarcaDinFisier("tests/verifica_angajati/angajati_rau.csv");
            
            break;
        case 2:
            cout << "CNP: ";
            cin >> cnp;
            cout << "Nume nou: ";
            cin >> nume;
            manager.angajati().modificaNume(cnp, nume);
            break;
        case 3:
            cout << "CNP: ";
            cin >> cnp;
            manager.angajati().stergeAngajat(cnp);
            break;
        case 4:
        {
            cout << "CNP: ";
            cin >> cnp;
            Angajat *a = manager.angajati().gasesteDupaCNP(cnp);
            if (a)
            {
                a->afiseaza(cout);
                cout << " " << a->get_Salariu() << " RON\n";
            }
            else
                cout << "Nu am gasit angajatul.\n";
            break;
        }
        case 5:
            manager.angajati().afisareToti();
            break;
        case 6:
            manager.angajati().adaugaAngajat();
            break;
        }
    } while (opt != 0);
}

void meniuElectrocasnice(ServiceManager &manager)
{
    int opt;
    do
    {
        cout << "\n--- GESTIUNE ELECTROCASNICE ---" << endl;
        cout << "1. Adaugare model Fisier(Catalog)\n2. Stergere model\n3. Afisare catalog reparabile\n";
        cout << "4. Afisare aparate FINALIZATE (detalii)\n5.Adauga model manual\n";
        cout << "6.Afisare top electrocasnice rejectate\n0. Revenire\nAlegeti: ";
        cin >> opt;
        switch (opt)
        {
        case 1:
        {
            // manager.electrocasnice().incarcaModeleDinFisier("tests/verifica_electrocasnice/catalog_rau_2.csv");

            manager.electrocasnice().incarcaModeleDinFisier("tests/set7/catalog_7.csv");
            break;
        }
        case 2:
        {
            string tip, marca, model;
            cout << "tip =";
            cin >> tip;
            cout << " marca=";
            cin >> marca;
            cout << " model=";
            cin >> model;
            manager.electrocasnice().stergeModel(tip, marca, model);
            break;
        }
        case 3:
        {
            manager.electrocasnice().afisareCatalog();
            break;
        }
        case 4:
        {
            try{
                if(manager.getFinalizate().empty())
                    throw runtime_error("nu exista nicio cerere finalizata in sistem!");
                else{
                    cout<<"\n\n ========Aparate finalizate ============";
                    for (auto &c : manager.getFinalizate())
                    {
                        c->get_aparat()->afiseaza(cout);
                        cout << endl;
                    }
                    cout<<"\n\n =======================================\n\n";
                }
            }catch(const exception& e){
                cout<<"\n\n"<<e.what()<<"\n\n";
            }
            
            break;
        }
        case 5:
        {
            manager.electrocasnice().adaugaModelManual();
            break;
        }
        case 6:
        try {
            manager.raport().raportAparateRespinse(manager.getRejectate());
        }catch(const exception& e){
            cout<<"\n\n"<<e.what()<<"\n\n";
        }
        }
    } while (opt != 0);
}

void meniuRapoarte(ServiceManager &manager)
{
    int opt;
    do
    {
        cout << "\n\n";
        cout << "========== RAPOARTE ==========\n";
        cout << "1.Top 3 Angajati cu cele mai mari Salarii\n2.Tehnician cu cea mai lunga durata reparatie\n";
        cout << "3.Afiseaza cereri in asteptare ordonate\n0.Pentru a iesi din meniu\n";
        cout << "==============================\n";
        cout << "Alegeti optiunea: ";

        cin >> opt;
        switch (opt)
        {
        case 1:
            try
            {
                manager.raport().raportTopSalariuAngajati(
                    manager.angajati().get_lista_angajati());
            }
            catch (const exception &e)
            {
                cerr << "[EROARE] " << e.what() << endl;
            }
            break;

        case 2:
            try
            {
                manager.raport().Angajat_Longest_Reparatie(
                    manager.getFinalizate(),
                    manager.getActive(),
                    manager.getAsteptare());
            }
            catch (const exception &e)
            {
                cerr << "[EROARE] " << e.what() << endl;
            }
            break;

        case 3:
            try
            {
                manager.raport().Cereri_Asteptare_Ordonate(
                    manager.getAsteptare());
            }
            catch (const exception &e)
            {
                cerr << "[EROARE] " << e.what() << endl;
            }
            break;
        }
    }while (opt != 0);
}
            
    
    void meniuProcesare(ServiceManager & manager, int &TIC)
    {
        int opt;
        do
        {
            cout << "\n--- PROCESARE CERERI ---" << endl;
            cout << "1. Incarca cereri din fisier\n2. Adauga cerere manual\n";
            cout << "3. START Simulare Completa (Loop automat)\n4. Ruleaza 1 TIC\n0. Revenire\nAlegeti: ";
            cin >> opt;
            switch (opt)
            {
            case 1:
             //manager.cereri().incarcaDinFisier("tests/verifica_cereri/cereri_rele_1.csv");
                manager.cereri().incarcaDinFisier("tests/set7/cereri_7.csv");
                break;
            case 2:
                manager.cereri().adaugaManual();
                break;
            case 3:
                if (!manager.angajati().echipaCompleta())
                    break;
                while (!manager.cereriInSistem())
                {
                    cout << "\n--- TIC " << TIC << " ---" << endl;
                    manager.updateSimulare();
                    TIC++;
                }
                break;
            case 4:
                if (manager.angajati().echipaCompleta())
                {
                    manager.updateSimulare();
                    TIC++;
                }
                break;
            }
        } while (opt != 0);
    }

    int main()
    {
        ServiceManager &manager = ServiceManager::getInstance();
        int TIC = 1;
        int optiune;

        do
        {
            cout << "\n========== SERVICE ELECTRONICE - MENIU PRINCIPAL ==========" << endl;
            cout << "1. Gestiune Angajati" << endl;
            cout << "2. Gestiune Electrocasnice" << endl;
            cout << "3. Procesare Cereri & Simulare" << endl;
            cout << "4. Rapoarte" << endl;
            cout << "0. Iesire Program" << endl;
            cout << "==========================================================" << endl;
            cout << "Alege categoria: ";
            cin >> optiune;

            switch (optiune)
            {
            case 1:
                meniuAngajati(manager);
                break;
            case 2:
                meniuElectrocasnice(manager);
                break;
            case 3:
                meniuProcesare(manager, TIC);
                break;
            case 4:
                meniuRapoarte(manager);
                break;
            case 0:
                cout << "Inchidere program..." << endl;
                break;
            default:
                cout << "Optiune invalida!" << endl;
            }
        } while (optiune != 0);

        return 0;
    }