#pragma once


#define MAKSYMALNA_DLUGOSC_HASLA 16
#define MAKSYMALNA_ILOSC_ZYC 100


void generowanieKolorowMastermind(int, int, bool, int*);
void mastermind();
void przywitanie(int*, int*, int*, bool*, int*, bool*, int*);
bool rozgrywka(int*, int, int, int, int);
void wypis(int, int[MAKSYMALNA_DLUGOSC_HASLA][MAKSYMALNA_ILOSC_ZYC], int[2][MAKSYMALNA_ILOSC_ZYC], int, int, int*);
void PvPC(int, int, int, int, bool);//PvP z generowanym haslem
void PvP(int);
