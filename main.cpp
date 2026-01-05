#include <iostream>
#include <vector>
#include <string>
#include "ServiceManager.h"

using namespace std;

int main()
{
    ServiceManager &manager = ServiceManager::getInstance();
    int optiune;
    int TIC = 1;

    do
    {
        cout << "\n======= SERVICE ELECTRONICE - MENU =======" << endl;
        cout << "1. Incarca cereri (BUNE)" << endl;
        cout << "2. Incarca cereri (RELE - Test Error Handling)" << endl;
        cout << "3. Incarca cereri (PARTIALE)" << endl;
        cout << "4. Adauga cerere MANUAL" << endl;
        cout << "5. Ruleaza 1 TIC Simulare" << endl;
        cout << "6. Ruleaza simulare completa" << endl;
        cout << "7. Incarca angajati (BUNE)" << endl;
        cout << " 8. Incarca electrocasnice catalog( BUNE)" << endl;
        cout << "0. Iesire" << endl;
        cout << "Alege optiunea: ";
        cin >> optiune;

        try
        {
            switch (optiune)
            {
            case 1:
                manager.cereri().incarcaDinFisier("tests/cereri_bune_1.csv");
                break;
            case 2:
                manager.cereri().incarcaDinFisier("tests/cereri_rele_1.csv");
                break;
            case 3:
                manager.cereri().incarcaDinFisier("tests/cereri_rele_2.csv");
                break;
            case 4:
                manager.cereri().adaugaManual();
                break;
            case 5:
                cout << "\n--- EXECUTIE TIC " << TIC << " ---" << endl;
                manager.updateSimulare(); 
                TIC++;
                break;
            case 6:
                cout << "Simulare automata pornita..." << endl;

                while (!manager.cereriInSistem())
                {
                    cout << "\n--- [TIC " << TIC << "] ---" << endl;
                    manager.updateSimulare();
                    TIC++;
                }

                cout << "\n>>> SIMULARE FINALIZATA <<<" << endl;
                cout << "Toate cererile au fost procesate. Total TIC-uri scurse: " << TIC - 1 << endl;
                break;

            case 7:
                manager.angajati().incarcaDinFisier("tests/angajati.csv");
                break;

            case 8:
                manager.electrocasnice().incarcaModeleDinFisier("tests/electrocasnice_bun_1.csv");
                break;
            case 0:
                cout << "Iesire program..." << endl;
                break;
            default:
                cout << "Optiune invalida!" << endl;
            }
        }
        catch (const exception &e)
        {
            cout << "CRITICAL ERROR in Main: " << e.what() << endl;
        }
    } while (optiune != 0);

    return 0;
}