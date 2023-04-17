#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "mylib.h"


struct studentas {
    string vardas = "", pavarde = "";
    int egz = 0;
    vector<int> paz;
    double galutinisVid = 0;
    double galutinisMed = 0;
};

bool taipArNe(char atsakymas);
char gautiAtsakyma(string klausimas);
bool arZodis (string tekstas);
int randomPazymiai(int min, int max) ;
void atsitiktinisEgz (int& egz);
void atsitiktiniaiPazymiai (studentas& temp, int s);
void generavimas ();
void galutinis(studentas& temp);
void lentele(std::ostream& output);
bool lyginam_vardus(studentas a, studentas b);
bool lyginam_pavardes(studentas a, studentas b);
void skaitymas(vector<studentas>& grupe, studentas& temp);
void rasytiIFaila(vector<studentas>& grupe, string pavadinimas);
void duomenys (studentas& temp, int s);
void galutinis(studentas& temp);
void budas1 (vector<studentas>& grupe, vector<studentas>& broliaiSaunuoliai, vector<studentas>& pasidaveliai);
void budas2(vector<studentas>& grupe, vector<studentas>& pasidaveliai);
void optimizuotas (vector<studentas>& grupe, vector<studentas>& pasidaveliai);
void userioIvedimas (vector<studentas>& grupe, studentas& T);

#endif