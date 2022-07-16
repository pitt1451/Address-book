#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <vector>

using namespace std;

struct Osoba
{
    int idAdresata = 0, idZalogowanegoUzytkownika = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "",adres = "";
};

struct Uzytkownik
{
    int id;
    string nazwaUzytkownika, hasloUzytkownika;
};

int konwersjaStringNaInt(string wyraz);

Osoba pobierzDaneZapisanejOsoby(string wczytanaLinia);
string zapiszEdytowaneDaneAdresata(Osoba osoba);
int wczytajZapisaneOsobyZPlikuTekstowego(vector <Osoba> &osoby, int idZalogowanegoUzytkownika);

int dodajNowaOsobe(vector <Osoba> &osoby, int idZalogowanegoUzytkownika, int idOstatniegoAdresata);
void dodajNowaOsobeDoPlikuTekstowego(vector <Osoba> &osoby, int idZalogowanegoUzytkownika, int idOstatniegoAdresata);

void edytujAdresata(vector <Osoba> &osoby);
void edytujKsiazkeAdresowa(string edytowanyTekst);
void usunAdresata(vector <Osoba> &osoby);
void usunAdresataZKsiazkiAdresowej(vector <Osoba> &osoby, int idUsuwanegoAdresata);
void zapiszVectorDoPliku(vector <Osoba> &osoby, int idZalogowanegoUzytkownika);

void wyszukajPoImieniu(vector <Osoba> &osoby);
void wyszukajPoNazwisku(vector <Osoba> &osoby);
void wyswietlWszystkieOsobyDlaZalogowanegoUzytkownika(vector <Osoba> &osoby, int idZalogowanegoUzytkownika);

void rejestracja(vector <Uzytkownik> &uzytkownicy);
void zmianaHasla(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika);
void wczytajZapisanychUzytkownikowZPlikuTekstowego(vector <Uzytkownik> &uzytkownicy);
void dodanieNowegoUzytkownikaDoPlikuTekstowego(vector <Uzytkownik> &uzytkownicy);
void zapiszVectorDoPlikuUzytkownicy(vector <Uzytkownik> &uzytkownicy);
int logowanie(vector <Uzytkownik> &uzytkownicy);
Uzytkownik pobierzDaneUzytkownika(string wczytanaLinia);

void wypiszMenuPoZalogowaniu();
void wypiszMenuPoStarcieProgramu();
void wczytajMenuRejestracji(char wyborPoleceniaDoWykonania, vector <Uzytkownik> &uzytkownicy);

int pobierzIdUzytkownikaZLiniiTekstu(string tekst);
int pobierzIdAdresataZLinii(string tekst);

int main()
{
    vector <Osoba> osoby;
    vector <Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    int idOstatniegoAdresata = 0;
    char wyborPoleceniaDoWykonania;
    bool powtorzenieDzialania = true;

    wczytajZapisanychUzytkownikowZPlikuTekstowego(uzytkownicy);

    while(true)
    {
        powtorzenieDzialania = true;
        if (idZalogowanegoUzytkownika == 0)
        {
            wypiszMenuPoStarcieProgramu();
            cin >> wyborPoleceniaDoWykonania;
            switch (wyborPoleceniaDoWykonania)
            {
            case '1':
                rejestracja(uzytkownicy);
                break;
            case '2':
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                break;
            case '9':
                exit(0);
                break;
            default:
                cout << "Nieprawidlowy wybor, sprobuj jeszcze raz\n";
                system("pause");
                break;
            }
        }
        else
        {
            idOstatniegoAdresata = wczytajZapisaneOsobyZPlikuTekstowego(osoby, idZalogowanegoUzytkownika);

            while (powtorzenieDzialania)
            {
                wypiszMenuPoZalogowaniu();
                cin >> wyborPoleceniaDoWykonania;

                switch (wyborPoleceniaDoWykonania)
                {
                case '1':
                    idOstatniegoAdresata = dodajNowaOsobe(osoby, idZalogowanegoUzytkownika, idOstatniegoAdresata);
                    break;
                case '2':
                    wyszukajPoImieniu(osoby);
                    break;
                case '3':
                    wyszukajPoNazwisku(osoby);
                    break;
                case '4':
                    wyswietlWszystkieOsobyDlaZalogowanegoUzytkownika(osoby, idZalogowanegoUzytkownika);
                    break;
                case '5':
                    usunAdresata(osoby);
                    break;
                case '6':
                    edytujAdresata(osoby);
                    break;
                case '7':
                    zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
                    break;
                case '8':
                    idZalogowanegoUzytkownika = 0;
                    powtorzenieDzialania = false;
                    osoby.clear();
                    break;
                case '9':
                    exit(0);
                    break;
                default:
                    cout << "Nieprawidlowy wybor, sprobuj jeszcze raz\n";
                    system("pause");
                    break;
                }
            }
        }
    }
    return 0;
}

