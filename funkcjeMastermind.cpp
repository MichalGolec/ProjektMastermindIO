#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include "mastermindBiblioteka.h"

using namespace std;


void mastermind()
{
	srand(time(NULL));
	bool powrot = 0;
	do {
		int dlugoscHasla = 0, iloscKolorow = 0, trybGry = 0, iloscZyc = 0, iloscRund = 0;
		bool powtarzanieKolorow = 0;
		int haslo[MAKSYMALNA_DLUGOSC_HASLA] = { 0 };
		przywitanie(&dlugoscHasla, &iloscKolorow, &trybGry, &powtarzanieKolorow, &iloscZyc, &powrot, &iloscRund);
		if (trybGry > 0 && trybGry < 4) {
			generowanieKolorowMastermind(dlugoscHasla, iloscKolorow, powtarzanieKolorow, haslo);
			rozgrywka(haslo, trybGry, iloscZyc, dlugoscHasla, iloscKolorow);
		}
		else if (trybGry == 4) PvPC(iloscRund, iloscKolorow, dlugoscHasla, iloscZyc, powtarzanieKolorow);
		else if (trybGry == 5) PvP(iloscRund);
		else cout << "To nigdy nie powinno zostac wypisane" << endl;

	} while (powrot == 0);
}

void generowanieKolorowMastermind(int dlugoscHasla, int iloscKolorow, bool powtarzanieKolorow, int* haslo)
{
	if (powtarzanieKolorow == 1) {
		for (int i = 0; i < dlugoscHasla; i++) {
			haslo[i] = rand() % iloscKolorow + 1;//bo kolory zaczynamy od 1
		}
	}
	else {
		for (int i = 0; i < dlugoscHasla; i++) {
			haslo[i] = rand() % iloscKolorow + 1;
			for (int j = 0; j < i; j++) {
				if (haslo[i] == haslo[j])
					i--;
			}
		}
	}//wypisanie tablic w celu upewnienia sie
	/*
	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << haslo[i];
	}
	*/
	return;
}

void przywitanie(int* dlugoscHasla, int* iloscKolorow, int* trybGry, bool* powtarzanieKolorow, int* iloscZyc, bool* powrot, int* iloscRund)
{
	char w = 0;
	system("CLS");
	do {
		cout << "\n\n\t\t\tWitamy w grze MASTERMIND\n\tWybierz tryb gry:\n\t1 - Latwy (8 kolorow, 4 miejsca, bez powtarzania, 10 zyc)";
		cout << "\n\t2 - Trudny (8 kolorow, 4 miejsca, powtarzanie, 10 zyc)\n\t3 - \"Custom\" (wszystko podane)";
		cout << "\n\t4 - PvP (wszystko podane, haslo wygenerowane)\n\t5 - PvP (wszystko uzupelniane przez uzytkownikow)\n\t0 - Powrot" << endl;
		cin >> w;
		while (getchar() != '\n');
		switch (w) {
		case '0':
			*powrot = 1;
			w = 0;
			break;
		case '1':case '2':
			*dlugoscHasla = 4;
			*iloscKolorow = 8;
			*iloscZyc = 10;
			*trybGry = (w == '1') ? 1 : 2;
			*powtarzanieKolorow = (w == '1') ? 0 : 1;
			w = 0;
			break;
		case '3':case '4':
		wpis0:
			system("CLS");
			cout << "\tPodaj liczbe kolorow:\n";
			cin >> *iloscKolorow;
			while (getchar() != '\n');
		wpis1:
			cout << "\tPodaj liczbe miejsc do odgadniecia (nie wieksza niz niz " << MAKSYMALNA_DLUGOSC_HASLA << "):\n";
			cin >> *dlugoscHasla;
			if (*dlugoscHasla > MAKSYMALNA_DLUGOSC_HASLA) {
				cout << "Podano za duza liczbe\n";
				goto wpis1;
			}
			while (getchar() != '\n');

		wpis2:
			cout << "\tPodaj liczbe zyc (nie wieksza niz " << MAKSYMALNA_ILOSC_ZYC << "):\n";
			cin >> *iloscZyc;
			if (*dlugoscHasla > MAKSYMALNA_ILOSC_ZYC) {
				cout << "Podano za duza liczbe\n";
				goto wpis2;
			}
			while (getchar() != '\n');

			cout << "\tCzy kolory maja sie powtarzac?\n\t1 - TAK\n\t0 - NIE\n\tWpisz 1 lub 0\n";
			cin >> *powtarzanieKolorow;
			while (getchar() != '\n');

			*trybGry = ((w == '4') ? 4 : 3);
			if (w == '4') {
				cout << "\tPodaj ilosc rund\n";
				cin >> *iloscRund;
				while (getchar() != '\n');

			}
			if ((iloscKolorow < dlugoscHasla && powtarzanieKolorow == 0) || dlugoscHasla <= 0 || iloscKolorow <= 0 || iloscRund <= 0 || iloscZyc <= 0) {
				cout << "\n\n\tPodane dzialanie jest nie mozliwe do wykonania\n\tProsze Sprobowac ponownie\n\t";
				goto wpis0;
			}
			w = 0;
			break;

		case '5':
			system("CLS");
			cout << "\tPodaj ilosc rund\n";
			cin >> *iloscRund;
			while (getchar() != '\n');

			*trybGry = 5;
			w = 0;
			break;
		default:
			cout << "\n\n\n\tCos poszlo nie tak!\n\tUpewnij sie ze wpisales poprawny numer" << endl;
			system("PAUSE");
			break;
		}
		system("CLS");
	} while (w != 0);
	return;
}

