#include "GestiuneElectrocasnice.h"
#include <fstream>
#include <sstream>

void GestiuneElectrocasnice::incarcaModeleDinFisier(const string &numeFisier)
{
    ifstream f(numeFisier);
    if (!f)
    {
        cerr << "Eroare: Nu s-a putut deschide fisierul de electrocasnice: " << numeFisier << endl;
        return;
    }

    string linie;
    int nrLinie = 0;
    while (getline(f, linie))
    {
        nrLinie++;
        if (linie.empty())
            continue;
        stringstream ss(linie);
        string tip, marca, model, an, pret;
        int an_productie;
        double pret_catalog;

        try
        {
            if (!getline(ss, tip, ','))
                throw invalid_argument("Lipseste tipul");
            if (!getline(ss, marca, ','))
                throw invalid_argument("Lipseste marca");
            if (!getline(ss, model, ','))
                throw invalid_argument("Lipseste model");
            if (!getline(ss, an, ','))
                throw invalid_argument("Lipseste an");
            if (!getline(ss, pret, ','))
                throw invalid_argument("Lipseste pret");

            auto trim = [](string &s)
            {
                s.erase(0, s.find_first_not_of(" \t\r\n"));
                size_t last = s.find_last_not_of(" \t\r\n");
                if (last != string::npos)
                    s.erase(last + 1);
            };

            trim(tip);
            trim(model);
            trim(marca);
            trim(an);
            trim(pret);
            an_productie = stoi(an);
            pret_catalog = stod(pret);

            unique_ptr<Electrocasnic> nou;
            if (tip == "Laptop")
            {
                string strRAM;
                if (!getline(ss, strRAM, ','))
                    throw invalid_argument("Lipseste memoria RAM");
                int RAM = stoi(strRAM);
                nou = make_unique<Laptop>(marca, model, an_productie, pret_catalog, RAM);
                catalog[tip].push_back(move(nou));
            }
            else if (tip == "TV")
            {
                string strdiag, unitate;
                if (!getline(ss, strdiag, ','))
                    throw invalid_argument("Lipseste valoare diagonala!");
                if (!getline(ss, unitate, ','))
                    throw invalid_argument("Lipseste unitate diagonala!");
                int diag = stoi(strdiag);
                unitate.erase(0, unitate.find_first_not_of(" "));
                nou = make_unique<TV>(marca, model, an_productie, pret_catalog, diag, unitate);
                catalog[tip].push_back(move(nou));
            }
            else if (tip == "Frigider")
            {
                string strcong;
                bool cong;
                if (!getline(ss, strcong, ','))
                    throw invalid_argument("Lipseste congelator!");
                if (strcong == " 1" || strcong == " true")
                {
                    cong = true;
                }
                else if (strcong == " 0" || strcong == " false")
                {
                    cong = false;
                }
                else
                {
                    throw invalid_argument("Valoare congelator necorespunzatoare ! " + strcong);
                }
                nou = make_unique<Frigider>(marca, model, an_productie, pret_catalog, cong);
                catalog[tip].push_back(move(nou));
            }
            else if (tip == "Masina_Spalat")
            {
                string strcap;
                if (!getline(ss, strcap, ','))
                    throw invalid_argument("Lipseste capacitate!");
                int capacitate = stoi(strcap);
                nou = make_unique<Masina_Spalat>(marca, model, an_productie, pret_catalog, capacitate);
                catalog[tip].push_back(move(nou));
            }
            else
            {
                throw invalid_argument("Tip angajat necunoscut: " + tip);
            }
        }
        catch (const exception &e)
        {
            cerr << "Eroare la citire: Electrocasnic invalid pe linia " << nrLinie
                 << ", cauza: " << e.what() << endl;
        }
    }
    f.close();
    cout << "Catalogul de electrocasnice a fost incarcat cu succes!\n";
};

void GestiuneElectrocasnice::adaugaModelManual()
{
    try
    {

        string tip, marca, model;
        int an_productie;
        double pret_catalog;

        unique_ptr<Electrocasnic> nou;
        cout << "tip: ";
        cin >> tip;
        if (tip != "Masina_Spalat" && tip != "Laptop" && tip != "TV" && tip != "Frigider")
            throw invalid_argument("Tip-ul electrocasnicului este necunoscut " + tip);
        cout << " marca:";
        cin >> marca;
        cout << " model:";
        cin >> model;
        cout << " an productie:";
        cin >> an_productie;
        cout << " pret catalog";
        cin >> pret_catalog;
        if (tip == "Masina_Spalat")
        {
            int capacitate;
            cout << " capacitate =";
            cin >> capacitate;
            nou = make_unique<Masina_Spalat>(marca, model, an_productie, pret_catalog, capacitate);
        }
        else if (tip == "Laptop")
        {
            int RAM;
            cout << " RAM=";
            cin >> RAM;
            nou = make_unique<Laptop>(marca, model, an_productie, pret_catalog, RAM);
        }
        else if (tip == "TV")
        {
            double diag;
            string unitate;
            cout << " diag=";
            cin >> diag;
            cout << " unitate=";
            cin >> unitate;
            nou = make_unique<TV>(marca, model, an_productie, pret_catalog, diag, unitate);
        }
        else if (tip == "Frigider")
        {
            bool congelator;
            cout << " congelator(0/1)=";
            cin >> congelator;
            nou = make_unique<Frigider>(marca, model, an_productie, pret_catalog, congelator);
        }
        catalog[tip].push_back(move(nou));
        cout << "electrocasnic adaugat cu succes!\n";
    }
    catch (const exception &e)
    {
        cout << e.what();
    }
};

bool GestiuneElectrocasnice::esteModelReparabil(const string &tip, const string &marca, const string &model) const
{

    string tipCautat = tip;

    tipCautat.erase(0, tipCautat.find_first_not_of(" \t\r\n"));
    tipCautat.erase(tipCautat.find_last_not_of(" \t\r\n") + 1);

    auto it = catalog.find(tipCautat);
    if (it == catalog.end())
    {
        cout << "DEBUG: Tipul '" << tipCautat << "' nu a fost gasit in map!\n";
        return false;
    }

    for (const auto &i : it->second)
    {
        if (i->get_marca() == marca && i->get_model() == model)
            return true;
    }
    return false;
};

void GestiuneElectrocasnice::stergeModel(const string &tip, const string &marca, const string &model)
{
    try
    {
        auto it = catalog.find(tip);
        if (it == catalog.end())
            throw invalid_argument("Tipul este necunoscut!" + tip);

        bool gasit = 0;
        for (auto i = (it->second).begin(); i != (it->second).end(); i++)
        {
            if ((*i)->get_marca() == marca && (*i)->get_model() == model)
            {
                (it->second).erase(i);
                gasit = 1;
                cout << "Electrocasnicul a fost eliminat cu succes!\n";
                break;
            }
        }
        if (!gasit)
            throw invalid_argument("Nu a fost gasit marca si modelul " + marca + " " + model);
    }
    catch (const exception &e)
    {
        cout << "Stergerea a esuat!Motiv:" << e.what() << endl;
    }
};

void GestiuneElectrocasnice::afisareCatalog() const
{
    if (catalog.empty())
    {
        cout << "Catalogul este gol\n";
        return;
    }

    for (auto itMap = catalog.begin(); itMap != catalog.end(); itMap++)
    {
        string tip = itMap->first;
        cout << "[" << tip << "]:\n";
        for (auto i = (itMap->second).begin(); i != (itMap->second).end(); i++)
        {
            (*i)->afiseaza(cout);
            cout << endl;
        }
    }
}