int wczytajZapisaneOsobyZPlikuTekstowego(vector <Osoba> &osoby, int idZalogowanegoUzytkownika)
{
    int idUzytkownikaPobraneZLinii, idOstatniegoAdresata = 0;
    Osoba wczytanaOsoba;

    string liniaWczytanaZPlikuTekstowego = "", pojedynczaDanaOsoby = "";

    fstream plik;
    plik.open("Adresaci.txt", ios::in);

    if (plik.good())
    {
        while(getline(plik,liniaWczytanaZPlikuTekstowego))
        {
            idUzytkownikaPobraneZLinii = pobierzIdUzytkownikaZLiniiTekstu(liniaWczytanaZPlikuTekstowego);
            if (idUzytkownikaPobraneZLinii == idZalogowanegoUzytkownika)
            {
                wczytanaOsoba = pobierzDaneZapisanejOsoby(liniaWczytanaZPlikuTekstowego);
                osoby.push_back(wczytanaOsoba);
            }
            idOstatniegoAdresata = pobierzIdAdresataZLinii(liniaWczytanaZPlikuTekstowego);
        }
        plik.close();
    }
    return idOstatniegoAdresata;
}

Osoba pobierzDaneZapisanejOsoby(string wczytanaLinia)
{
    Osoba osoba;
    string pojedynczaDanaOsoby = "";
    int indeksWLiniiDlaDanejAdresata = 1, dlugoscLinii = wczytanaLinia.length();

    for (int pozycjaZnaku = 0; pozycjaZnaku < dlugoscLinii; pozycjaZnaku++)
    {
        if (wczytanaLinia[pozycjaZnaku] != '|')
            pojedynczaDanaOsoby += wczytanaLinia[pozycjaZnaku];
        else
        {
            switch(indeksWLiniiDlaDanejAdresata)
            {
            case 1:
                osoba.idAdresata = atoi(pojedynczaDanaOsoby.c_str());
                break;
            case 2:
                osoba.idZalogowanegoUzytkownika = atoi(pojedynczaDanaOsoby.c_str());
                break;
            case 3:
                osoba.imie = pojedynczaDanaOsoby;
                break;
            case 4:
                osoba.nazwisko = pojedynczaDanaOsoby;
                break;
            case 5:
                osoba.numerTelefonu = pojedynczaDanaOsoby;
                break;
            case 6:
                osoba.email = pojedynczaDanaOsoby;
                break;
            case 7:
                osoba.adres = pojedynczaDanaOsoby;
                break;
            }
            pojedynczaDanaOsoby = "";
            indeksWLiniiDlaDanejAdresata++;
        }
    }
    return osoba;
}

int dodajNowaOsobe(vector <Osoba> &osoby, int idZalogowanegoUzytkownika, int idOstatniegoAdresata)
{
    string imie, nazwisko, numerTelefonu, email, adres;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, numerTelefonu);
    cout << "Podaj email: ";
    cin >> email;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, adres);

    Osoba nowaOsoba;

    if (osoby.size() == 0)
        nowaOsoba.idAdresata = osoby.size() + 1;

    nowaOsoba.idAdresata = ++idOstatniegoAdresata;
    nowaOsoba.idZalogowanegoUzytkownika = idZalogowanegoUzytkownika;
    nowaOsoba.imie = imie;
    nowaOsoba.nazwisko = nazwisko;
    nowaOsoba.numerTelefonu = numerTelefonu;
    nowaOsoba.email = email;
    nowaOsoba.adres = adres;

    osoby.push_back(nowaOsoba);
    dodajNowaOsobeDoPlikuTekstowego(osoby, idZalogowanegoUzytkownika, idOstatniegoAdresata);
    return idOstatniegoAdresata;
}

