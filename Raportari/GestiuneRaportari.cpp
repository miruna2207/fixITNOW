#include "GestiuneRaportari.h"
#include "../ServiceManager.h"
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>

// ============= Functie utilitara ===============

template <typename T>
void gasesteCeaMaiLungaReparatie(const T &container, int &best_reparatie, Tehnician *&t)
{
    for (const auto &cerere : container)
    {
        if (cerere->get_durata_reparatie() > best_reparatie)
        {
            best_reparatie = cerere->get_durata_reparatie();
            t = cerere->get_tehnician_alocat();
        }
    }
}

// ========================= Rapoarte propriu-zise ==============================
void GestiuneRaportari::Cereri_Asteptare_Ordonate(const deque<unique_ptr<CerereReparatie>> &asteptare)
{
    if (asteptare.empty())
    {
        throw runtime_error(" coada asteptare este goala ");
        return;
    }

    map<string, map<string, vector<CerereReparatie *>>> grupate;

    for (auto it = asteptare.begin(); it != asteptare.end(); ++it)
    {
        CerereReparatie *ptr = it->get();
        string tip = ptr->get_aparat()->get_tip();
        string marca = ptr->get_aparat()->get_marca();

        grupate[tip][marca].push_back(ptr);
    }

    try
    {

        ofstream out("output/Cereri_Asteptare_ordonate.csv");
        if (!out)
        {
            throw runtime_error("fisierul nu poate fi deschis");
            return;
        }

        std::cout << "\n\n=========Cereri in asteptare=========\n";
        for (auto itTip = grupate.begin(); itTip != grupate.end(); ++itTip)
        {

            for (auto itMarca = itTip->second.begin(); itMarca != itTip->second.end(); ++itMarca)
            {

                sort(itMarca->second.begin(), itMarca->second.end(), [](CerereReparatie *a, CerereReparatie *b)
                     { return a->get_aparat()->get_model() < b->get_aparat()->get_model(); });

                for (auto itCerere = itMarca->second.begin(); itCerere != itMarca->second.end(); ++itCerere)
                {

                    (*itCerere)->afisare(out);
                    (*itCerere)->afisare(std::cout);
                    std::cout << endl;
                    out << "\n";
                }
            }
        }
        std::cout << "Fisierul a fost incarcat cu succes!\n";
        std::cout << "\n\n===================\n\n";
        out.close();
    }
    catch (const exception &e)
    {
        std::cout << "\n"
                  << e.what() << endl;
    }
}

void GestiuneRaportari::raportTopSalariuAngajati(const vector<unique_ptr<Angajat>> &lista_angajati)
{
    if (lista_angajati.empty())
    {
        throw runtime_error(" Lista de angajati este goala");
        return;
    }

    vector<Angajat *> lista;
    for (auto i = lista_angajati.begin(); i != lista_angajati.end(); i++)
    {
        lista.push_back(i->get());
    }

    sort(lista.begin(), lista.end(), [](Angajat *a, Angajat *b)
         { return a->get_Salariu() > b->get_Salariu(); });

    std::cout << "\n=== TOP 3 ANGAJATI DUPA SALARIU ===\n";
    int limita = min(3, (int)lista.size());
    for (int i = 0; i < limita; i++)
    {
        lista[i]->afiseaza(std::cout);
        std::cout << " ," << lista[i]->get_Salariu() << " RON" << endl;
    }
    std::cout << "==================================\n";

    try
    {
        ofstream file("output/Top_3_Angajati_In_Functie_De_Salariu.csv");
        if (!file)
        {
            throw runtime_error("Eroare: fisierul nu poate fi deschis");
            return;
        }

        for (int i = 0; i < limita; i++)
        {
            lista[i]->afiseaza(file);
            file << " ," << lista[i]->get_Salariu() << " RON" << endl;
        }
        file.close();
        std::cout << "Raportul a fost salvat cu succes in fisier!\n ";
    }
    catch (const exception &e)
    {
        cout << "\n"
             << e.what() << endl;
    }
}

void GestiuneRaportari::Angajat_Longest_Reparatie(const vector<unique_ptr<CerereReparatie>> &cereriFinalizate,
                                                  const vector<unique_ptr<CerereReparatie>> &cereriActive, const deque<unique_ptr<CerereReparatie>> &cereriAsteptare)
{

    int best_reparatie = -1;
    Tehnician *t = nullptr;

    gasesteCeaMaiLungaReparatie(cereriFinalizate, best_reparatie, t);
    gasesteCeaMaiLungaReparatie(cereriAsteptare, best_reparatie, t);
    gasesteCeaMaiLungaReparatie(cereriActive, best_reparatie, t);

    if (t == nullptr)
    {
        throw runtime_error("Nu exista nicio reparatie in sistem.");
        return;
    }

    std::cout << "\n=== TEHNICIAN CU CEA MAI LUNGA REPARATIE ===\n";
    t->afiseaza(std::cout);
    std::cout << " Salariu: " << t->get_Salariu() << " RON\n";
    std::cout << " Durata cea mai lunga reparatie: " << best_reparatie << " TIC-uri\n";
    std::cout << "============================================\n";

    try
    {
        ofstream file("output/Tehnician_cu_cea_mai_lunga_reparatie.csv");
        if (!file)
        {
            throw runtime_error("Eroare: fisierul nu poate fi deschis");
            return;
        }

        t->afiseaza(file);
        file << "," << t->get_Salariu() << "," << best_reparatie;
        file.close();
        std::cout << "Raportul a fost salvat cu succes in fisier!\n";
    }
    catch (const exception &e)
    {
        cout << "\n"
             << e.what() << endl;
    }
}

// ================================Raport pentru meniu electrocasnice ===========================
void GestiuneRaportari::raportAparateRespinse(const vector<unique_ptr<CerereReparatie>> &respinse)
{
    if (respinse.empty())
    {
        std::cout << "Nu exista aparate respinse in sistem." << endl;
        return;
    }

    map<string, int> frecventa;
    for (auto cr = respinse.begin(); cr != respinse.end(); cr++)
    {
        if ((*cr)->get_aparat())
        {
            string cheie = (*cr)->get_aparat()->get_marca() + " " + (*cr)->get_aparat()->get_model();
            frecventa[cheie]++;
        }
    }

    vector<pair<string, int>> elementeSortate(frecventa.begin(), frecventa.end());

    sort(elementeSortate.begin(), elementeSortate.end(),
         [](const pair<string, int> &a, const pair<string, int> &b)
         {
             return a.second > b.second;
         });

    for (auto cerere = elementeSortate.begin(); cerere != elementeSortate.end(); cerere++)
    {
        std::cout << cerere->first << " ," << cerere->second << endl;
    }
}