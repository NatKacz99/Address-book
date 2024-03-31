#ifndef ADRESATMENEDZER_H
#define ADRESATMENEDZER_H

#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>

#include "Adresat.h"
#include "Uzytkownik.h"
#include "PlikZAdresatami.h"

using namespace std;

class AdresatMenedzer
{
    int idAdresata;
    int idZalogowanegoUzytkownika;
    int idOstatniegoAdresata;
    vector <Adresat> adresaci;
    vector <Uzytkownik> uzytkownicy;
    PlikZAdresatami plikZAdresatami;

    Adresat podajDaneNowegoAdresata(int idZalogowanegoUzytkownika, int idOstatniegoAdresata);

public:
    AdresatMenedzer(string nazwaPlikuZAdresatami) : plikZAdresatami(nazwaPlikuZAdresatami) {};
    void ustawIdZalogowanegoUzytkownika(int noweIdZalogowanegoUzytkownika);
    void ustawIdOstatniegoAdresata(int noweIdOstatniegoAdresata);
    int pobierzIdOstatniegoAdresata();
    int dodajAdresata();
    Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami);
    string nazwaPlikuZAdresatami = "Adresaci.txt";
    int pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami);
    void wyswietlWszystkichAdresatow();
    void wyswietlDaneAdresata(Adresat adresat);
};

#endif