void dodajNowaOsobeDoPlikuTekstowego(vector <Osoba> &osoby, int idZalogowanegoUzytkownika, int idOstatniegoAdresata)
{
    fstream plik;
    plik.open("Adresaci.txt", ios::out | ios::app);

    if (plik.good())
    {
        if (osoby.size() == 0)
        {
            plik << osoby[osoby.size()].idAdresata << "|";
            plik << idZalogowanegoUzytkownika << "|";
        }
        else
        {
            plik << idOstatniegoAdresata << "|";
            plik << idZalogowanegoUzytkownika << "|";
        }
        plik << osoby.back().imie << "|";
        plik << osoby.back().nazwisko << "|";
        plik << osoby.back().numerTelefonu << "|";
        plik << osoby.back().email << "|";
        plik << osoby.back().adres << "|" << endl;

        cout << "Osoba zostala poprawnie dodana do ksiazki adresowej" << endl;
        system("pause");
        plik.close();
    }
    else
    {
        cout << "Plik uszkodzony lub nie istnieje - nie mozna otworzyc" << endl;
        system("pause");
    }
}

void wyswietlWszystkieOsobyDlaZalogowanegoUzytkownika(vector <Osoba> &osoby, int idZalogowanegoUzytkownika)
{
    int iloscOsob = osoby.size();
    if (iloscOsob)
    {
        for (int i = 0; i < iloscOsob; i++)
        {
            cout << "Id: " << osoby[i].idAdresata << endl;
            cout << "Imie: " << osoby[i].imie << endl;
            cout << "Nazwisko: " << osoby[i].nazwisko << endl;
            cout << "Numer telefonu: " << osoby[i].numerTelefonu << endl;
            cout << "Email: " << osoby[i].email << endl;
            cout << "Adres: " << osoby[i].adres << endl;
            cout << endl;
        }
        system("pause");
    }
    else
    {
        cout << "Plik nie istnieje lub brak osob w ksiazce adresowej" << endl;
        system("pause");
    }
}

void wyszukajPoImieniu(vector <Osoba> &osoby)
{
    int iloscOsob = osoby.size();
    if (iloscOsob)
    {
        string szukaneImie;
        system("cls");
        cout << "Wpisz szukane imie: " << endl;
        cin >> szukaneImie;
        int licznikImion = 0;

        for (int i = 0; i < iloscOsob; i++)
        {
            if (szukaneImie == osoby[i].imie)
            {
                cout << "Id: " << osoby[i].idAdresata << endl;
                cout << "Imie: " << osoby[i].imie << endl;
                cout << "Nazwisko: " << osoby[i].nazwisko << endl;
                cout << "Numer telefonu: " << osoby[i].numerTelefonu << endl;
                cout << "Email: " << osoby[i].email << endl;
                cout << "Adres: " << osoby[i].adres << endl;
                cout << endl;
                licznikImion++;
            }
        }
        if (licznikImion == 0)
        {
            cout << "Osoba o podanym imieniu nie jest w bazie" << endl;
        }
        system("pause");
    }
    else
    {
        cout << "Plik nie istnieje lub brak osob w ksiazce adresowej" << endl;
        system("pause");
    }
}

void wyszukajPoNazwisku(vector <Osoba> &osoby)
{
    int iloscOsob = osoby.size();
    if (iloscOsob)
    {
        string szukaneNazwisko;
        system("cls");
        cout << "Wpisz szukane nazwisko: " << endl;
        cin >> szukaneNazwisko;
        int licznikNazwisk = 0;

        for (int i = 0; i < iloscOsob; i++)
        {
            if (szukaneNazwisko == osoby[i].nazwisko)
            {
                cout << "Id: " << osoby[i].idAdresata << endl;
                cout << "Imie: " << osoby[i].imie << endl;
                cout << "Nazwisko: " << osoby[i].nazwisko << endl;
                cout << "Numer telefonu: " << osoby[i].numerTelefonu << endl;
                cout << "Email: " << osoby[i].email << endl;
                cout << "Adres: " << osoby[i].adres << endl;
                cout << endl;
                licznikNazwisk++;
            }
        }
        if (licznikNazwisk == 0)
        {
            cout << "Osoba o podanym nazwisku nie jest w bazie" << endl;
        }
        system("pause");
    }
    else
    {
        cout << "Plik nie istnieje lub brak osob w ksiazce adresowej" << endl;
        system("pause");
    }
}

