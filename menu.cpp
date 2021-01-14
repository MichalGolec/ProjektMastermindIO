#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<ctime>
#include<cmath>
#include"mastermindBiblioteka.h"
#include"wisielecBiblioteka.h"
#include"menuBiblioteka.h"
#include"kolko i krzyzyk.h"
using namespace std;

void menu() {
	char w = 0;//zmienna przechowywuj¹ca wybór u¿ytkownika w menu
	do {
		w = -1;
		system("CLS");
		cout << "\n\n\t\t\tWITAJ W GRZE!\n\tMENU\n\t1 - Wybierz gre\n\t2 - Przeczytaj instrukcje\n\t0 - Wyjscie z gry..." << endl;
		cin >> w;
		system("CLS");
		while (getchar() != '\n');//czyszczenie bufora klawiatury

		switch (w) {
		case '0':
			cout << "\n\n\n\n\t\t\t\tDziekujemy za skorzystanie z naszej gry";
			break;
		case '1':
			wyborGry();
			break;
		case '2':
			instrukcje();
			break;
		default:
			cout << "\n\n\n\tCos poszlo nie tak!\n\tUpewnij sie ze wpisales poprawny numer";
			system("PAUSE");
			break;
		}
	} while (w != '0');
	while (getchar() != '\n');
	system("CLS");
	return;
}

void wyborGry()
{
	int w = -1;//zmienna przechowywuj¹ca wybór u¿ytkownika w menu
	do {
		cout << "\n\n\t\t\tWYBOR GRY\n\t1 - Wisielec\n\t2 - Kolko i krzyzyk\n\t3 - Mastermind\n\t0 - powrot" << endl;
		cin >> w;
		while (getchar() != '\n');
		system("CLS");
		switch (w) {
		case 0:
			break;
		case 1:
			wisielec();
			w = 0;
			break;
		case 2:
			kolko_i_krzyzyk();
			w = 0;
			break;
		case 3:
			mastermind();
			w = 0;
			break;
		default:
			cout << "Cos poszlo nie tak!\nUpewnij sie ze wpisales poprawny numer\n";
		}
	} while (w != 0);
}

void instrukcje()
{
	int w = -1;
	do {
		system("CLS");
		cout << "\n\n\t\t\tINSTRUKCJE\n\t1 - Wisielec\n\t2 - Kolko i krzyzyk\n\t3 - Mastermind\n\t0 - Powrot do menu glownego\n";
		cin >> w;
		system("CLS");
		switch (w) {
		case 0:
			w = 0;
			break;
		case 1:
			cout << "\n\t\t\tWISIELEC\n\t\tNa odgadniecie hasla masz 10 zyc, ale jezeli Twoje 3 proby z rzedu beda bledne rowniez przegrasz!\n\t\tWielkosc wpisywanej litery nie ma znaczenia\n\n\t\t";
			break;
		case 2:
			cout << "\n\t\t\tKOLKO I KRZYZYK\n\t   Jest to zwyczajna gra w kolko i krzyzyk. Pierwszy gracz to kolko, drugi krzyzyk.\n\t"
				"   W wersji na dowolny wymiar nalezy zgromadzic pod rzad tyle swoich znakow, ile wynosi wymiar planszy.\n\t"
				"   Plansza moze miec wymiar od 3x3 do 10x10.\n\n";
			break;
		case 3:
			cout << "\n\t\t\t\tMASTERMIND\n\n\t   Zadaniem gracza jest odgadniecie ustawienia 4 kolorowych kul.\n\t"
				"   Gracz podaje 4 sposrod 8 roznych kolorow (kolory na poziomie latwym nie powtarzaja sie).\n\t"
				"   Jesli wybrany kolor znajduje sie na tym samym miejscu co w zgadywanej sekwencji,\n\t   gracz otrzymuje czarny klocek.\n\t"
				"   Jesli wybrany kolor znajduje sie w zgadywanej sekwencji w innym miejscu,\n\t   gracz otrzymuje bialy klocek.\n\t"
				"   Jesli wybrany kolor nie wystepuje w ustawieniu, gracz nie otrzymuje nic.\n\t"
				"   Gracz ma 10 prob na wpisywanie roznych kombinacji kolorow i odgadniecie ukrytej sekwencji.\n\n";
			break;
		default:
			cout << "\n\t\t\tBLAD\n\t\tProsze sprobowac jeszcze raz\n";
			break;
		}
		

		while (getchar() != '\n');
		if (w != 0) system("PAUSE");
	} while (w != 0);
}

