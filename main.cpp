#include "ServiceManager.h"

int main() {
    auto& service = ServiceManager::getInstance();

    // 1. Test Incarcare din Fisier (cu erori controlate)
    cout << "--- Incarcare angajati din fisier ---\n";
    service.angajati().incarcaDinFisier("angajati.csv");

    // 2. Test Afisare
    cout << "\n--- Lista angajati incarcati ---\n";
    service.angajati().afisareToti();

    // 3. Test Modificare Nume
    cout << "\n--- Test Modificare Nume ---\n";
    service.angajati().modificaNume("6051212410041", "Popescu");
    
    // 4. Test Stergere
    cout << "\n--- Test Stergere Angajat ---\n";
    service.angajati().stergeAngajat("5001010410036");

    // 5. Afisare finala
    cout << "\n--- Lista finala ---\n";
    service.angajati().afisareToti();

    return 0;
}