void zapiszVectorDoPliku(vector <Osoba> &osoby, int idZalogowanegoUzytkownika)
{
    ofstream plik;
    plik.open("Adresaci.txt", std::ofstream::out | std::ofstream::trunc);
    int iloscOsob = osoby.size();

    if (plik.good())
    {
        for (int i=0; i < iloscOsob; i++)
        {
            plik << osoby[i].idAdresata << "|";
            plik << idZalogowanegoUzytkownika << "|";
            plik << osoby[i].imie << "|" << endl;
            plik << osoby[i].nazwisko << "|";
            plik << osoby[i].numerTelefonu << "|";
            plik << osoby[i].email << "|";
            plik << osoby[i].adres << "|" << endl;
        }
        cout << "Aktualizacja osob w ksiazce adresowej poprawna" << endl;
        system("pause");
        plik.close();
    }
    else
    {
        cout << "Plik uszkodzony lub nie istnieje - nie mozna otworzyc" << endl;
        system("pause");
    }
}

void edytujAdresata(vector <Osoba> &osoby)
{
    system("cls");
    int id, iloscOsob = osoby.size(), statusPrawidlowegoID = 0;
    string wpisane_id, edytowaneDane = "";
    cout << "Podaj ID adresata: ";
    cin >> wpisane_id;
    id = konwersjaStringNaInt(wpisane_id);

    int wybor;
    string wpisanyTekstDoEdycji = "";

    for (int i=0; i < iloscOsob; i++)
    {
        if (osoby[i].idAdresata == id)
        {
            statusPrawidlowegoID = 1;
            cout << "Ktore dane chcesz zaktualizowac:" << endl;
            cout << "1: Imie" << endl;
            cout << "2: Nazwisko" << endl;
            cout << "3: Numer telefonu" << endl;
            cout << "4: Email" << endl;
            cout << "5: Adres" << endl;

            cin >> wybor;
            switch (wybor)
            {
            case 1:
                cout << "Wpisz imie: " << endl;
                cin >> wpisanyTekstDoEdycji;
                osoby[i].imie = wpisanyTekstDoEdycji;
                edytowaneDane = zapiszEdytowaneDaneAdresata(osoby[i]);
                edytujKsiazkeAdresowa(edytowaneDane);
                break;
            case 2:
                cout << "Wpisz nazwisko: " << endl;
                cin >> wpisanyTekstDoEdycji;
                osoby[i].nazwisko = wpisanyTekstDoEdycji;
                edytowaneDane = zapiszEdytowaneDaneAdresata(osoby[i]);
                edytujKsiazkeAdresowa(edytowaneDane);
                break;
            case 3:
                cout << "Wpisz numer telefonu: " << endl;
                cin.sync();
                getline(cin, wpisanyTekstDoEdycji);
                osoby[i].numerTelefonu = wpisanyTekstDoEdycji;
                edytowaneDane = zapiszEdytowaneDaneAdresata(osoby[i]);
                edytujKsiazkeAdresowa(edytowaneDane);
                break;
            case 4:
                cout << "Wpisz Email: " << endl;
                cin >> wpisanyTekstDoEdycji;
                osoby[i].email = wpisanyTekstDoEdycji;
                edytowaneDane = zapiszEdytowaneDaneAdresata(osoby[i]);
                edytujKsiazkeAdresowa(edytowaneDane);
                break;
            case 5:
                cout << "Wpisz Adres: " << endl;
                cin.sync();
                getline(cin, wpisanyTekstDoEdycji);
                osoby[i].adres = wpisanyTekstDoEdycji;
                edytowaneDane = zapiszEdytowaneDaneAdresata(osoby[i]);
                edytujKsiazkeAdresowa(edytowaneDane);
                break;
            }
            cout << "Dane zostaly zmienione" << endl;
        }
    }
    if (statusPrawidlowegoID == 0)
        cout << "Wpisales ID, ktorego nie ma w bazie" << endl;
    system("pause");
}

