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
int KsiazkaAdresowa::logowanieUzytkownika(int &idZalogowanegoUzytkownika)
{
    return uzytkownikMenedzer.logowanieUzytkownika(idZalogowanegoUzytkownika);
}
int KsiazkaAdresowa::dodajAdresata()
{
    return adresatMenedzer.dodajAdresata();
}
void KsiazkaAdresowa::wyswietlWszystkichAdresatow()
{
    adresatMenedzer.wyswietlWszystkichAdresatow();
}
int KsiazkaAdresowa::pobierzIdZalogowanegoUzytkownika()
{
    return uzytkownikMenedzer.pobierzIdZalogowanegoUzytkownika();
}
int KsiazkaAdresowa::wczytajAdresatowZalogowanegoUzytkownikaZPliku(vector <Adresat> adresaci, int idZalogowanegoUzytkownika)
{
    return plikZAdresatami.wczytajAdresatowZalogowanegoUzytkownikaZPliku(adresaci, idZalogowanegoUzytkownika);
}
char KsiazkaAdresowa::wybierzOpcjeZMenuUzytkownika()
{
    return uzytkownikMenedzer.wybierzOpcjeZMenuUzytkownika();
}
char KsiazkaAdresowa::wybierzOpcjeZMenuGlownego()
{
    return uzytkownikMenedzer.wybierzOpcjeZMenuGlownego();
}
void KsiazkaAdresowa::wylogujUzytkownika()
{
    uzytkownikMenedzer.wylogujUzytkownika();
}
