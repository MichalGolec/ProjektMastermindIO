#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<ctime>
#include<cmath>
#include"wisielecBiblioteka.h"
using namespace std;

int wisielec() {
	przywitanie();
	int numerSlowa = generowanieNumeruSlowaWisielec();
	char slowoDoOdgadniecia[30] = { 0 };
	generowanieSlowaDoOdgadniecia(numerSlowa, slowoDoOdgadniecia);
	rozgrywka(slowoDoOdgadniecia);
	return 0;
}

int generowanieNumeruSlowaWisielec() {
	srand(time(NULL));

	int numerSlowa = rand() * 1731 % 34868;
	return numerSlowa;
}

void generowanieSlowaDoOdgadniecia(int numerSlowa, char* slowoDoOdgadniecia) {
	char pusteWczytanie[30] = { 0 };
	fstream wczytanieSlowaZPliku;
	wczytanieSlowaZPliku.open("slownik.txt", ios::in);
	for (int j = 1; j < numerSlowa; j++) {
		wczytanieSlowaZPliku >> pusteWczytanie;
	}
	wczytanieSlowaZPliku >> slowoDoOdgadniecia;
}

int warunekSprawdzajacyWisielec(char podanyZnak, char* slowoDoOdgadniecia, char* wypisanieOdgadnietychLiter) {
	int iloscOdgadnietychLiter = 0;
	for (int i = 0; i < strlen(slowoDoOdgadniecia); i++) {
		if (podanyZnak == wypisanieOdgadnietychLiter[i]) {
			cout << "Ta litera juz byla\nza probe oszustwa tracisz jedna sznse\n";
			break;
		}
		else if (podanyZnak == slowoDoOdgadniecia[i]) {
			iloscOdgadnietychLiter++;
			wypisanieOdgadnietychLiter[i] = podanyZnak;
		}
	}
	return iloscOdgadnietychLiter;
}
void wysw(int i) {
	switch (i) {
	case 0:
		break;
	case 1:
		cout << "\n\n\n\n\n___\n";
		break;
	case 2:
		cout << "\n|\n|\n|\n|\n|___\n";
		break;
	case 3:
		cout << " ___\n|\n|\n|\n|\n|___\n";
		break;
	case 4:
		cout << " ___\n|   |\n|\n|\n|\n|___\n";
		break;
	case 5:
		cout << " ___\n|   |\n|   o\n|\n|\n|___\n";
		break;
	case 6:
		cout << " ___\n|   |\n|   o__\n|\n|\n|___\n";
		break;
	case 7:
		cout << " ___\n|   |\n|   o__\n|   |\n|\n|___\n";
		break;
	case 8:
		cout << " ___\n|   |\n|   o__\n|  /|\n|\n|___\n";
		break;
	case 9:
		cout << " ___\n|   |\n|   o__\n|  /|\n|   /\n|___\n";
		break;
	case 10:
		cout << " ___\n|   |\n|   o__\n|  /|\n|  //\n|___\n";
		break;

	}
}
int rozgrywka(char* slowoDoOdgadniecia) {
	
	int iloscZyc = 10, iloscProbZRzedu = 0, iloscOdgadnietychLiter = 0; int bledy = 0;
	bool wygrana = 0, odgadniecieLitery = 0;
	char wypisanieOdgadnietychLiter[30] = { 0 }, probaOdgadnieciaPrzezGracza[30] = { 0 };
	for (int i = 0; i < strlen(slowoDoOdgadniecia); i++) { wypisanieOdgadnietychLiter[i] = { '*' }; }
	do {
		system("cls");
		cout << endl << "W przypadku checi odgadniecia calego slowa prosze wpisac 1, a nastepnie wcisnac enter" << endl;
		char podanyZnak;
		cout << "podaj litere do sprawdzenia(lub wpisz 1):\tTwoja liczba zyc to:" << iloscZyc << "\tPozostale proby:" << 3 - iloscProbZRzedu << endl; 
		wysw(bledy);
		cout<<wypisanieOdgadnietychLiter << endl;

		cin >> podanyZnak;
		if (podanyZnak >= 'a' && podanyZnak <= 'z') { podanyZnak = podanyZnak - 32; }//zamiana malych na duze
		if (podanyZnak >= 'A' && podanyZnak <= 'Z') {
			int iloscLiterOdgadnietychPrzedPodaniemZnaku = iloscOdgadnietychLiter;
			iloscOdgadnietychLiter = iloscOdgadnietychLiter + warunekSprawdzajacyWisielec(podanyZnak, slowoDoOdgadniecia, wypisanieOdgadnietychLiter);
			if (iloscLiterOdgadnietychPrzedPodaniemZnaku == iloscOdgadnietychLiter) {
				iloscProbZRzedu++;
				iloscZyc--;
				bledy++;
			}
			else {
				iloscProbZRzedu = 0;
			}
		}
		else if (podanyZnak == '1') {
			char probaOdgadnieciaCalegoHasla[30] = { 0 };
			int iloscOdgadnietychLiterWCalymHasle = 0;
			cout << "Podaj cale haslo: " << endl;
			while (getchar() != '\n');
			cin >> probaOdgadnieciaCalegoHasla;
			for (int i = 0; i < strlen(slowoDoOdgadniecia); i++) {
				if (probaOdgadnieciaCalegoHasla[i] == slowoDoOdgadniecia[i] || probaOdgadnieciaCalegoHasla[i] == slowoDoOdgadniecia[i] + 32) {
					iloscOdgadnietychLiterWCalymHasle++;
				}
			}
			if (iloscOdgadnietychLiterWCalymHasle == strlen(slowoDoOdgadniecia)) {
				iloscOdgadnietychLiter = iloscOdgadnietychLiterWCalymHasle;
			}
			else {
				iloscProbZRzedu++;
				iloscZyc--;
				bledy++;
			}
		}
		else { cout << "Prosimy o ponowne wpisanie znaku" << endl; }
		if (iloscOdgadnietychLiter == strlen(slowoDoOdgadniecia)) {
			wygrana = 1;
		}
	} while (iloscZyc != 0 && iloscProbZRzedu != 3 && wygrana == 0);
	system("CLS");
	if (wygrana == 1) {
		cout << "Gratulacje!\nUdalo Ci sie odgadnac haslo!" << endl;
	}
	else {
		wysw(10);
		cout << "Niestety tym razem Ci sie nie udalo" << endl;
		
	}
	cout << "Twoje haslo brzmialo: " << slowoDoOdgadniecia << endl;
	system("PAUSE");
	while (getchar() != '\n');
	return 0;
}

void przywitanie() {
	cout << "\n\n\t\t\tWitamy w WISIELCU\n\tZyczymy Ci powodzenia ;)\n\t";
	system("PAUSE");
	system("CLS");
}