bool rozgrywka(int* haslo, int tryb, int zycia, int dlugoscHasla, int kolory)
{

	int proba = 0;
	int wszystkieStrzaly[MAKSYMALNA_DLUGOSC_HASLA][MAKSYMALNA_ILOSC_ZYC] = { 0 };//tablica przecz=howywujaca wszystkie strzaly gracza
	int wszystkie_cz_b[2][MAKSYMALNA_ILOSC_ZYC] = { 0 };//[0] - czarne, tablica przechowujaca ile bialych i czarnych mial gracz w kazdej turze
	int gracz[MAKSYMALNA_DLUGOSC_HASLA] = { 0 };//tablica przechowywujaca aktualny strzal gracza
	int wygrana = -1;
	do {
	wpis:
		int czarne = 0, biale = 0;
		wypis(proba, wszystkieStrzaly, wszystkie_cz_b, dlugoscHasla, wygrana, haslo);
		cout << "Podaj " << dlugoscHasla << " kolorow:" << endl;

		//petla zbierajaca dane od uzytkownika dotyczace ustawienia
		for (int i = 0; i < dlugoscHasla; ++i) {
			if (scanf_s("%d", &gracz[i]) < 1 || ferror(stdin) || gracz[i] < 1 || gracz[i] > kolory) {//sprawdzenie czy wpisane dane sa poprawne
				cout << "\nNiepoprawne dane! Wpisz ponownie" << endl;
				system("PAUSE");
				system("CLS");
				while (getchar() != '\n');//czyszczenie bufora
				goto wpis;
			}
			else {
				wszystkieStrzaly[i][proba] = gracz[i];
			}
		}
		while (getchar() != '\n');//czyszczenie bufora (zabezpieczenie przed wczytaniem paru prob na raz)

		//warunek sprawdzajacy

		for (int i = 0; i < dlugoscHasla; i++) {
			for (int j = 0; j < dlugoscHasla; j++) {
				if (gracz[i] == haslo[j] && i == j) {
					czarne++;
				}
				else if (gracz[i] == haslo[j]) {
					biale++;
				}
			}
		}/* //sprawdzenie hasel
		for (int i = 0; i < MAKSYMALNA_DLUGOSC_HASLA; i++) {
			cout << haslo[i];
		}
		cout << endl;
		for (int i = 0; i < MAKSYMALNA_DLUGOSC_HASLA; i++) {
			cout << gracz[i];
		}
		cout << endl;//do tego moentu
		*/
		wszystkie_cz_b[0][proba] = czarne;
		//cout << czarne<<"\t"<<biale;//wypisanie bialych i czarnych
		wszystkie_cz_b[1][proba] = biale;
		if (czarne == dlugoscHasla) {
			wygrana = 1;
		}
		proba++;
		//system("PAUSE");potrzebne przy wypisywaniu
		system("CLS");

	} while (wygrana != 1 && proba < zycia);
	if (wygrana != 1)wygrana = 0;
	//system("PAUSE");
	if (tryb > 0 && tryb < 6) {
		wypis(proba, wszystkieStrzaly, wszystkie_cz_b, dlugoscHasla, wygrana, haslo);
		if (wygrana == 1) {
			cout << "\n\n\t\tGratulacje!\n\tUdalo Ci sie odgadnac haslo!\n\t";
		}
		else {
			cout << "\n\n\t\tSprobuj jeszcze raz!\n\tNastepnym razem na pewno sie uda!\n";
		}
		system("PAUSE");
	}
	return wygrana;
}

