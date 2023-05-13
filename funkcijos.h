#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "mylib.h"

class zmogus {
protected:
    string vardas, pavarde;
public:
    zmogus(string name = "", string surname = "") : vardas{name}, pavarde{surname} {}
	virtual string getName() const = 0;
	virtual string getSurname() const = 0;
    virtual void setName(string name) { vardas = name; }
    virtual void setSurname(string surname) { pavarde = surname; }
};

class studentas: public zmogus{
private:
    int egz;
    vector<int> paz;
    double galutinisVid, galutinisMed;

public:
    //default konstruktorius
    studentas() : egz{0}, galutinisVid {0.0}, galutinisMed{0.0} {}
    studentas(string name, string surname, int exam, vector<int> marks) : zmogus{name, surname}, egz{exam}, paz{marks} { galutinis(); }
    //copy constructor
    studentas(const studentas& x) : zmogus{x.vardas, x.pavarde}, galutinisVid{x.galutinisVid}, galutinisMed {x.galutinisMed} {}
    //move constructor
    studentas(studentas&& x) : zmogus{move(x.vardas), move(x.pavarde)}, galutinisVid{move(x.galutinisVid)}, galutinisMed{move(x.galutinisMed)} {
        x.galutinisVid = 0.0;
        x.galutinisMed = 0.0;
        x.paz.clear();
    }
    //copy assignment operator
    studentas& operator = (const studentas& x) {
        if (this!= &x) {
            vardas = x.vardas;
            pavarde = x.pavarde;
            galutinisVid = x.galutinisVid;
            galutinisMed = x.galutinisMed;
        }
        return *this;
    }
    //move assignment operator
    studentas& operator=(studentas&& x){
        if (this != &x) {
            vardas = move(x.vardas);
            pavarde = move(x.pavarde);
            egz = move(x.egz);
            paz = move(x.paz);
            galutinisVid = move(x.galutinisVid);
            galutinisMed = move(x.galutinisMed);
            x.galutinisMed = 0.0;
            x.galutinisVid = 0.0;
            x.paz.clear();

        }
        return *this;
    }

    //destruktorius
    ~studentas() { paz.clear(); }

    void clearMarks () { paz.clear(); }

    void galutinis() {
        int s = paz.size();
        galutinisVid = 0.4 * std::accumulate(paz.begin(),paz.end(), 0.0) / s + 0.6 * egz;

        sort(paz.begin(), paz.end());
        galutinisMed = (s % 2 == 0) ? (double)(paz[s/2 - 1] + paz[s/2]) / 2 : (double)paz[s/2];
        galutinisMed = galutinisMed * 0.4  + 0.6 * egz;
        clearMarks();
        setEgz(0);
    }

    friend std::ostream& operator<<(std::ostream& out, const studentas& s) {
        out << left << setw(15) << s.vardas << left << setw(15) << s.pavarde;
        out << std::fixed << std::setprecision(2) << left << setw(20) << s.galutinisVid << left << setw(20) << s.galutinisMed;
        return out;
    }

    //setteriai
	void setEgz(int x) { egz = x; }
    void setMark(int x) { paz.push_back(x); }
    void setSize (int x) { paz.resize(x); }

    //getteriai
    inline int getMarks(int i) const { return paz.at(i); }
	inline double getGalutinisVid() const { return galutinisVid; }
    inline double getGalutinisMed() const { return galutinisMed; }
    inline double getEgz() const { return egz; }
	inline string getName() const { return vardas; }
	inline string getSurname() const { return pavarde; }
    inline vector<int> getMarks() const{ return paz; }
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
void lentele(std::ostream& output);
void skaitymas(vector<studentas>& grupe, studentas& temp);
void rasytiIFaila(vector<studentas>& grupe, string pavadinimas);
void duomenys (studentas& temp, int s);
void rusiavimasIGrupes (vector<studentas>& grupe, vector<studentas>& pasidaveliai);
void userioIvedimas (vector<studentas>& grupe, studentas& T);

#endif