#include "ServiceManager.h"

int main() {
    auto& service = ServiceManager::getInstance();

    // // 1. Test Incarcare din Fisier (cu erori controlate)
    // cout << "--- Incarcare angajati din fisier ---\n";
    // service.angajati().incarcaDinFisier("angajati.csv");

    // // 2. Test Afisare
    // cout << "\n--- Lista angajati incarcati ---\n";
    // service.angajati().afisareToti();

    // // 3. Test Modificare Nume
    // cout << "\n--- Test Modificare Nume ---\n";
    // service.angajati().modificaNume("6051212410041", "Popescu");
    
    // // 4. Test Stergere
    // cout << "\n--- Test Stergere Angajat ---\n";
    // service.angajati().stergeAngajat("5001010410036");

    // // 5. Afisare finala
    // cout << "\n--- Lista finala ---\n";
    // service.angajati().afisareToti();

    cout << "===== TEST 1: Incarcare Fisier Corect =====" << endl;
    service.electrocasnice().incarcaModeleDinFisier("tests/electrocasnice_bun_1.csv");
    service.electrocasnice().afisareCatalog();

    cout << "\n===== TEST 2: Incarcare Fisier cu Erori =====" << endl;
    service.electrocasnice().incarcaModeleDinFisier("tests/electrocasnice_rau_1.csv");

    cout << "\n===== TEST 3: Verificare Model Reparabil =====" << endl;
    if (service.electrocasnice().esteModelReparabil("Laptop", "ASUS", "Zenbook")) {
        cout << "[OK] Laptop ASUS Zenbook este in catalog." << endl;
    } else {
        cout << "[EROARE] Laptop ASUS Zenbook nu a fost gasit!" << endl;
    }

    
    if (!service.electrocasnice().esteModelReparabil("TV", "Sony", "Bravia")) {
        cout << "[OK] Sony Bravia a fost respins corect (nu e in catalog)." << endl;
    }

    cout << "\n===== TEST 4: Adaugare Manuala =====" << endl;
    // Aici introduci de la tastatura datele: Frigider, Samsung, FamilyHub, 2024, 9000, 1
    service.electrocasnice().adaugaModelManual();
    
    cout << "\n===== TEST 5: Stergere Model =====" << endl;
    service.electrocasnice().stergeModel("Laptop", "ASUS", "Zenbook");
    
    cout << "\n===== CATALOG FINAL =====" << endl;
    service.electrocasnice().afisareCatalog();

    return 0;
}