#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <vector>

using namespace std;

struct Osoba
{
    int id = 0;
    string imie = "";
    string nazwisko = "";
    string numerTelefonu = "";
    string email = "";
    string adres = "";
};

int konwersjaStringNaInt(string wyraz);
vector <Osoba> wczytajZapisaneOsobyZPlikuTekstowego();
Osoba pobierzDaneZapisanejOsoby (string wczytanaLinia);

vector <Osoba> dodajNowaOsobeDoVectora (vector <Osoba> osoby, int iloscOsobWKsiazceAdresowej);
void dodajNowaOsobeDoPlikuTekstowego(vector <Osoba> osoby);

vector <Osoba> usunAdresata (vector <Osoba> osoby);
vector <Osoba> edytujAdresata (vector <Osoba> osoby);
void zapiszVectorDoPliku (vector <Osoba> osoby);

void wyswietlWszystkieOsoby (vector <Osoba> osoby);
void wyszukajPoImieniu (vector <Osoba> osoby);
void wyszukajPoNazwisku (vector <Osoba> osoby);
void wyszukajZapisaneOsobyPoImieniuNazwisku (vector <Osoba> osoby);

int main()
{
    vector <Osoba> osoby;
    int iloscOsobWKsiazceAdresowej = 0;
    char wyborPoleceniaDoWykonania;

    osoby = wczytajZapisaneOsobyZPlikuTekstowego();
    iloscOsobWKsiazceAdresowej = osoby.size();

    while(1)
    {
        system("cls");
        cout << ">>> KSIAZKA ADRESOWA <<<" << endl << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Koniec programu" << endl;

        cin >> wyborPoleceniaDoWykonania;

        osoby = wczytajZapisaneOsobyZPlikuTekstowego();

        switch (wyborPoleceniaDoWykonania)
        {
        case '1':
            osoby = dodajNowaOsobeDoVectora(osoby, iloscOsobWKsiazceAdresowej);
            dodajNowaOsobeDoPlikuTekstowego(osoby);
            break;
        case '2':
            wyszukajPoImieniu(osoby);
            break;
        case '3':
            wyszukajPoNazwisku(osoby);
            break;
        case '4':
            wyswietlWszystkieOsoby(osoby);
            break;
        case '5':
            usunAdresata(osoby);
            break;
        case '6':
            edytujAdresata(osoby);
            break;
        case '9':
            exit(0);
        }
    }
    return 0;
}

vector <Osoba> wczytajZapisaneOsobyZPlikuTekstowego()
{
    vector <Osoba> osoby;
    Osoba wczytanaOsoba;

    string liniaWczytanaZPlikuTekstowego = "";
    string pojedynczaDanaOsoby = "";
    int indeksWLiniiDlaDanejAdresata = 1;

    fstream plik;
    plik.open("Ksiazka_adresowa_PK.txt", ios::in);

    if (plik.good())
    {
        while(getline(plik,liniaWczytanaZPlikuTekstowego))
        {
            wczytanaOsoba = pobierzDaneZapisanejOsoby(liniaWczytanaZPlikuTekstowego);
            osoby.push_back(wczytanaOsoba);
        }
        plik.close();
    }
    return osoby;
}

Osoba pobierzDaneZapisanejOsoby (string wczytanaLinia)
{
    Osoba osoba;
    string pojedynczaDanaOsoby = "";
    int indeksWLiniiDlaDanejAdresata = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < wczytanaLinia.length(); pozycjaZnaku++)
    {
        if (wczytanaLinia[pozycjaZnaku] != '|')
        {
            pojedynczaDanaOsoby += wczytanaLinia[pozycjaZnaku];
        }
        else
        {
            switch(indeksWLiniiDlaDanejAdresata)
            {
            case 1:
                osoba.id = atoi(pojedynczaDanaOsoby.c_str());
                break;
            case 2:
                osoba.imie = pojedynczaDanaOsoby;
                break;
            case 3:
                osoba.nazwisko = pojedynczaDanaOsoby;
                break;
            case 4:
                osoba.numerTelefonu = pojedynczaDanaOsoby;
                break;
            case 5:
                osoba.email = pojedynczaDanaOsoby;
                break;
            case 6:
                osoba.adres = pojedynczaDanaOsoby;
                break;
            }
            pojedynczaDanaOsoby = "";
            indeksWLiniiDlaDanejAdresata++;
        }
    }
    return osoba;
}

