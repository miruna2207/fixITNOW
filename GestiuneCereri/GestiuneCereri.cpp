#include "GestiuneCereri.h"
#include "../ServiceManager.h"
#include <iostream>
#include <sstream>

void GestiuneCereri::incarcaDinFisier(const string &numeFisier)
{
    ifstream f(numeFisier);
    if (!f.is_open())
    {
        cout << "Eroare: Nu s-a putut deschide fisierul " << numeFisier << endl;
        return;
    }

    string linie;
    int nr_linie = 0;
    while (getline(f, linie))
    {
        nr_linie++;
        try
        {
            stringstream ss(linie);
            string numeClient, complexitateStr, tip;

            if (!getline(ss, numeClient, ',') || !getline(ss, complexitateStr, ','))
                continue;

            if (!getline(ss, tip, ','))
                continue;

            tip.erase(0, tip.find_first_not_of(" \t\r\n"));
            tip.erase(tip.find_last_not_of(" \t\r\n") + 1);

            auto aparatNou = citesteAparat(ss, tip, nr_linie);

            int complexitate = stoi(complexitateStr);
            if (complexitate < 0 || complexitate > 5)
                throw out_of_range("Complexitate nu se afla in intervalul 0-5 " + complexitate);

            auto cr = make_unique<CerereReparatie>(std::move(aparatNou), numeClient, complexitate);
            ServiceManager::getInstance().proceseazaCerereNoua(std::move(cr));
        }
        catch (const exception &e)
        {
            cout << "Eroare la procesarea liniei " << nr_linie << ": " << e.what() << endl;
        }
    }
}

void GestiuneCereri::adaugaManual()
{
    try
    {
        string numeClient, tip, marca, model;
        int complexitate, an;
        double pret;

        cout << "Nume Client: ";
        cin.ignore();
        getline(cin, numeClient);
        cout << "Complexitate (1-5): ";
        cin >> complexitate;
        cout << "Tip (Laptop/TV/Frigider/Masina_Spalat): ";
        cin >> tip;
        cout << "Marca: ";
        cin >> marca;
        cout << "Model: ";
        cin >> model;
        cout << "An fabricatie: ";
        cin >> an;
        cout << "Pret catalog: ";
        cin >> pret;

        unique_ptr<Electrocasnic> nou;
        if (tip == "Laptop")
        {
            int ram;
            cout << "RAM (GB): ";
            cin >> ram;
            nou = make_unique<Laptop>(marca, model, an, pret, ram);
        }
        else if (tip == "TV")
        {
            double diag;
            string unit;
            cout << "Diagonala: ";
            cin >> diag;
            cout << "Unitate: ";
            cin >> unit;
            nou = make_unique<TV>(marca, model, an, pret, diag, unit);
        }
        else if (tip == "Frigider")
        {
            bool cong;
            cout << "Are congelator (1/0): ";
            cin >> cong;
            nou = make_unique<Frigider>(marca, model, an, pret, cong);
        }
        else if (tip == "Masina_Spalat")
        {
            int cap;
            cout << "Capacitate (kg): ";
            cin >> cap;
            nou = make_unique<Masina_Spalat>(marca, model, an, pret, cap);
        }

        if (nou)
        {
            auto cr = make_unique<CerereReparatie>(std::move(nou), numeClient, complexitate);
            ServiceManager::getInstance().proceseazaCerereNoua(std::move(cr));
            cout << "Cererea a fost inregistrata cu succes!\n";
        }
        else
        {
            cout << "Eroare: Tip electrocasnic necunoscut.\n";
        }
    }
    catch (const exception &e)
    {
        cout << "Eroare la adaugarea manuala: " << e.what() << endl;
    }
}

unique_ptr<Electrocasnic> citesteAparat(stringstream &ss, string tip, int nr_linie)
{
    string marca, model, anStr, pretStr;

    if (!getline(ss, marca, ','))
        throw invalid_argument("Lipseste marca");
    if (!getline(ss, model, ','))
        throw invalid_argument("Lipseste modelul");
    if (!getline(ss, anStr, ','))
        throw invalid_argument("Lipseste anul");
    if (!getline(ss, pretStr, ','))
        throw invalid_argument("Lipseste pretul");

    auto trim = [](string &s) {
    s.erase(0, s.find_first_not_of(" \t\r\n"));
    size_t last = s.find_last_not_of(" \t\r\n");
    if (last != string::npos) s.erase(last + 1);
    };

    trim(marca);
    trim(model);
    trim(anStr);
    trim(pretStr);
    trim(tip);

    int an = stoi(anStr);
    double pret = stod(pretStr);

    if (tip == "Laptop")
    {
        string strRAM;
        if (!getline(ss, strRAM, ','))
            throw invalid_argument("Lipseste memoria RAM");
        trim(strRAM);
        int RAM = stoi(strRAM);
        if (RAM < 0)
            throw out_of_range("RAM-ul nu poate fi negativ");

        return make_unique<Laptop>(marca, model, an, pret, RAM);
    }
    else if (tip == "TV")
    {
        string strdiag, unitate;
        if (!getline(ss, strdiag, ','))
            throw invalid_argument("Lipseste diagonala");
        if (!getline(ss, unitate, ','))
            throw invalid_argument("Lipseste unitatea");
        trim(strdiag);
        trim(unitate);

        double diag = stod(strdiag);
        if (diag < 0)
            throw out_of_range("Diagonala nu poate fi negativa");

        return make_unique<TV>(marca, model, an, pret, diag, unitate);
    }
    else if (tip == "Frigider")
    {
        string strcong;
        if (!getline(ss, strcong, ','))
            throw invalid_argument("Lipseste info congelator");
        trim(strcong);

        bool cong;
        if (strcong == "1" || strcong == "true")
            cong = true;
        else if (strcong == "0" || strcong == "false")
            cong = false;
        else
            throw invalid_argument("Valoare congelator invalida (0/1 sau true/false): " + strcong);

        return make_unique<Frigider>(marca, model, an, pret, cong);
    }
    else if (tip == "Masina_Spalat")
    {
        string strcap;
        if (!getline(ss, strcap, ','))
            throw invalid_argument("Lipseste capacitatea");
        trim(strcap);
        int capacitate = stoi(strcap);
        if (capacitate < 0)
            throw out_of_range("Capacitatea nu poate fi negativa");

        return make_unique<Masina_Spalat>(marca, model, an, pret, capacitate);
    }
    else
    {
        throw invalid_argument("Tip electrocasnic necunoscut: " + tip);
    }
}