#ifndef PLIKZADRESATAMI_H
#define PLIKZADRESATAMI_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>

#include "Adresat.h"
#include "MetodyPomocnicze.h"

using namespace std;

class PlikZAdresatami
{
    const string nazwaPlikuZAdresatami;
    const string nazwaPlikuTymczasowego;
    string liniaZDanymiAdresata;
    int idOstatniegoAdresata;
    fstream plikZAdresatami;
    string zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat adresat);
    void usunPlik(string nazwaPlikuTymczasowego, string nazwaPlikuZAdresatami);
    int zwrocNumerLiniiSzukanegoAdresata(int idAdresata);
    void zmienNazwePliku(string nazwaPlikuTymczasowego, string nazwaPlikuZAdresatami);

public:
    PlikZAdresatami(string nazwaPlikuZAdresatami) : nazwaPlikuZAdresatami(nazwaPlikuZAdresatami) {};
    void dopiszAdresataDoPliku(Adresat adresat);
    int wczytajAdresatowZalogowanegoUzytkownikaZPliku(vector <Adresat> adresaci, int idZalogowanegoUzytkownika);
    bool czyPlikJestPusty(fstream &plikZAdresatami);
};

#endif