void usunAdresata(vector <Osoba> &osoby)
{
    system("cls");
    int id, iloscOsob = osoby.size();
    string wpisane_id;
    int statusPrawidlowegoID = 0;
    cout << "Podaj ID adresata: ";
    cin >> wpisane_id;
    id = konwersjaStringNaInt(wpisane_id);

    for (int i=0; i < iloscOsob; i++)
    {
        if (osoby[i].idAdresata == id)
        {
            statusPrawidlowegoID = 1;
            char potwierdzenie;
            cout << "Czy na pewno chcesz usunac osobe o podanym ID? (t/n)" << endl;
            cin >> potwierdzenie;
            if (potwierdzenie == 't')
            {
                osoby.erase(osoby.begin() + i);
                usunAdresataZKsiazkiAdresowej(osoby, id);
                system("pause");
            }
            else if (potwierdzenie == 'n')
            {
                cout << "Nie usunales osoby o podanym ID" << endl;
                system("pause");
            }
        }
    }
    if (statusPrawidlowegoID == 0)
    {
        cout << "Wpisales ID, ktorego nie ma w bazie" << endl;
        system("pause");
    }
}

int konwersjaStringNaInt(string wyraz)
{
    int i = atoi(wyraz.c_str());
    return i;
}

void wypiszMenuPoStarcieProgramu()
{
    system("cls");
    cout << " KSIAZKA ADRESOWA - Zarejestruj sie lub zaloguj " << endl;
    cout << "-------------------------" << endl;
    cout << "1. Rejestracja" << endl;
    cout << "2. Logowanie" << endl;
    cout << "9. Zakoncz program" << endl;
    cout << "-------------------------" << endl;
    cout << "Wybierz 1, 2 lub 9: " << endl;
}

void wypiszMenuPoZalogowaniu()
{
    system("cls");
    cout << ">>> KSIAZKA ADRESOWA - MENU <<<" << endl;
    cout << "-------------------------" << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "-------------------------" << endl;
    cout << "7. Zmien haslo" << endl;
    cout << "8. Wyloguj sie" << endl;
    cout << "9. Koniec programu" << endl;
}

void wczytajZapisanychUzytkownikowZPlikuTekstowego(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik wczytanyUzytkownik;

    string liniaWczytanaZPlikuTekstowego = "";
    string pojedynczaInformacjaOUzytkowniku = "";

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good())
    {
        while(getline(plik,liniaWczytanaZPlikuTekstowego))
        {
            wczytanyUzytkownik = pobierzDaneUzytkownika(liniaWczytanaZPlikuTekstowego);
            uzytkownicy.push_back(wczytanyUzytkownik);
        }
        plik.close();
    }
}

Uzytkownik pobierzDaneUzytkownika(string wczytanaLinia)
{
    Uzytkownik uzytkownik;
    string pojedynczaDanaUzytkownika = "";
    int indeksWLiniiDanejUzytkownika = 1, dlugoscWczytanejLinii = wczytanaLinia.length();

    for (int pozycjaZnaku = 0; pozycjaZnaku < dlugoscWczytanejLinii; pozycjaZnaku++)
    {
        if (wczytanaLinia[pozycjaZnaku] != '|')
        {
            pojedynczaDanaUzytkownika += wczytanaLinia[pozycjaZnaku];
        }
        else
        {
            switch(indeksWLiniiDanejUzytkownika)
            {
            case 1:
                uzytkownik.id = atoi(pojedynczaDanaUzytkownika.c_str());
                break;
            case 2:
                uzytkownik.nazwaUzytkownika = pojedynczaDanaUzytkownika;
                break;
            case 3:
                uzytkownik.hasloUzytkownika = pojedynczaDanaUzytkownika;
                break;
            }
            pojedynczaDanaUzytkownika = "";
            indeksWLiniiDanejUzytkownika++;
        }
    }
    return uzytkownik;
}

void rejestracja(vector <Uzytkownik> &uzytkownicy)
{
    string nazwaUzytkownika, hasloUzytkownika;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwaUzytkownika;
    int i = 0, liczbaUzytkownikow = uzytkownicy.size();
    while ( i < liczbaUzytkownikow )
    {
        if ( uzytkownicy[i].nazwaUzytkownika == nazwaUzytkownika )
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwaUzytkownika;
            i = 0;
        }
        else
            i++;
    }
    cout << "Podaj haslo: ";
    cin >> hasloUzytkownika;

    Uzytkownik nowyUzytkownik;

    nowyUzytkownik.nazwaUzytkownika = nazwaUzytkownika;
    nowyUzytkownik.hasloUzytkownika = hasloUzytkownika;

    if (uzytkownicy.size() == 0)
        nowyUzytkownik.id = uzytkownicy.size() + 1;
    else
        nowyUzytkownik.id = uzytkownicy[uzytkownicy.size()-1].id + 1;

    uzytkownicy.push_back(nowyUzytkownik);

    cout << "Konto zalozone" << endl;
    dodanieNowegoUzytkownikaDoPlikuTekstowego(uzytkownicy);
}

