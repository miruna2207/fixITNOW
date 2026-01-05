#include "Angajat.h"
using namespace std;
int Angajat::nextid = 1;


Angajat::Angajat() : id(nextid)
{
    nextid++;
};

Angajat::Angajat(const string name, const string pronum, const string code, const string date, const string city)
    : id(nextid), nume(name), prenume(pronum), CNP(code), data_angajare(date), oras_domiciliu(city)
{
    nextid++;
    verify_angajat();
};

double Angajat::get_Salariu()
{
    double baza = 4000;
    if (oras_domiciliu != "Bucuresti")
        baza = baza + 400;
    int vechime = get_vechime();
    baza += (vechime / 3) * ((double)((5 * 4000) / 100));
    return baza;
};

int Angajat::get_vechime() const
{
    time_t t = time(nullptr);
    tm *now = localtime(&t);
    int anul_curent = now->tm_year + 1900;
    int luna_curenta = now->tm_mon +1;
    int zi_curenta = now->tm_mday;
    int zi_angajare = (data_angajare[0]-'0') * 10 + (data_angajare[1]-'0');
    int luna_angajare = (data_angajare[3]-'0') * 10 + (data_angajare[4]-'0');
    int an_angajare = (data_angajare[6]-'0') * 1000 + (data_angajare[7]-'0') * 100
     + (data_angajare[8]-'0') * 10 + (data_angajare[9]-'0');
    if ((zi_curenta - zi_angajare) < 0)
    {
        if ((luna_curenta - 1 - luna_angajare) < 0)
        {
            return anul_curent - an_angajare - 1;
        }
    }
    return anul_curent - an_angajare;
};

void Angajat::change_name(const string buff)
{
    verify_name(buff);
    nume = buff;
};

void verify_CNP(string CNP) 
{
    if (CNP.length() != 13)
    {
        throw std::invalid_argument("CNP n-are marime potrivita\n");
    }

    for (int i = 0; i < 13; i++)
    {
        if (!isdigit(CNP[i])){
            throw std::invalid_argument("CNP nu contine doar cifre\n");
        }
            
    }

    if (CNP[0] == '0' || CNP[0] == '3' || CNP[0] == '4' || CNP[0] == '9')
    {
        throw std::invalid_argument("cnp nu incepe cu cifra buna\n");
    }

    if (get_varsta(CNP) < 16)
    {
        throw std::out_of_range("varsta angajat <16\n");
    }

    int cod_judet = (CNP[7] - '0') * 10 + (CNP[8] - '0');
    if (cod_judet > 52 && cod_judet != 70)
    {
        throw(std::invalid_argument("CNP ul " + CNP + " este invalid(cod judet invalid)\n"));
    }

    verify_cifra_control(CNP);
};

int get_varsta(const string cod)
{
    int an_nastere = 0;
    if (cod[0] == '1' || cod[0] == '2') // e nascut inainte 2000
    {
        an_nastere = 1900;
        an_nastere += (cod[1] - '0') * 10;
        an_nastere += (cod[2] - '0') ;
    }
    if(cod[0] == '5' || cod[0] == '6')
    {
        an_nastere = 2000;
        an_nastere += (cod[1] - '0') * 10;
        an_nastere += (cod[2] - '0') ;
    }
    else{
        if(cod[0] == '7' || cod[0] == '8') //nascut in strainatate
        {
            int c = cod[1] - '0';
            if( c > 2)
                an_nastere = 1900 + c*10 + (cod[2] - '0');
            else
                an_nastere = 2000+ c*10+(cod[2]-'0');
        }
    }

    time_t t = time(nullptr);
    tm *now = localtime(&t);
    int anul_curent = now->tm_year + 1900;
    int luna_curenta = now->tm_mon +1;
    int zi_curenta = now->tm_mday;
        int luna_nastere = (cod[3] - '0') * 10 + (cod[4] - '0');
    int zi_nastere = (cod[5] - '0') * 10 + (cod[6] - '0');
    if ((zi_curenta - zi_nastere) < 0)
    {
        if ((luna_curenta - 1 - luna_nastere) < 0)
        {
            return anul_curent - an_nastere - 1;
        }
    }
    return anul_curent - an_nastere;
}

void verify_cifra_control(string CNP)
{
    int c = CNP[12] - '0';
    // 279146358279
    int s = (CNP[0] - '0') * 2 + (CNP[1] - '0') * 7 + (CNP[2] - '0') * 9 + (CNP[3] - '0') * 1 + (CNP[4] - '0') * 4 + (CNP[5] - '0') * 6 +
            (CNP[6] - '0') * 3 + (CNP[7] - '0') * 5 + (CNP[8] - '0') * 8 + (CNP[9] - '0') * 2 + (CNP[10] - '0') * 7 + (CNP[11] - '0') * 9;
    s = s % 11;
    if (!((s < 10 && c == s) || (s == 10 && c == 1)))
        throw(std::invalid_argument("CNP invalid,cifra control invalida\n"));
       
}

void verify_name(const string sir)
{
    if (sir.length() < 3)
    {
        throw std::invalid_argument("Nume " + sir + " prea scurt\n");
    }
    if (sir.length() > 30)
    {
        throw std::invalid_argument("Nume " + sir + " prea lung\n");
    }
}

bool verify_data_angajare(const string data_angajare)
{
    time_t t = time(nullptr);
    tm *now = localtime(&t);
    int anul_curent = now->tm_year + 1900;

    int zi_angajare = (data_angajare[0] - '0') * 10 + (data_angajare[1] - '0');
    int luna_angajare = (data_angajare[3] - '0') * 10 + (data_angajare[4] - '0');
    int an_angajare = (data_angajare[6] - '0') * 1000 + (data_angajare[7] - '0') * 100 
    + (data_angajare[8] - '0') * 10 + (data_angajare[9] - '0');
    if (zi_angajare > 31 || luna_angajare > 12 || an_angajare > anul_curent){
        throw std::invalid_argument("Data angajare nu exista "+data_angajare+"\n");
        return false;
    }
       
    else
        return true;
}

void Angajat::verify_angajat() const

{
    verify_name(nume);
    verify_name(prenume);
    verify_CNP(CNP);
    verify_data_angajare(data_angajare);
};
  
    void Angajat::afiseaza(ostream& file) const{
        file<<get_tip()<<" "<<nume<<" "<<prenume<<" "<<CNP<<" "<<id<<" "<<data_angajare<<" "<<oras_domiciliu;
    };

    string Angajat::get_CNP() const{
        return CNP;
    };

    string Angajat::get_nume() const{
        return nume;
    }

    string Angajat::get_prenume() const{
        return prenume;
    }