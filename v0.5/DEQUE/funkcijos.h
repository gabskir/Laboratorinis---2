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
void skaitymas(deque<studentas>& grupe, studentas& temp);
void rasytiIFaila(deque<studentas>& grupe, string pavadinimas);
void duomenys (studentas& temp, int s);
void galutinis(studentas& temp);
void dalinimas (deque<studentas>& grupe, deque<studentas>& broliaiSaunuoliai, deque<studentas>& pasidaveliai);
void userioIvedimas (deque<studentas>& grupe, studentas& T);

#endif