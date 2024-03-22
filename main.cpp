#include <iostream>

#include "KsiazkaAdresowa.h"
#include "UzytkownikMenedzer.h"
#include "PlikZAdresatami.h"

using namespace std;

int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;
    KsiazkaAdresowa ksiazkaAdresowa("Uzytkownicy.txt", "Adresaci.txt");
    char wybor;
    UzytkownikMenedzer uzytkownikMenedzer("Uzytkownicy.txt");
    int idOstatniegoAdresata;
    PlikZAdresatami plikZAdresatami("Adresaci.txt");

    while (true)
    {
        int idZalogowanegoUzytkownika = uzytkownikMenedzer.pobierzIdZalogowanegoUzytkownika();
        if (idZalogowanegoUzytkownika == 0)
        {
            wybor = uzytkownikMenedzer.wybierzOpcjeZMenuGlownego();

            switch (wybor)
            {
            case '1':
                ksiazkaAdresowa.rejestracjaUzytkownika();
                break;
            case '2':
                idZalogowanegoUzytkownika = uzytkownikMenedzer.logowanieUzytkownika();
                break;
            case '9':
                exit(0);
                break;
            default:
                cout << endl << "Nie ma takiej opcji w menu." << endl << endl;
                system("pause");
                break;
            }
        }
        else
        {
            if (adresaci.empty() == true)
                idOstatniegoAdresata = plikZAdresatami.wczytajAdresatowZalogowanegoUzytkownikaZPliku(adresaci, idZalogowanegoUzytkownika);

            wybor = uzytkownikMenedzer.wybierzOpcjeZMenuUzytkownika();

            switch (wybor)
            {
            case '1':
                idOstatniegoAdresata = ksiazkaAdresowa.dodajAdresata(adresaci, idZalogowanegoUzytkownika, idOstatniegoAdresata);
                break;
            case '2':
                ksiazkaAdresowa.wyswietlWszystkichAdresatow(adresaci);
                break;
            case '8':
                idZalogowanegoUzytkownika = 0;
                adresaci.clear();
                break;
            }
        }
    }
    return 0;
}

