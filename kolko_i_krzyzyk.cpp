#include<iostream>
#define MAX_ROZMIAR 10
using namespace std;

int check(int x, int y, char t[MAX_ROZMIAR][MAX_ROZMIAR]) {
	int w = 1, a = x, b = y;
	if (t[x][y] != 0) {
		//printf("\n %d %d %d \n", t[x][y],a,b);
		w = 0;
	}
	return w;
}

int wyg(char tab[MAX_ROZMIAR][MAX_ROZMIAR], int rozmiar) {

	int wygrana = 0;
	int kolkow = 0, krzyzykw = 0, kolkok = 0, krzyzykk = 0, kolkop = 0, krzyzykp = 0, kolkod = 0, krzyzykd = 0;

	//kolumny
	for (int i = 0; i < rozmiar && wygrana == 0; i++) {
		krzyzykk = 0;
		kolkok = 0;
		for (int j = 0; j < rozmiar; j++) {
			if (tab[i][j] == 'x') {
				krzyzykk++;
			}
			else if (tab[i][j] == 'o') {
				kolkok++;
			}
		}
		if (kolkok == rozmiar) {
			wygrana = 1;
		}

		if (krzyzykk == rozmiar) {
			wygrana = 2;
		}
	}

	//wiersze
	for (int j = 0; j < rozmiar && wygrana == 0; j++) {
		krzyzykw = 0;
		kolkow = 0;
		for (int i = 0; i < rozmiar; i++) {
			if (tab[i][j] == 'x') {
				krzyzykw++;
			}
			else if (tab[i][j] == 'o') {
				kolkow++;
			}
		}
		if (kolkow == rozmiar) {
			wygrana = 1;
		}

		if (krzyzykw == rozmiar) {
			wygrana = 2;
		}
	}

	//1 przekontna
	for (int i = 0, j = 0; i < rozmiar && wygrana == 0; i++, j++) {
		if (tab[i][j] == 'x') {
			krzyzykp++;
		}
		else if (tab[i][j] == 'o') {
			kolkop++;
		}

		if (kolkop == rozmiar) {
			wygrana = 1;
		}

		if (krzyzykp == rozmiar) {
			wygrana = 2;
		}

	}


	//druga przekatna

	for (int i = 0, j = 0; i < rozmiar && wygrana == 0; i++, j++) {
		if (tab[i][rozmiar - j - 1] == 'x') {
			krzyzykd++;
		}
		else if (tab[i][rozmiar - j - 1] == 'o') {
			kolkod++;
		}

		if (kolkod == rozmiar) {
			wygrana = 1;
		}

		if (krzyzykd == rozmiar) {
			wygrana = 2;
		}
	}
	return wygrana;
}

int wypis(char tab[MAX_ROZMIAR][MAX_ROZMIAR], int r) {

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < r; j++) {
			if (tab[i][j] == 0) {
				cout << "*\t";
			}
			else
				cout << tab[i][j] << "\t";

		}
		cout << endl;
	}
	return 0;
}


void graLatwa(int rozmiar) {
	char tab[MAX_ROZMIAR][MAX_ROZMIAR] = { 0 };
	system("cls");

	int a, b;
	int w = 0;
	for (int i = 0; i < rozmiar * rozmiar && w == 0; i++) {
	wpis:
		system("cls");
		wypis(tab, rozmiar);

		if (i % 2 == 1) {
			cout << "kolej gracza krzyzyk" << endl << "podaj najpierw numer wiersza potem kolumny" << endl;
			cin >> a;
			cin >> b;

			if (a > rozmiar || b > rozmiar) {
				cout << "Podales zla wspolzedna wiersza lub kolumny" << endl;
				system("PAUSE");
				goto wpis;
			}
			else if (check(a - 1, b - 1, tab) == 0) {
				cout << "oszukujesz, tam juz bylo cos wpisane" << endl;
				system("PAUSE");
				goto wpis;
			}
			else {

				tab[a - 1][b - 1] = 'x';
			}


		}
		else {
			cout << "kolej gracza kolko" << endl << "podaj najpierw numer wiersza potem kolumny" << endl;
			cin >> a;
			cin >> b;

			if (a > rozmiar || b > rozmiar) {
				cout << "Podales zla wspolzedna wiersza lub kolumny" << endl;
				system("PAUSE");
				goto wpis;
			}
			else if (check(a - 1, b - 1, tab) == 0) {

				cout << "oszukujesz, tam juz bylo cos wpisane" << endl;
				system("PAUSE");
				goto wpis;
			}
			else {

				tab[a - 1][b - 1] = 'o';
			}
		}
		system("cls");

		w = wyg(tab, rozmiar);

	
	
		//if (w == 0) {
			//wypis(tab, rozmiar);
			//cout << "nikt nie wygral" << endl;
			//i = 120;
		//}
		if (w == 1) {
			wypis(tab, rozmiar);
			cout << "wygralo o" << endl;
			i = 120;

		}
		if (w == 2) {
			wypis(tab, rozmiar);
			cout << "wygral x" << endl;
			i = 120;
		}
		
	}
	if (w == 0) {
		cout << "nikt nie wygral" << endl;
	}
	cout << endl << "koniec gry"<<endl;
	system("PAUSE");
	
}

void kolko_i_krzyzyk() {
menu:
	int wybor = 0;
	cout << "Witaj w grze kolko i krzyzyk, wybierz opcje:" << endl << "1. Kolko i krzyzyk 3x3" << endl << "2. Kolko i krzyzyk na dowolny wymiar" << endl;
	cin >> wybor;
	if (wybor == 1) {

		graLatwa(3);
	}
	else if (wybor == 2) {
		int r;
		cout << "podaj wymiar, nie mniejszy niz 3 a nie wiekszy niz 10: " << endl;
		cin >> r;
		while (r < 3 || r>10) {
			cout << "Nieopoprawny wymiar, podaj jescze raz: " << endl;
			cin >> r;
		}
		graLatwa(r);
	}

	else {
		system("cls");
		cout << "blad, nie ma takiej opcji w menu";
		goto menu;
	}

}