void wypis(int proba, int strzaly[MAKSYMALNA_DLUGOSC_HASLA][MAKSYMALNA_ILOSC_ZYC], int cz_b[2][MAKSYMALNA_ILOSC_ZYC], int dlugosc, int w, int* haslo)
{
	if (w == -1) {
		cout << "Numer Twojej proby to: " << proba + 1 << endl;
		cout << "|";
		for (int i = 0; i < dlugosc; i++) {
			cout << "# ";
		}
	}
	else {
		cout << "|";
		for (int i = 0; i < dlugosc; ++i) {
			cout << haslo[i] << " ";
		}
	}
	cout << "|" << endl << "|";
	for (int i = 0; i < dlugosc; i++) {
		cout << "==";
	}
	cout << "|" << endl;
	for (int i = 0; i < proba; ++i) {
		cout << "|";
		for (int j = 0; j < dlugosc; ++j) {
			cout << strzaly[j][i] << " ";
		}
		cout << "| biale: " << cz_b[1][i] << " czarne: " << cz_b[0][i] << endl;//cz_b[0] - czarne
	}
	return;
}

void PvPC(int iloscRund, int kolory, int dlugosc, int zycia, bool powtarzanie)
{
	int runda = 1, wynikGracz1 = 0, wynikGracz2 = 0;
wpis:
	do {
		system("CLS");
		int haslo[MAKSYMALNA_DLUGOSC_HASLA] = { 0 };
		int wynik = 0;
		cout << "\t\tRunda:" << runda / 2 + runda % 2 << "\n\t\tNastepuje kolej gracza " << (runda - 1) % 2 + 1 << "\n\tgracz 1: " << wynikGracz1 << "\tgracz 2: " << wynikGracz2 << endl << endl;
		generowanieKolorowMastermind(dlugosc, kolory, powtarzanie, haslo);
		wynik = rozgrywka(haslo, 4, zycia, dlugosc, kolory);
		if ((runda - 1) % 2 + 1 == 1)wynikGracz1 = wynikGracz1 + wynik;
		else wynikGracz2 = wynikGracz2 + wynik;
		system("CLS");
		runda++;
	} while (runda <= 2 * iloscRund || (abs(wynikGracz1 - wynikGracz2) <= (iloscRund - runda)));
	if (wynikGracz1 > wynikGracz2) {
		cout << "\n\t\tZWYCIESTWO!\n\n\tZwyciezyl gracz o numerze 1 wynikiem:" << "\n\tgracz 1: " << wynikGracz1 << "\tgracz 2: " << wynikGracz2 << endl << endl << "\t\tGRATULACJE!";
	}
	else if (wynikGracz1 < wynikGracz2) {
		cout << "\n\t\tZWYCIESTWO!\n\n\tZwyciezyl gracz o numerze 2 wynikiem:" << "\n\tgracz 2: " << wynikGracz2 << "\tgracz 1: " << wynikGracz1 << endl << endl << "\t\tGRATULACJE!";

	}
	else {
		cout << "\n\t\tREMIS\n\n\tJezeli chcecie rozegrac dogrywke prosze wpisac 1\n\t\t";
		if (getchar() == 1) {
			cout << "\n\tPodaj liczbe rund w dogrywce:" << endl;
			cin >> iloscRund;
			goto wpis;
		}
	}
	system("PAUSE");
}