void dodanieNowegoUzytkownikaDoPlikuTekstowego(vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    int numerIndeksuVectoraDoDodania = uzytkownicy.size() - 1;

    if (plik.good())
    {
        if (uzytkownicy.size() == 0)
            plik << uzytkownicy[uzytkownicy.size()].id << "|";
        else
            plik << uzytkownicy[numerIndeksuVectoraDoDodania].id << "|";

        plik << uzytkownicy[numerIndeksuVectoraDoDodania].nazwaUzytkownika << "|";
        plik << uzytkownicy[numerIndeksuVectoraDoDodania].hasloUzytkownika << "|" << endl;

        cout << "Uzytkownik zostal poprawnie przypisany do bazy" << endl;
        system("pause");
        plik.close();
    }
}

int logowanie(vector <Uzytkownik> &uzytkownicy)
{
    bool powtorzenie = true;
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;
    int i = 0, liczbaUzytkownikow = uzytkownicy.size();
    while (i < liczbaUzytkownikow)
    {
        if(uzytkownicy[i].nazwaUzytkownika == nazwa)
        {
            while(powtorzenie)
            {
                for (int proby = 0; proby < 3; proby++)
                {
                    cout << "Podaj haslo. Pozostalo prob " << 3-proby << ": ";
                    cin >> haslo;
                    if(uzytkownicy[i].hasloUzytkownika == haslo)
                    {
                        cout << "Zalogowales sie" << endl;
                        system("pause");
                        powtorzenie = false;
                        return uzytkownicy[i].id;
                    }
                }
                cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
                Sleep(3000);
                powtorzenie = true;
            }
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    system("pause");
    return 0;
}

void zmianaHasla(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    int liczbaUzytkownikow = uzytkownicy.size();
    string haslo = "";
    cout << "Podaj nowe haslo: ";
    cin >> haslo;
    for (int i = 0; i < liczbaUzytkownikow; i++)
    {
        if(uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].hasloUzytkownika = haslo;
            cout << "Haslo zostalo zmienione" << endl;
            system("pause");
        }
        zapiszVectorDoPlikuUzytkownicy(uzytkownicy);
    }
    cout << "Aktualizacja danych przebiegla poprawnie" << endl;
    system("pause");
}

void zapiszVectorDoPlikuUzytkownicy(vector <Uzytkownik> &uzytkownicy)
{
    int liczbaUzytkownikow = uzytkownicy.size();
    ofstream plik;
    plik.open("Uzytkownicy.txt", std::ofstream::out | std::ofstream::trunc);

    if (plik.good())
    {
        for (int i=0; i < liczbaUzytkownikow; i++)
        {
            plik << uzytkownicy[i].id << "|";
            plik << uzytkownicy[i].nazwaUzytkownika << "|";
            plik << uzytkownicy[i].hasloUzytkownika << "|" << endl;
        }
        plik.close();
    }
    else
    {
        cout << "Plik uszkodzony lub nie istnieje - nie mozna otworzyc" << endl;
        system("pause");
    }
}

void wczytajMenuRejestracji(char wyborPoleceniaDoWykonania, vector <Uzytkownik> &uzytkownicy)
{
    wczytajZapisanychUzytkownikowZPlikuTekstowego(uzytkownicy);
    int idZalogowanegoUzytkownika = 0;

    if (wyborPoleceniaDoWykonania == '1')
    {
        rejestracja (uzytkownicy);
        dodanieNowegoUzytkownikaDoPlikuTekstowego(uzytkownicy);
        wypiszMenuPoStarcieProgramu();
    }
    else if (wyborPoleceniaDoWykonania == '2')
    {
        idZalogowanegoUzytkownika = logowanie(uzytkownicy);
        cout << "Zalogowales sie jako uzytkownik z id: " << idZalogowanegoUzytkownika;
        system("pause");
        wypiszMenuPoZalogowaniu();
    }
    else if (wyborPoleceniaDoWykonania == '9')
        exit(0);
}

void usunPlik(string calkowitaNazwaPlikuZRozszerzeniem)
{
    if (remove(calkowitaNazwaPlikuZRozszerzeniem.c_str()) == 0) {}
    else
        cout << "Nie udalo sie usunac pliku: " << calkowitaNazwaPlikuZRozszerzeniem << endl;
}

void zmienNazwePliku(string staraNazwa, string nowaNazwa)
{
    if (rename(staraNazwa.c_str(), nowaNazwa.c_str()) == 0) {}
    else
        cout << "Nazwa pliku nie zostala zmieniona: " << staraNazwa << endl;
}

int pobierzIdUzytkownikaZLiniiTekstu(string tekst)
{
    int IdUzytkownikaOdczytaneZLinii = 0;
    int pozycjaZnaku = 0;
    string odczytaneIdUzytkownikaZTekstu = "";
    while (tekst[pozycjaZnaku] != '|')
    {
        pozycjaZnaku++;
    }
    pozycjaZnaku++;
    while (tekst[pozycjaZnaku] != '|')
    {
        odczytaneIdUzytkownikaZTekstu += tekst[pozycjaZnaku];
        pozycjaZnaku++;
    }
    IdUzytkownikaOdczytaneZLinii = konwersjaStringNaInt(odczytaneIdUzytkownikaZTekstu);

    return IdUzytkownikaOdczytaneZLinii;
}

int pobierzIdAdresataZLinii(string tekst)
{
    int IdAdresataOdczytaneZLinii = 0;
    int pozycjaZnaku = 0;
    string odczytaneIdUzytkownikaZTekstu = "";
    while (tekst[pozycjaZnaku] != '|')
    {
        odczytaneIdUzytkownikaZTekstu += tekst[pozycjaZnaku];
        pozycjaZnaku++;
    }
    IdAdresataOdczytaneZLinii = konwersjaStringNaInt(odczytaneIdUzytkownikaZTekstu);

    return IdAdresataOdczytaneZLinii;
}

string zapiszEdytowaneDaneAdresata(Osoba osoba)
{
    string edytowaneDane = "";
    edytowaneDane += to_string(osoba.idAdresata) + '|';
    edytowaneDane += to_string(osoba.idZalogowanegoUzytkownika) + '|';
    edytowaneDane += osoba.imie + '|';
    edytowaneDane += osoba.nazwisko + '|';
    edytowaneDane += osoba.numerTelefonu + '|';
    edytowaneDane += osoba.email + '|';
    edytowaneDane += osoba.adres + '|';

    return edytowaneDane;
}

void edytujKsiazkeAdresowa(string edytowanyTekst)
{
    string liniaTekstuOdczytanegoZPliku;
    int idEdytowanegoAdresata = pobierzIdAdresataZLinii(edytowanyTekst);
    fstream plik, plikTymczasowy;
    plik.open("Adresaci.txt", ios::in);
    plikTymczasowy.open("tymczasowy.txt", ios::out);

    while(getline(plik, liniaTekstuOdczytanegoZPliku))
    {
        int idAdresataZPliku = pobierzIdAdresataZLinii(liniaTekstuOdczytanegoZPliku);
        if (idEdytowanegoAdresata == idAdresataZPliku)
            plikTymczasowy << edytowanyTekst << endl;
        else
            plikTymczasowy << liniaTekstuOdczytanegoZPliku << endl;
    }
    plik.close();
    plikTymczasowy.close();

    usunPlik("Adresaci.txt");
    zmienNazwePliku("tymczasowy.txt","Adresaci.txt");
}

void usunAdresataZKsiazkiAdresowej(vector <Osoba> &osoby, int idUsuwanegoAdresata)
{
    string liniaTekstuOdczytanegoZPliku;
    fstream plik, plikTymczasowy;
    plik.open("Adresaci.txt", ios::in);
    plikTymczasowy.open("tymczasowy.txt", ios::out);

    while(getline(plik, liniaTekstuOdczytanegoZPliku))
    {
        int idAdresataZPliku = pobierzIdAdresataZLinii(liniaTekstuOdczytanegoZPliku);
        if (idUsuwanegoAdresata != idAdresataZPliku)
            plikTymczasowy << liniaTekstuOdczytanegoZPliku << endl;
    }
    plik.close();
    plikTymczasowy.close();

    usunPlik("Adresaci.txt");
    zmienNazwePliku("tymczasowy.txt","Adresaci.txt");
}

