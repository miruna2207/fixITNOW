#include "GestiuneRaportari.h"
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>

void GestiuneRaportari::raportAparateRespinse(const vector<unique_ptr<CerereReparatie>> &respinse)
{
    if (respinse.empty())
    {
        cout << "Nu exista aparate respinse in sistem." << endl;
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
        cout << cerere->first << " " << cerere->second << endl;
    }
}

void GestiuneRaportari::raportTopSalariuAngajati(const vector<unique_ptr<Angajat>> &lista_angajati)
{
    if (lista_angajati.empty())
    {
        cout << " Lista de angajati este goala\n";
        return;
    }

    vector<Angajat*> lista;
    for (auto i = lista_angajati.begin(); i != lista_angajati.end(); i++)
    {
        lista.push_back(i->get());
    }

    sort(lista.begin(), lista.end(), [](Angajat *a, Angajat *b)
         { return a->get_Salariu() > b->get_Salariu(); });

    ofstream file("../output/Top_3_Angajati_In_Functie_De_Salariu.csv");
    if(!file){
        cout<<" fisierul nu poate fi deschis\n";
        return;
    }

    int limita = 3;
    for(int i = 0; i < limita; i++){
        lista[i]->afiseaza(file);
        file << " " << lista[i]->get_Salariu() << endl;
    }
    file.close();
};