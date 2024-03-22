#include "PlikZAdresatami.h"
#include "UzytkownikMenedzer.h"
#include "AdresatMenedzer.h"

void PlikZAdresatami::dopiszAdresataDoPliku(Adresat adresat)
{
    liniaZDanymiAdresata = "";
    plikZAdresatami.open(nazwaPlikuZAdresatami.c_str(), ios::out | ios::app);

    if (plikZAdresatami.good() == true)
    {
        liniaZDanymiAdresata = zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);

        if (czyPlikJestPusty(plikZAdresatami) == true)
        {
            plikZAdresatami << liniaZDanymiAdresata;
        }
        else
        {
            plikZAdresatami << endl << liniaZDanymiAdresata ;
        }
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
    }
    plikZAdresatami.close();
    system("pause");
}
int PlikZAdresatami::wczytajAdresatowZalogowanegoUzytkownikaZPliku(vector <Adresat> adresaci, int idZalogowanegoUzytkownika)
{
    Adresat adresat;
    UzytkownikMenedzer uzytkownikMenedzer("Uzytkownicy.txt");
    AdresatMenedzer adresatMenedzer("Adresaci.txt");
    idOstatniegoAdresata = 0;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    string daneOstaniegoAdresataWPliku = "";
    plikZAdresatami.open(nazwaPlikuZAdresatami.c_str(), ios::in);

    if (plikZAdresatami.good() == true)
    {
        while (getline(plikZAdresatami, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            if(idZalogowanegoUzytkownika == uzytkownikMenedzer.pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                adresat = adresatMenedzer.pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
                adresaci.push_back(adresat);
            }
        }
        daneOstaniegoAdresataWPliku = daneJednegoAdresataOddzielonePionowymiKreskami;
    }
    else
        cout << "Nie udalo sie otworzyc pliku i wczytac danych." << endl;

    plikZAdresatami.close();

    if (daneOstaniegoAdresataWPliku != "")
    {
        idOstatniegoAdresata = adresatMenedzer.pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneOstaniegoAdresataWPliku);
        return idOstatniegoAdresata;
    }
    else
        return 0;
}
bool PlikZAdresatami::czyPlikJestPusty(fstream &plikZAdresatami)
{
    plikZAdresatami.seekg(0, ios::end);
    if (plikZAdresatami.tellg() == 0)
        return true;
    else
        return false;
}
string PlikZAdresatami::zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat adresat)
{
    liniaZDanymiAdresata = "";

    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzId()) + '|';
    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzIdUzytkownika()) + '|';
    liniaZDanymiAdresata += adresat.pobierzImie() + '|';
    liniaZDanymiAdresata += adresat.pobierzNazwisko() + '|';
    liniaZDanymiAdresata += adresat.pobierzNumerTelefonu() + '|';
    liniaZDanymiAdresata += adresat.pobierzEmail() + '|';
    liniaZDanymiAdresata += adresat.pobierzAdres() + '|';

    return liniaZDanymiAdresata;
}
