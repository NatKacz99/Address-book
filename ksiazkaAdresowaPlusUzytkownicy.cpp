#include <iostream>
#include <sstream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
struct Uzytkownik
{
    int idUzytkownika = 0;
    string nazwa, hasloProba1;
};
struct Adresat
{
    string imie = "", nazwisko = "", mail = "", adresZamieszkania = "", numerTelefonu = "";
    int idAdresata = 0, idZalogowanegoUzytkownika = 0;
};
char wczytajZnak()
{
    string wejscie = "";
    char znak = {0};

    while (true){
        getline(cin, wejscie);

        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Sprobuj wpisac jeszcze raz." << endl;
    }
    return znak;
}
int wczytajLiczbeCalkowita()
{
    string wejscie = "";
    int liczba = 0;

    while (true)
    {
        getline(cin, wejscie);

        stringstream myStream(wejscie);
        if (myStream >> liczba)
            break;
        cout << "To nie jest liczba. Wpisz ponownie." << endl;
    }
    return liczba;
}
string pobierzLinie()
{
    string linia;
    getline(cin, linia);
    return linia;
}
string zamianaPierwszejLiteryNaDuzaResztyNaMala (string tekstDoZamiany)
{
    transform(tekstDoZamiany.begin(),tekstDoZamiany.begin()+1,tekstDoZamiany.begin(),::toupper);
    transform(tekstDoZamiany.begin()+1,tekstDoZamiany.end(),tekstDoZamiany.begin()+1,::tolower);
    return tekstDoZamiany;
}
void wczytajUzytkownikowZPliku (vector <Uzytkownik> &uzytkownicy)
{
    fstream plikZUzytkownikami;
    plikZUzytkownikami.open("uzytkownicy.txt", ios::in);
    if (plikZUzytkownikami.good())
    {
        string daneUzytkownika = "";

        while (getline(plikZUzytkownikami, daneUzytkownika))
        {
            Uzytkownik uzytkownik;
            stringstream ss(daneUzytkownika);

            ss >> uzytkownik.idUzytkownika;
            ss.ignore();
            getline(ss, uzytkownik.nazwa, '|');
            getline(ss, uzytkownik.hasloProba1, '|');

            uzytkownicy.push_back(uzytkownik);
        }
    }
    else
    {
        cout << "Problem z otwarciem pliku." << endl;
    }
    plikZUzytkownikami.close();
}
void przepiszDaneUzytkownikaPoZmianieHaslaDoPliku(vector <Uzytkownik> &uzytkownicy)
{
    fstream plikZUzytkownikami;
    plikZUzytkownikami.open("uzytkownicy.txt", ios::out | ios::trunc);
    if (plikZUzytkownikami.good())
    {
        for (const auto &uzytkownik : uzytkownicy)
        {
            plikZUzytkownikami << uzytkownik.idUzytkownika << "|";
            plikZUzytkownikami << uzytkownik.nazwa << "|";
            plikZUzytkownikami << uzytkownik.hasloProba1 << "|";
            plikZUzytkownikami << endl;
        }
    }
    else cout << "Problem z otwarciem pliku." << endl;
    plikZUzytkownikami.close();
}
void zmienHaslo(vector <Uzytkownik> &uzytkownicy)
{
    cout << "Podaj aktualne haslo: ";
    string aktualneHaslo = pobierzLinie();
    for(auto &uzytkownik : uzytkownicy)
    {
        if (aktualneHaslo == uzytkownik.hasloProba1)
        {
            cout << "Podaj nowe haslo: ";
            string noweHaslo = pobierzLinie();
            uzytkownik.hasloProba1 = noweHaslo;
            cout << "Twoje haslo zostalo zmienione" <<  endl;
            Sleep(1000);
            przepiszDaneUzytkownikaPoZmianieHaslaDoPliku(uzytkownicy);
            return;
        }
    }
    cout << "Podales/as niepoprawne haslo. Sprobuj wpisac jeszcze raz..." << endl;
    system("pause");
}
Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami)
{
    Adresat adresat;
    string pojedynczaDanaAdresata = "";
    char numerDanejAdresata = '1';
    for (size_t pozycjaZnaku = 0; pozycjaZnaku < daneAdresataOddzielonePionowymiKreskami.length(); pozycjaZnaku++)
    {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
        {
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else
        {
            switch(numerDanejAdresata)
            {
            case '1':
                adresat.idAdresata = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case '2':
                adresat.idZalogowanegoUzytkownika = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case '3':
                adresat.imie = pojedynczaDanaAdresata;
                break;
            case '4':
                adresat.nazwisko = pojedynczaDanaAdresata;
                break;
            case '5':
                adresat.numerTelefonu = pojedynczaDanaAdresata;
                break;
            case '6':
                adresat.mail = pojedynczaDanaAdresata;
                break;
            case '7':
                adresat.adresZamieszkania = pojedynczaDanaAdresata;
                break;
            default:
                cout << "Nie ma wiecej danych wybranego adresata" << endl;
                break;
            }
            pojedynczaDanaAdresata = "";
            numerDanejAdresata++;
        }
    }
    return adresat;
}
int logowanieUzytkownika(vector <Uzytkownik> &uzytkownicy);
int pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielone);
string pobierzLiczbeId(size_t pozycjaZnaku, string daneJednegoAdresataOddzielone);
int pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielone)
{
    size_t pozycjaRozpoczeciaIdUzytkownika = daneJednegoAdresataOddzielone.find_first_of("|") + 1;
    int idUzytkownika = atoi(pobierzLiczbeId(pozycjaRozpoczeciaIdUzytkownika, daneJednegoAdresataOddzielone).c_str());
    return idUzytkownika;
}
int wczytajDaneAdresataAktualnieZalogowanegoUzytkownikaZPliku(vector<Adresat> &adresaci, int idAktualnieZalogowanegoUzytkownika)
{
    Adresat adresat;
    string daneOstatniegoAdresataWPliku = "", daneJednegoAdresataOddzielonePionowymiKreskami = "";
    int idOstatniegoAdresataWPliku  = 0;
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if (!plik.good())
    {
        cout << "Nie udalo sie otworzyc pliku tekstowego i wczytac danych" << endl;
    }
    else
    {
        while(getline(plik, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            if (idAktualnieZalogowanegoUzytkownika == pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
                adresaci.push_back(adresat);
            }
            daneOstatniegoAdresataWPliku = daneJednegoAdresataOddzielonePionowymiKreskami;
        }
    }
    plik.close();

    if(daneOstatniegoAdresataWPliku != "")
    {
        idOstatniegoAdresataWPliku = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneOstatniegoAdresataWPliku);
        return idOstatniegoAdresataWPliku;
    }
    else return 0;
}
void wyszukajPoImieniu(vector <Adresat> &adresaci, int idAktualnieZalogowanegoUzytkownika)
{
    string imiePoszukiwanegoAdresata;
    int iloscAdresatow = 0;
    cout << "Podaj imie: " << endl;
    imiePoszukiwanegoAdresata = pobierzLinie();
    imiePoszukiwanegoAdresata = zamianaPierwszejLiteryNaDuzaResztyNaMala(imiePoszukiwanegoAdresata);
    if (!adresaci.empty())
    {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->imie == imiePoszukiwanegoAdresata && itr->idZalogowanegoUzytkownika == idAktualnieZalogowanegoUzytkownika)
            {
                cout << "Id:                 " << itr->idAdresata << endl;
                cout << "Imie:               " << itr->imie << endl;
                cout << "Nazwisko:           " << itr->nazwisko << endl;
                cout << "Numer Telefonu:     " << itr->numerTelefonu << endl;
                cout << "Nr Email:           " << itr->mail << endl;
                cout << "Adres:              " << itr->adresZamieszkania << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0)
        {
            cout << "Brak adresatow z takim imieniem" << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl;
    }
    system("pause");
}
void wyszukajPoNazwisku (vector <Adresat> &adresaci, int idAktualnieZalogowanegoUzytkownika)
{
    string nazwiskoPoszukiwanegoAdresata;
    int liczbaAdresatow = 0;
    cout << "Podaj nazwisko: " << endl;
    nazwiskoPoszukiwanegoAdresata = pobierzLinie();
    nazwiskoPoszukiwanegoAdresata = zamianaPierwszejLiteryNaDuzaResztyNaMala(nazwiskoPoszukiwanegoAdresata);
    if (!adresaci.empty())
    {
        for (vector<Adresat>:: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->idZalogowanegoUzytkownika == idAktualnieZalogowanegoUzytkownika && nazwiskoPoszukiwanegoAdresata == itr->nazwisko)
            {
                cout << "Id:                 " << itr->idAdresata << endl;
                cout << "Imie:               " << itr->imie << endl;
                cout << "Nazwisko:           " << itr->nazwisko << endl;
                cout << "Numer Telefonu:     " << itr->numerTelefonu << endl;
                cout << "Nr Email:           " << itr->mail << endl;
                cout << "Adres:              " << itr->adresZamieszkania << endl;
                liczbaAdresatow++;
            }
        }
        if (liczbaAdresatow == 0)
        {
            cout << "Niestety, nie ma adresata o podanym nazwisku" << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl;
    }
    system("pause");
}
void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci, int idAktualnieZalogowanegoUzytkownika)
{
    system("cls");
    if (!adresaci.empty())
    {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->idZalogowanegoUzytkownika == idAktualnieZalogowanegoUzytkownika)
            {
                cout << "Id:                 " << itr->idAdresata << endl;
                cout << "Imie:               " << itr->imie << endl;
                cout << "Nazwisko:           " << itr->nazwisko << endl;
                cout << "Numer telefonu:     " << itr->numerTelefonu << endl;
                cout << "Email:              " << itr->mail << endl;
                cout << "Adres:              " << itr->adresZamieszkania << endl << endl;
            }
        }
        cout << endl;
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }

    system("pause");
}
string konwersjaIntNaString(int liczba)
{
    ostringstream ss;
    ss << liczba;
    string zmieniona = ss.str();
    return zmieniona;
}
string zamienDaneAdresataNaOddzielonePionowymiKreskami(Adresat adresat)
{
    string pojedynczaLinia = "";
    pojedynczaLinia += konwersjaIntNaString(adresat.idAdresata) + "|";
    pojedynczaLinia += konwersjaIntNaString(adresat.idZalogowanegoUzytkownika) + "|";
    pojedynczaLinia += adresat.imie + '|';
    pojedynczaLinia += adresat.nazwisko + '|';
    pojedynczaLinia += adresat.mail + '|';
    pojedynczaLinia += adresat.adresZamieszkania + '|';
    pojedynczaLinia += adresat.numerTelefonu + '|';
    return pojedynczaLinia;
}
int zwrocNumerLiniiAdresata(int idAdresata)
{
    int numerLiniiWPlikuTekstowym = 1;
    bool czyIstniejeAdresat = false;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    fstream plikTekstowy;
    plikTekstowy.open("ksiazkaAdresowa.txt", ios::in);
    if(plikTekstowy.good() && numerLiniiWPlikuTekstowym != 0)
    {
        while(getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            if (idAdresata == pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                czyIstniejeAdresat = true;
                plikTekstowy.close();
                return numerLiniiWPlikuTekstowym;
            }
            else numerLiniiWPlikuTekstowym++;
        }
    }
    if (czyIstniejeAdresat == false)
    {
        plikTekstowy.close();
        return 0;
    }
    return 0;
}
void usunWybranaLinieWPliku(int numerUsuwanejLinii)
{
    fstream odczytywanyPlik, plikTymczasowy;
    string wczytanaLinia = "";
    int numerWczytanejLinii = 1;

    odczytywanyPlik.open("ksiazkaAdresowa.txt", ios::in);
    plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out | ios::app);

    if (odczytywanyPlik.good() == true && numerWczytanejLinii != 0)
    {
        while(getline(odczytywanyPlik, wczytanaLinia))
        {
            if(numerWczytanejLinii == numerUsuwanejLinii) {}
            else if (numerWczytanejLinii == 1 && numerWczytanejLinii != numerUsuwanejLinii)
            {
                plikTymczasowy << wczytanaLinia;
            }
            else if (numerWczytanejLinii == 2 && numerUsuwanejLinii == 1)
            {
                plikTymczasowy << wczytanaLinia;
            }
            else if (numerWczytanejLinii > 2 && numerUsuwanejLinii == 1)
            {
                plikTymczasowy << endl << wczytanaLinia;
            }
            else if (numerWczytanejLinii > 1 && numerUsuwanejLinii != 1)
            {
                plikTymczasowy << endl << wczytanaLinia;
            }
            numerWczytanejLinii++;
        }
    }
    odczytywanyPlik.close();
    plikTymczasowy.close();
    if (remove("ksiazkaAdresowa.txt") != 0 || rename("Adresaci_tymczasowy.txt", "ksiazkaAdresowa.txt") != 0)
    {
        throw runtime_error("Problem podczas aktualizacji pliku.");
    }
}
void usunAdresata(vector <Adresat> &adresaci)
{
    int idWybranegoAdresata = 0;
    int numerLiniiWybranegoAdresata = 0;

    bool adresatZnaleziony = false;

    system("cls");
    if (!adresaci.empty())
    {
        cout << "Podaj numer ID adresata, ktorego chcesz usunac: ";
        idWybranegoAdresata = wczytajLiczbeCalkowita();

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr -> idAdresata == idWybranegoAdresata)
            {
                adresatZnaleziony = true;
                cout << "Czy na pewno chcesz usunac adresata o numerze ID " << idWybranegoAdresata << "? Potwierdz wciskajac klawisz t" << endl;
                char potwierdzenie = wczytajZnak();

                if (potwierdzenie == 't')
                {
                    numerLiniiWybranegoAdresata = zwrocNumerLiniiAdresata(idWybranegoAdresata);
                    usunWybranaLinieWPliku(numerLiniiWybranegoAdresata);
                    adresaci.erase(itr);
                    cout << "Wybrany adresat zostal usuniety." << endl;
                    Sleep(1000);
                    break;
                }
                else
                {
                    cout << "Nie potwierdziles usuniecia." << endl;
                    Sleep(1000);
                    break;
                }
            }
        }
        if (adresatZnaleziony == false)
        {
            cout << "Brak adresata o podanym numerze ID." << endl;
            Sleep(1500);
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl;
        Sleep(1500);
    }
}
string pobierzLiczbeId(size_t pozycjaZnaku, string daneJednegoAdresataOddzielone)
{
    string liczbaId = "";
    if (pozycjaZnaku < daneJednegoAdresataOddzielone.length())
    {
        while(isdigit(daneJednegoAdresataOddzielone[pozycjaZnaku])  && pozycjaZnaku < daneJednegoAdresataOddzielone.length())
        {
            liczbaId += daneJednegoAdresataOddzielone[pozycjaZnaku];
            pozycjaZnaku++;
        }
    }
    return liczbaId;
}
int pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielone)
{
    size_t pozycjaRozpoczeciaIdAdresata = 0;
    int idAdresata = atoi(pobierzLiczbeId(pozycjaRozpoczeciaIdAdresata, daneJednegoAdresataOddzielone).c_str());
    return idAdresata;
}
void edytujWybranaLinieWPliku(string liniaZDanymiAdresataOddzielonymiPionowymiKreskami, int numerEdytowanejLinii)
{
    string wczytywanaLinia = "";
    int numerWczytanejLinii = 1;
    fstream plikTymczasowy, odczytywanyPlik;
    odczytywanyPlik.open("ksiazkaAdresowa.txt", ios::in),
    plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out | ios::app);

    if(odczytywanyPlik.good())
    {
        while(getline(odczytywanyPlik, wczytywanaLinia))
        {
            if (numerWczytanejLinii == numerEdytowanejLinii)
            {
                if (numerWczytanejLinii == 1)
                {
                    plikTymczasowy << liniaZDanymiAdresataOddzielonymiPionowymiKreskami;
                }
                else if (numerWczytanejLinii > 1)
                {
                    plikTymczasowy << endl << liniaZDanymiAdresataOddzielonymiPionowymiKreskami;
                }
            }
            else
            {
                if (numerWczytanejLinii == 1)
                {
                    plikTymczasowy << wczytywanaLinia;
                }
                else if (numerWczytanejLinii > 1)
                {
                    plikTymczasowy << endl << wczytywanaLinia;
                }
            }
            numerWczytanejLinii++;
        }
    }
    odczytywanyPlik.close();
    plikTymczasowy.close();

    if (remove("ksiazkaAdresowa.txt") != 0 || rename("Adresaci_tymczasowy.txt", "ksiazkaAdresowa.txt") != 0)
    {
        throw runtime_error("Problem podczas aktualizacji pliku.");
    }
}
void aktualizujDaneAdresata(Adresat adresat, int idAdresata)
{
    int numerEdytowanejLinii = zwrocNumerLiniiAdresata(idAdresata);
    string liniaZDanymiAdresata = "";

    liniaZDanymiAdresata = zamienDaneAdresataNaOddzielonePionowymiKreskami(adresat);
    edytujWybranaLinieWPliku(liniaZDanymiAdresata, numerEdytowanejLinii);
}
void edytujDaneAdresata(vector <Adresat> &adresaci)
{
    int idWybranegoAdresata = 0;
    bool adresatZnaleziony = false;

    if(!adresaci.empty())
    {
        cout << "Prosze podac numer ID adresata, ktorego chcesz edytowac:" << endl;
        idWybranegoAdresata = wczytajLiczbeCalkowita();
        for(size_t i = 0; i < adresaci.size(); i++)
        {
            if(adresaci[i].idAdresata == idWybranegoAdresata)
            {
                adresatZnaleziony = true;
                cout << "Wybierz, ktora informacje chcesz edytowac: " << endl;
                cout << "1. Imie" << endl;
                cout << "2. Nazwisko" << endl;
                cout << "3. E-mail" << endl;
                cout << "4. Adres zamieszkania" << endl;
                cout << "5. Numer telefonu" << endl;

                char wybor = wczytajZnak();
                switch (wybor)
                {
                case '1':
                cout << "Podaj nowe imie: ";
                adresaci[i].imie = pobierzLinie();
                adresaci[i].imie = zamianaPierwszejLiteryNaDuzaResztyNaMala(adresaci[i].imie);
                aktualizujDaneAdresata(adresaci[i], idWybranegoAdresata);
                cout << endl << "Imie zostalo zmienione" << endl;
                Sleep(1000);
                break;
                case '2':
                cout << "Podaj nowe nazwisko: ";
                adresaci[i].nazwisko = pobierzLinie();
                adresaci[i].nazwisko = zamianaPierwszejLiteryNaDuzaResztyNaMala(adresaci[i].nazwisko);
                aktualizujDaneAdresata(adresaci[i], idWybranegoAdresata);
                cout << endl << "Nazwisko zostalo zmienione" << endl;
                Sleep(1000);
                break;
                case '3':
                cout << "Podaj nowy e-mail: ";
                adresaci[i].mail = pobierzLinie();
                aktualizujDaneAdresata(adresaci[i], idWybranegoAdresata);
                cout << endl << "Adres e-mail zostal zmieniony" << endl;
                Sleep(1000);
                break;
                case '4':
                cout << "Podaj nowy adres zamieszkania: ";
                adresaci[i].adresZamieszkania = pobierzLinie();
                aktualizujDaneAdresata(adresaci[i], idWybranegoAdresata);
                cout << endl << "Adres zamieszkania zostal zmieniony" << endl;
                Sleep(1000);
                break;
                case '5':
                cout << "Podaj nowy numer telefonu: ";
                adresaci[i].numerTelefonu = pobierzLinie();
                aktualizujDaneAdresata(adresaci[i], idWybranegoAdresata);
                cout << endl << "Numer telefonu zostal zmieniony" << endl;
                Sleep(1000);
                break;
                default:
                cout << "Niepoprawny wybor. Sprobuj wybrac jeszcze raz" << endl;
                Sleep(1000);
                break;
                }
            }
        }
        if (adresatZnaleziony == false)
        {
            cout << "Nie ma adresata z takim numerem ID." << endl;
            Sleep(1000);
        }
    }
    else
    {
        cout << "Pusta ksiazka adresowa." << endl;
        Sleep(1000);
    }
}
int logowanieUzytkownika(vector <Uzytkownik> &uzytkownicy);
Adresat podajDaneNowegoAdresata(int idAktualnieZalogowanegoUzytkownika, int idOstatniegoAdresata)
{
    Adresat adresat;
    adresat.idAdresata = ++idOstatniegoAdresata;
    cout << "Podaj imie: ";
    adresat.imie = pobierzLinie();
    adresat.imie = zamianaPierwszejLiteryNaDuzaResztyNaMala(adresat.imie);
    cout << "Podaj nazwisko: ";
    adresat.nazwisko = pobierzLinie();
    adresat.nazwisko = zamianaPierwszejLiteryNaDuzaResztyNaMala(adresat.nazwisko);
    cout << "Podaj e-mail: ";
    adresat.mail = pobierzLinie();
    cout << "Podaj adres zamieszkania: ";
    adresat.adresZamieszkania = pobierzLinie();
    cout << "Podaj numer telefonu: ";
    adresat.numerTelefonu = pobierzLinie();
    adresat.idZalogowanegoUzytkownika = idAktualnieZalogowanegoUzytkownika;
    return adresat;
}
bool czyPlikJestPusty()
{
    if(!ifstream("ksiazkaAdresowa.txt", ios::ate).tellg())
    {
        return true;
    }
    else return false;
}
void dopiszAdresataDoPliku(Adresat &adresat)
{
    string liniaDaneAdresata = "";
    fstream plikOryginalny;
    plikOryginalny.open("ksiazkaAdresowa.txt", ios::out | ios::app);
    if(plikOryginalny.good() == true)
    {
        string liniaDaneAdresata = zamienDaneAdresataNaOddzielonePionowymiKreskami(adresat);

        if(czyPlikJestPusty() == true)
        {
            plikOryginalny << liniaDaneAdresata;
        }
        else
        {
            plikOryginalny << endl << liniaDaneAdresata;
        }
    }
    else
    {
        cout << "Problem z otwarciem pliku" << endl;
    }
    plikOryginalny.close();
    system("pause");
}
int dodajAdresata(vector <Adresat> &adresaci, int idAktualnieZalogowanegoUzytkownika, int idOstatniegoAdresata, Adresat adresat)
{
    adresat = podajDaneNowegoAdresata(idAktualnieZalogowanegoUzytkownika, idOstatniegoAdresata);
    adresaci.push_back(adresat);
    dopiszAdresataDoPliku(adresat);
    return ++idOstatniegoAdresata;
}
int logowanieUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    cout << "Podaj nazwe: ";
    string wprowadzonaNazwa = pobierzLinie();
    cout << "Podaj haslo: ";
    string wprowadzoneHaslo = pobierzLinie();
    for(auto &uzytkownik : uzytkownicy)
    {
        if (wprowadzonaNazwa == uzytkownik.nazwa && wprowadzoneHaslo == uzytkownik.hasloProba1)
        {
            cout << "Zalogowales/as sie na swoje konto" << endl;
            Sleep(1000);
            return uzytkownik.idUzytkownika;
        }
    }
    cout << "Wprowadzono niepoprawne dane logowania. Sprobuj ponownie." << endl;
    system("pause");
    system("cls");
    return 0;
}
void rejestracjaUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;
    string nazwa, hasloProba1, hasloProba2;
    cout << "Podaj nazwe uzytkownika: " << endl;
    uzytkownik.nazwa = pobierzLinie();
    cout << "Podaj haslo: " << endl;
    uzytkownik.hasloProba1 = pobierzLinie();
    cout << "Powtorz wprowadzone haslo: " << endl;
    hasloProba2 = pobierzLinie();
    if (uzytkownik.hasloProba1 == hasloProba2)
    {
        cout << "Rejestracja przebiegla pomyslnie. Mozesz zalogowac sie na swoje konto." << endl;
        uzytkownik.idUzytkownika = uzytkownicy.empty() ? 1 : uzytkownicy.back().idUzytkownika + 1;
        uzytkownicy.push_back(uzytkownik);
        ofstream plikZUzytkownikami;
        plikZUzytkownikami.open("uzytkownicy.txt", ios::out | ios::app);
        if (plikZUzytkownikami.good())
        {
            plikZUzytkownikami << uzytkownik.idUzytkownika << "|";
            plikZUzytkownikami << uzytkownik.nazwa << "|";
            plikZUzytkownikami << uzytkownik.hasloProba1 << "|";
            plikZUzytkownikami << endl;
            plikZUzytkownikami.close();
        }
        else cout << "Blad otwarcia pliku." << endl;
        system("pause");
    }
    else
    {
        cout << "Wprowadzone hasla nie sa identyczne. Prosze sprobowac wpisac ponownie." << endl;
        system("pause");
        system("cls");
    }
}
int main()
{
    vector <Uzytkownik> uzytkownicy;
    Adresat adresat;
    vector <Adresat> adresaci;
    int idAktualnieZalogowanegoUzytkownika = 0;
    int idOstatniegoAdresata = 0;
    char wybor;

    wczytajUzytkownikowZPliku(uzytkownicy);

    while(1)
    {
        if (idAktualnieZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << ">>> MENU GLOWNE <<<" << endl;
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Koniec programu" << endl;
            wybor = wczytajZnak();
            switch(wybor)
            {
            case '1':
                rejestracjaUzytkownika(uzytkownicy);
                break;
            case '2':
                idAktualnieZalogowanegoUzytkownika = logowanieUzytkownika(uzytkownicy);
                break;
            case '9':
                exit(0);
            default:
                cout << "Nie ma takiej opcji w menu" << endl;
                system("pause");
                break;
            }
        }
        else
        {
            if (adresaci.empty() == true)
            {
                idOstatniegoAdresata = wczytajDaneAdresataAktualnieZalogowanegoUzytkownikaZPliku(adresaci, idAktualnieZalogowanegoUzytkownika);
            }
                system("cls");
                cout << ">>> MENU ADRESATA <<<" << endl;
                cout << "1. Dodaj adresata" << endl;
                cout << "2. Wyszukaj po imieniu" << endl;
                cout << "3. Wyszukaj po nazwisku" << endl;
                cout << "4. Wyswietl wszystkich adresatow" << endl;
                cout << "5. Usun adresata" << endl;
                cout << "6. Edytuj adresata" << endl;
                cout << "--------------------------------" << endl;
                cout << "7. Zmien haslo" << endl;
                cout << "8. Wyloguj sie" << endl;
                wybor = wczytajZnak();
                switch (wybor)
                {
                case '1':
                    idOstatniegoAdresata = dodajAdresata(adresaci, idAktualnieZalogowanegoUzytkownika, idOstatniegoAdresata, adresat);
                    break;
                case '2':
                    wyszukajPoImieniu(adresaci, idAktualnieZalogowanegoUzytkownika);
                    break;
                case '3':
                    wyszukajPoNazwisku(adresaci, idAktualnieZalogowanegoUzytkownika);
                    break;
                case '4':
                    wyswietlWszystkichAdresatow(adresaci, idAktualnieZalogowanegoUzytkownika);
                    break;
                case '5':
                    usunAdresata(adresaci);
                    break;
                case '6':
                    edytujDaneAdresata(adresaci);
                    break;
                case '7':
                    zmienHaslo(uzytkownicy);
                    break;
                case '8':
                    idAktualnieZalogowanegoUzytkownika = 0;
                    adresaci.clear();
                    system("cls");
                default:
                    cout << "Nie ma takiej opcji w menu" << endl;
                }
        }
    }
    return 0;
}

