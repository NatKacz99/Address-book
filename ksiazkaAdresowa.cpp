#include "KsiazkaAdresowa.h"
#include <fstream>

void KsiazkaAdresowa::rejestracjaUzytkownika()
{
    uzytkownikMenedzer.rejestracjaUzytkownika();
}
void KsiazkaAdresowa::wypiszWszystkichUzytkownikow()
{
    uzytkownikMenedzer.wypiszWszystkichUzytkownikow();
}
void KsiazkaAdresowa::logowanieUzytkownika()
{
    uzytkownikMenedzer.logowanieUzytkownika();
}
int KsiazkaAdresowa::dodajAdresata(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika, int idOstatniegoAdresata)
{
    return adresatMenedzer.dodajAdresata(adresaci, idZalogowanegoUzytkownika, idOstatniegoAdresata);
}
void KsiazkaAdresowa::wyswietlWszystkichAdresatow(vector <Adresat> &adresaci)
{
    adresatMenedzer.wyswietlWszystkichAdresatow(adresaci);
}


