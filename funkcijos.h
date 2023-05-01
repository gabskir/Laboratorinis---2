#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "mylib.h"

class studentas 
{
private:
    string vardas, pavarde;
    int egz;
    vector<int> paz;
    double galutinisVid, galutinisMed;

public:
    //konstruktorius
    studentas() {
        vardas = "";
        pavarde = "";
        egz = 0;
        galutinisVid = 0.0;
        galutinisMed = 0.0;
    }
    //destruktorius
    ~studentas() {
        paz.clear();
        //cout << "destruktorius suveike" << endl;
    }

    void clearMarks () {
        paz.clear();
    }

    void galutinis() {
        int s = paz.size();
        galutinisVid = 0.4 * std::accumulate(paz.begin(),paz.end(), 0.0) / s + 0.6 * egz;

        sort(paz.begin(), paz.end());
        galutinisMed = (s % 2 == 0) ? (double)(paz[s/2 - 1] + paz[s/2]) / 2 : (double)paz[s/2];
        galutinisMed = galutinisMed * 0.4  + 0.6 * egz;
        clearMarks();
    } 

    //setteriai
    void setName(string x)
    {
        vardas = x;
    }

    void setSurname(string x) 
    {
        pavarde = x;
    }

	void setEgz(int x) 
    {
        egz = x;
    }
	void setGalutinisVid(double x) 
    {
        galutinisVid = x;
    }
    void setGalutinisMed (double x) 
    {
        galutinisMed = x;
    }
    void setMark(int x) 
    {
        paz.push_back(x);
    }
    void setSize (int x) 
    {
        paz.resize(x);
    }


    //getteriai
    inline int getMarks(int i) const {
        return paz.at(i);
    }

	inline double getGalutinisVid() const{
        return galutinisVid;
    };
    inline double getGalutinisMed() const{
        return galutinisMed;
    }
    inline double getEgz() {
        return egz;
    }
	inline string getName() const
    {
        return vardas;
    }
	inline string getSurname() const {
        return pavarde;
    }

    inline vector<int> getMarks() const{
        return paz;
    }
};

bool lyginam_vardus(studentas& a, studentas& b);
bool lyginam_pavardes(studentas& a, studentas& b);
int randomPazymiai(int min, int max);
void atsitiktinisEgz (studentas& temp);
void atsitiktiniaiPazymiai (studentas& temp, int s);
void generavimas ();
bool taipArNe(char atsakymas);
char gautiAtsakyma(string klausimas);
bool arZodis (string tekstas);
//void galutinis(studentas& temp);
void lentele(std::ostream& output);
void skaitymas(vector<studentas>& grupe, studentas& temp);
void rasytiIFaila(vector<studentas>& grupe, string pavadinimas);
void duomenys (studentas& temp, int s);
//void galutinis(studentas& temp);
void budas2 (vector<studentas>& grupe, vector<studentas>& pasidaveliai);
void userioIvedimas (vector<studentas>& grupe, studentas& T);

#endif