vector <Osoba> dodajNowaOsobeDoVectora (vector <Osoba> osoby, int iloscOsobWKsiazceAdresowej)
{
    iloscOsobWKsiazceAdresowej = osoby.size();
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

    if (iloscOsobWKsiazceAdresowej == 0)
        nowaOsoba.id = iloscOsobWKsiazceAdresowej + 1;
    else
        nowaOsoba.id = osoby[iloscOsobWKsiazceAdresowej-1].id + 1;

    nowaOsoba.imie = imie;
    nowaOsoba.nazwisko = nazwisko;
    nowaOsoba.numerTelefonu = numerTelefonu;
    nowaOsoba.email = email;
    nowaOsoba.adres = adres;

    osoby.push_back(nowaOsoba);

    return osoby;
}

void dodajNowaOsobeDoPlikuTekstowego(vector <Osoba> osoby)
{
    int iloscOsobWKsiazceAdresowej = osoby.size();

    cout << "Ilosc osob w ksiazce adresowej: " << iloscOsobWKsiazceAdresowej << endl;

    int numerIndeksuVectoraDoDodania = iloscOsobWKsiazceAdresowej - 1;

    fstream plik;
    plik.open("Ksiazka_adresowa_PK.txt", ios::out | ios::app);

    if (plik.good())
    {
        if (iloscOsobWKsiazceAdresowej == 0)
            plik << osoby[iloscOsobWKsiazceAdresowej].id << "|";
        else
            plik << osoby[numerIndeksuVectoraDoDodania].id << "|";

        plik << osoby[numerIndeksuVectoraDoDodania].imie << "|";
        plik << osoby[numerIndeksuVectoraDoDodania].nazwisko << "|";
        plik << osoby[numerIndeksuVectoraDoDodania].numerTelefonu << "|";
        plik << osoby[numerIndeksuVectoraDoDodania].email << "|";
        plik << osoby[numerIndeksuVectoraDoDodania].adres << "|" << endl;

        cout << "Osoba zostala poprawnie dodana do ksiazki adresowej" << endl;
        Sleep(2000);
        plik.close();
    }
    else
    {
        cout << "Plik uszkodzony lub nie istnieje - nie mozna otworzyc" << endl;
        system("pause");
    }
}

