#include "GestiuneAngajati.h"
#include<sstream>
#include <fstream>
#include <iostream>

void GestiuneAngajati::adaugaAngajat()
{
    try
    {
        string tip, nume, prenume, cnp, data, oras;

        cout << "Tip (tehnician, receptioner, supervizor): ";
        cin >> tip;
        cout << "Nume: ";
        cin >> nume;
        cout << "Prenume: ";
        cin >> prenume;
        cout << "CNP: ";
        cin >> cnp;
        cout << "Data angajare (ZZ.LL.AAAA): ";
        cin >> data;
        cout << "Oras domiciliu: ";
        cin >> oras;

        if (tip == "tehnician")
        {
            int nr_comp;
            string tip_e, marca;
            cout << "nr competente:";
            cin >> nr_comp;
            vector<Competenta> comp;
            for (int i = 0; i < nr_comp; i++)
            {
                cout << "tip(tv,frigider,laptop,masina_spalat)";
                cin >> tip_e;
                cout << "marca ";
                cin >> marca;
                comp.push_back(Competenta{tip_e, marca});
            }

            lista.push_back(make_unique<Tehnician>(nume, prenume, cnp, data, oras, comp));
        }
        else if (tip == "receptioner")
        {
            lista.push_back(make_unique<Receptioner>(nume, prenume, cnp, data, oras));
        }
        else if (tip == "supervizor")
        {
            lista.push_back(make_unique<Supervizor>(nume, prenume, cnp, data, oras));
        }
        else
        {
            throw std::invalid_argument("Tip de angajat necunoscut!\n");
        }

        cout << "Angajat adaugat cu succes!\n";
    }
    catch (const exception &e)
    {
        cerr << "Eroare la adaugare: " << e.what() << endl;
    }
}
void GestiuneAngajati::incarcaDinFisier(const string& numeFisier) {
    ifstream f(numeFisier);
    if (!f) {
        cerr << "Eroare: Nu s-a putut deschide fisierul " << numeFisier << endl;
        return;
    }

    std::string linie;
    int nrLinie = 0;

    while (getline(f, linie)) {
        nrLinie++;
        if (linie.empty()) continue;

        stringstream ss(linie);
        string tip, nume, prenume, cnp, data, oras, temp;

        try {
            if (!getline(ss, tip, ',')) throw invalid_argument("Lipseste tipul");
            if (!getline(ss, nume, ',')) throw invalid_argument("Lipseste numele");
            if (!getline(ss, prenume, ',')) throw invalid_argument("Lipseste prenumele");
            if (!getline(ss, cnp, ',')) throw invalid_argument("Lipseste CNP");
            if (!getline(ss, data, ',')) throw invalid_argument("Lipseste data");
            if (!getline(ss, oras, ',')) throw invalid_argument("Lipseste orasul");

            auto trim = [](string& s) {
                s.erase(0, s.find_first_not_of(" "));
            };
            trim(tip); trim(nume); trim(prenume); trim(cnp); trim(data); trim(oras);

            if (tip == "tehnician") {
                string strNrComp;
                if (!getline(ss, strNrComp, ',')) throw runtime_error("Lipseste numarul de competente");
                
                int nrComp = stoi(strNrComp);
                vector<Competenta> comp_citite;

                for (int i = 0; i < nrComp; i++) {
                    string tip_e, marca;
                    if (!getline(ss, tip_e, ',') || !getline(ss, marca, ',')) {
                        throw runtime_error("Format competente invalid (pereche incompleta)");
                    }
                    trim(tip_e); trim(marca);
                    comp_citite.push_back(Competenta{tip_e, marca});
                }

                if (comp_citite.empty()) throw runtime_error("Tehnicianul trebuie sa aiba minim o competenta");

                lista.push_back(make_unique<Tehnician>(nume, prenume, cnp, data, oras, comp_citite));
            } 
            else if (tip == "receptioner") {
                lista.push_back(make_unique<Receptioner>(nume, prenume, cnp, data, oras));
            } 
            else if (tip == "supervizor") {
                lista.push_back(make_unique<Supervizor>(nume, prenume, cnp, data, oras));
            } 
            else {
                throw runtime_error("Tip angajat necunoscut: " + tip);
            }

        } catch (const exception& e) {
            cerr << "Eroare la citire: Angajat invalid pe linia " << nrLinie 
                 << ", cauza: " << e.what() << endl;
        }
    }
    f.close();
    cout<<" Lista de angajati a fost incarcata cu succes!";
}

void GestiuneAngajati::afisareToti() const
{
    if (lista.empty())
    {
        cout << "Nu sunt angajati in sistem.\n";
        return;
    }
    for ( auto a = lista.begin() ; a != lista.end(); a++)
    {
         (*a)->afiseaza();
         cout<<"Salariu: " << (*a)->get_Salariu() << " RON\n";
    }
}

void GestiuneAngajati::modificaNume(const std::string &cnp, const std::string &numeNou)
{
    Angajat *a = gasesteDupaCNP(cnp);
    if (a)
    {
        a->change_name(numeNou); 
        cout << "Nume modificat cu succes.\n";
    }
    else
    {
        cout << "Angajatul cu CNP-ul respectiv nu a fost gasit.\n";
    }
}

Angajat* GestiuneAngajati::gasesteDupaCNP(const std::string &cnp) const
{
    for (auto a =lista.begin() ; a != lista.end(); a++)
    {
        if ( ( (*a)->get_CNP()) == cnp)
            return  (*a).get();
    }
    return nullptr;
}

 void GestiuneAngajati::stergeAngajat(const string& cnp){
    Angajat *a = gasesteDupaCNP(cnp);
    if( a )
    {
        for( auto i = lista.begin(); i != lista.end() ; i ++){
            if( (*i)->get_CNP() == (*a).get_CNP()){
                cout<<"Angajatul "<<(*i)->get_nume()<<" "<<(*i)->get_prenume()<<" va fi sters\n";
                lista.erase(i);

                break;
            }
                
        }
    }
    else{
        cout<<"Angajat cu CNP-ul respectiv nu a fost gasit, cnp:"<<cnp<<endl;
    }
 };