void PvP(int iloscRund)
{
	system("CLS");
	int runda = 1, wynikGracz1 = 0, wynikGracz2 = 0, zycia = 0, kolory = 0;
	cout << "\tPodaj liczbe zyc: ";
	cin >> zycia;
	cout << "\tPodaj liczbe kolorow: ";
	cin >> kolory;
wpis:
	do {
	wpis1:
		system("CLS");
		int haslo[MAKSYMALNA_DLUGOSC_HASLA] = { 0 };
		int wynik = 0, dlugosc = 0, c = 1;
		cout << "\t\tRunda:" << runda / 2 + runda % 2 << "\n\t\tNastepuje kolej gracza " << (runda - 1) % 2 + 1 << "\n\tgracz 1: " << wynikGracz1 << "\tgracz 2: " << wynikGracz2 << endl << endl << "\tPodaj haslo do odgadniecia nie dluzsze niz " << MAKSYMALNA_DLUGOSC_HASLA << "\n\tdostepne kolory: 1 - " << kolory << endl << "\tAby zakonczyc wpisywanie wpisz 0 i nacisnij enter\n\n";
	
		for (int i = 0; i < MAKSYMALNA_DLUGOSC_HASLA && c != 0; i++) {
			cin >> c;
			if (c != 0) {
				haslo[i] = c;
				if (c > kolory) {
					cout << "\nNastapilo bledne wpisanie\n";
					system("PAUSE");
					system("CLS");
					goto wpis1;
				}
				dlugosc++;
			}
			
		}
		system("CLS");
		cout << "\t\tRunda:" << runda / 2 + runda % 2 << "\n\t\tNastepuje kolej gracza " << (runda - 1) % 2 + 1 << "\n\tgracz 1: " << wynikGracz1 << "\tgracz 2: " << wynikGracz2 << endl << endl;
		wynik = rozgrywka(haslo, 5, zycia, dlugosc, kolory);
		if ((runda - 1) % 2 + 1 == 1)wynikGracz1 = wynikGracz1 + wynik;
		else wynikGracz2 = wynikGracz2 + wynik;
		system("CLS");
		runda++;
	} while (runda <= 2 * iloscRund || (abs(wynikGracz1 - wynikGracz2) <= (iloscRund - runda)));
	if (wynikGracz1 > wynikGracz2) {
		cout << "\n\t\tZWYCIESTWO!\n\n\tZwyciezyl gracz o numerze 1 wynikiem:" << "\n\tgracz 1: " << wynikGracz1 << "\tgracz 2: " << wynikGracz2 << endl << endl << "\t\tGRATULACJE!";
	}
	else if (wynikGracz1 < wynikGracz2) {
		cout << "\n\t\tZWYCIESTWO!\n\n\tZwyciezyl gracz o numerze 2 wynikiem:" << "\n\tgracz 2: " << wynikGracz2 << "\tgracz 1: " << wynikGracz1 << endl << endl << "\t\tGRATULACJE!";

	}
	else {
		cout << "\n\t\tREMIS\n\n\tJezeli chcecie rozegrac dogrywke prosze wpisac 1\n\t\t";
		if (getchar() == 1) {
			cout << "\n\tPodaj liczbe rund w dogrywce:" << endl;
			cin >> iloscRund;
			goto wpis;
		}		
	}
	system("PAUSE");
}