void wyswietlWszystkieOsoby (vector <Osoba> osoby)
{
    if (osoby.size())
    {
        for (int i = 0; i < osoby.size(); i++)
        {
            cout << "Id: " << osoby[i].id << endl;
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

void wyszukajPoImieniu (vector <Osoba> osoby)
{
    if (osoby.size())
    {
        string szukaneImie;

        system("cls");
        cout << "Wpisz szukane imie: " << endl;
        cin >> szukaneImie;
        int licznikImion = 0;

        for (int i = 0; i < osoby.size(); i++)
        {
            if ( szukaneImie == osoby[i].imie )
            {
                cout << "Id: " << osoby[i].id << endl;
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

void wyszukajPoNazwisku (vector <Osoba> osoby)
{
    if (osoby.size())
    {
        string szukaneNazwisko;

        system("cls");
        cout << "Wpisz szukane nazwisko: " << endl;
        cin >> szukaneNazwisko;
        int licznikNazwisk = 0;

        for (int i = 0; i < osoby.size(); i++)
        {
            if ( szukaneNazwisko == osoby[i].nazwisko )
            {
                cout << "Id: " << osoby[i].id << endl;
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

void wyszukajZapisaneOsobyPoImieniuNazwisku (vector <Osoba> osoby)
{
    if (osoby.size())
    {
        cout << "1. Wyszukaj wpisujac imie:" << endl;
        cout << "2. Wyszukaj wpisujac nazwisko:" << endl;
        char wyborPoleceniaDoWykonania;
        cin >> wyborPoleceniaDoWykonania;

        switch(wyborPoleceniaDoWykonania)
        {
        case '1':
            wyszukajPoImieniu (osoby);
            system("pause");
            break;

        case '2':
            wyszukajPoNazwisku (osoby);
            system("pause");
            break;
        }
    }
    else
    {
        cout << "Plik nie istnieje lub brak osob w ksiazce adresowej" << endl;
        system("pause");
    }
}

vector <Osoba> usunAdresata (vector <Osoba> osoby)
{
    system("cls");
    int id;
    string wpisane_id;
    int statusPrawidlowegoID = 0;
    cout << "Podaj ID adresata: ";
    cin >> wpisane_id;
    id = konwersjaStringNaInt(wpisane_id);

    for (int i=0; i < osoby.size(); i++)
    {
        if (osoby[i].id == id)
        {
            statusPrawidlowegoID = 1;
            char potwierdzenie;
            cout << "Czy na pewno chcesz usunac osobe o podanym ID? (t/n)" << endl;
            cin >> potwierdzenie;
            if (potwierdzenie == 't')
            {
                osoby.erase(osoby.begin() + i);
                zapiszVectorDoPliku(osoby);
            }
            else if (potwierdzenie == 'n')
            {
                cout << "Nie usunales osoby o podanym ID" << endl;
                Sleep(2000);
            }
        }
    }
    if (statusPrawidlowegoID == 0)
    {
        cout << "Wpisales ID, ktorego nie ma w bazie" << endl;
        Sleep(2000);
    }
    return osoby;
}

void zapiszVectorDoPliku (vector <Osoba> osoby)
{
    ofstream plik;
    plik.open("Ksiazka_adresowa_PK.txt", std::ofstream::out | std::ofstream::trunc);

    if (plik.good())
    {
        for (int i=0; i < osoby.size(); i++)
        {
            plik << osoby[i].id << "|";
            plik << osoby[i].imie << "|";
            plik << osoby[i].nazwisko << "|";
            plik << osoby[i].numerTelefonu << "|";
            plik << osoby[i].email << "|";
            plik << osoby[i].adres << "|" << endl;
        }
        cout << "Aktualizacja osob w ksiazce adresowej poprawna" << endl;
        Sleep(2000);
        plik.close();
    }
    else
    {
        cout << "Plik uszkodzony lub nie istnieje - nie mozna otworzyc" << endl;
        system("pause");
    }
}

vector <Osoba> edytujAdresata (vector <Osoba> osoby)
{
    system("cls");
    int id;
    string wpisane_id;
    int statusPrawidlowegoID = 0;
    cout << "Podaj ID adresata: ";
    cin >> wpisane_id;
    id = konwersjaStringNaInt(wpisane_id);

    int wybor;
    string wpisanyTekstDoEdycji = "";

    for (int i=0; i < osoby.size(); i++)
    {
        if (osoby[i].id == id)
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
                break;
            case 2:
                cout << "Wpisz nazwisko: " << endl;
                cin >> wpisanyTekstDoEdycji;
                osoby[i].nazwisko = wpisanyTekstDoEdycji;
                break;
            case 3:
                cout << "Wpisz numer telefonu: " << endl;
                cin.sync();
                getline(cin, wpisanyTekstDoEdycji);
                osoby[i].numerTelefonu = wpisanyTekstDoEdycji;
                break;
            case 4:
                cout << "Wpisz Email: " << endl;
                cin >> wpisanyTekstDoEdycji;
                osoby[i].email = wpisanyTekstDoEdycji;
                break;
            case 5:
                cout << "Wpisz Adres: " << endl;
                cin.sync();
                getline(cin, wpisanyTekstDoEdycji);
                osoby[i].adres = wpisanyTekstDoEdycji;
                break;
            }
            zapiszVectorDoPliku(osoby);
        }
    }
    if (statusPrawidlowegoID == 0)
        cout << "Wpisales ID, ktorego nie ma w bazie" << endl;

    system("pause");

    return osoby;
}

int konwersjaStringNaInt(string wyraz)
{
    int i = atoi(wyraz.c_str());
    return i;
}
