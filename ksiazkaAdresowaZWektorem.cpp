#include <iostream>
#include <sstream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Adresat
{
    string imie = "", nazwisko = "", mail = "", adresZamieszkania = "", numerTelefonu = "";
    int id = 0;
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
void dodajAdresata(vector <Adresat> &adresaci)
{
    Adresat adresat;
    adresat.id = adresaci.empty() ? 1 : adresaci.back().id + 1;
    cout << "Podaj imie: ";
    adresat.imie = pobierzLinie();
    adresat.imie = zamianaPierwszejLiteryNaDuzaResztyNaMala(adresat.imie);
    cout << "Podaj nazwisko: ";
    adresat.nazwisko = pobierzLinie();
    adresat.nazwisko = zamianaPierwszejLiteryNaDuzaResztyNaMala(adresat.nazwisko);
    cout << "Podaj adres e-mail: ";
    adresat.mail = pobierzLinie();
    cout << "Podaj nr tel.: ";
    adresat.numerTelefonu = pobierzLinie();
    cout << "Podaj adres: ";
    adresat.adresZamieszkania = pobierzLinie();

    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::out | ios::app);
    if (plik.good())
    {
            plik << adresat.id << "|";
            plik << adresat.imie << "|";
            plik << adresat.nazwisko << "|";
            plik << adresat.mail << "|";
            plik << adresat.numerTelefonu << "|";
            plik << adresat.adresZamieszkania << "|" << endl;
            plik.close();
            adresaci.push_back(adresat);
    }
    else cout << "Blad przy probie otwarcia pliku." << endl;
    system("pause");
}
vector<Adresat> wczytajDaneZPliku()
{
    vector <Adresat> adresaci;
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);
    if(plik.good() == false)
    {
        cout << "Plik nie istnieje" << endl;
        return adresaci;
    }

    string daneAdresata = "";

    while (getline(plik, daneAdresata))
    {
        Adresat adresat;
        stringstream ss(daneAdresata);

        ss >> adresat.id;
        ss.ignore();
        getline(ss, adresat.imie, '|');
        getline(ss, adresat.nazwisko, '|');
        getline(ss, adresat.mail, '|');
        getline(ss, adresat.numerTelefonu, '|');
        getline(ss, adresat.adresZamieszkania, '|');

        adresaci.push_back(adresat);
    }
    plik.close();
    return adresaci;
}
void wyszukajPoImieniu(vector <Adresat> &adresaci)
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
            if (itr->imie == imiePoszukiwanegoAdresata)
            {
                cout << "Id:                 " << itr->id << endl;
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
void wyszukajPoNazwisku (vector <Adresat> &adresaci)
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
            if (nazwiskoPoszukiwanegoAdresata == itr->nazwisko)
            {
                cout << "Id:                 " << itr->id << endl;
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
void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci)
{
    system("cls");
    if (!adresaci.empty())
    {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            cout << "Id:                 " << itr->id << endl;
            cout << "Imie:               " << itr->imie << endl;
            cout << "Nazwisko:           " << itr->nazwisko << endl;
            cout << "Numer telefonu:     " << itr->numerTelefonu << endl;
            cout << "Email:              " << itr->mail << endl;
            cout << "Adres:              " << itr->adresZamieszkania << endl << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }

    system("pause");
}
void przepiszDaneAdresataPoEdycjiLubUsunieciuDoPliku(vector <Adresat> &adresaci)
{
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::out | ios::trunc);
    if (plik.good())
    {
        for (const auto &adresat : adresaci)
        {
            plik << adresat.id << "|";
            plik << adresat.imie << "|";
            plik << adresat.nazwisko << "|";
            plik << adresat.mail << "|";
            plik << adresat.numerTelefonu << "|";
            plik << adresat.adresZamieszkania << "|" << endl;
        }
        plik.close();
    }
    else cout << "Problem z otwarciem pliku." << endl;
}
void usunAdresata(vector <Adresat> &adresaci)
{
    int idWybranegoAdresata = 0;

    bool adresatZnaleziony = false;

    system("cls");
    if (!adresaci.empty())
    {
        cout << "Podaj numer ID adresata, ktorego chcesz usunac: ";
        idWybranegoAdresata = wczytajLiczbeCalkowita();

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr->id == idWybranegoAdresata)
            {
                adresatZnaleziony = true;
                cout << "Czy na pewno chcesz usunac adresata o numerze ID " << idWybranegoAdresata << "? Potwierdz wciskajac klawisz t" << endl;
                char potwierdzenie = wczytajZnak();

                if (potwierdzenie == 't')
                {
                    adresaci.erase(itr);
                    przepiszDaneAdresataPoEdycjiLubUsunieciuDoPliku(adresaci);
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
void edytujDaneAdresata(vector <Adresat> &adresaci)
{
    int idWybranegoAdresata = 0;
    bool adresatZnaleziony = false;

    if(!adresaci.empty())
    {
        cout << "Prosze podac numer ID adresata, ktorego chcesz edytowac:" << endl;
        idWybranegoAdresata = wczytajLiczbeCalkowita();
        for(vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++){
            if(itr->id == idWybranegoAdresata)
            {
                adresatZnaleziony = true;
                cout << "Wybierz, ktora informacje chcesz edytowac: " << endl;
                cout << "1. Imie" << endl;
                cout << "2. Nazwisko" << endl;
                cout << "3. E-mail" << endl;
                cout << "4. Adres zamieszkania" << endl;
                cout << "5. Numer telefonu" << endl;

                Adresat adresat;
                char wybor = wczytajZnak();
                switch (wybor)
                {
                case '1':
                cout << "Podaj nowe imie: ";
                itr->imie = pobierzLinie();
                itr->imie = zamianaPierwszejLiteryNaDuzaResztyNaMala(itr->imie);
                cout << endl << "Imie zostalo zmienione" << endl;
                break;
                case '2':
                cout << "Podaj nowe nazwisko: ";
                itr->nazwisko = pobierzLinie();
                itr->nazwisko = zamianaPierwszejLiteryNaDuzaResztyNaMala(itr->nazwisko);
                cout << endl << "Nazwisko zostalo zmienione" << endl;
                break;
                case '3':
                cout << "Podaj nowy e-mail: ";
                itr->mail = pobierzLinie();
                cout << endl << "Adres e-mail zostal zmieniony" << endl;
                break;
                case '4':
                cout << "Podaj nowy adres zamieszkania: ";
                itr->adresZamieszkania = pobierzLinie();
                cout << endl << "Adres zamieszkania zostal zmieniony" << endl;
                break;
                case '5':
                cout << "Podaj nowy numer telefonu: ";
                itr->numerTelefonu = pobierzLinie();
                cout << endl << "Numer telefonu zostal zmieniony" << endl;
                break;
                default:
                cout << "Niepoprawny wybor. Sprobuj wybrac jeszcze raz" << endl;
                break;
                }
                przepiszDaneAdresataPoEdycjiLubUsunieciuDoPliku(adresaci);
            }
        }
        if (adresatZnaleziony == false)
        {
            cout << "Nie ma adresata z takim numerem ID." << endl;
        }
    }
    else
    {
        cout << "Pusta ksiazka adresowa." << endl;
        Sleep(1500);
    }
}
int main()
{
    vector <Adresat> adresaci = wczytajDaneZPliku();

    while(1)
    {
        cout << "KSIAZKA ADRESOWA" << endl;
        system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        char wybor = wczytajZnak();
        switch (wybor)
        {
        case '1':
            dodajAdresata(adresaci);
            break;
        case '2':
            wyszukajPoImieniu(adresaci);
            break;
        case '3':
            wyszukajPoNazwisku(adresaci);
            break;
        case '4':
            wyswietlWszystkichAdresatow(adresaci);
            break;
        case '5':
            usunAdresata(adresaci);
            break;
        case '6':
            edytujDaneAdresata(adresaci);
            break;
        case '9':
            exit(0);
            break;
        }
    }
    return 0;
}
