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
    //default konstruktorius
    studentas() {
        vardas = "";
        pavarde = "";
        egz = 0;
        galutinisVid = 0.0;
        galutinisMed = 0.0;
    }

    // studentas(string name, string surname, int exam, vector<int> marks)
    //     : vardas(name), pavarde(surname), egz(exam), paz(marks) {
    //     galutinisVid = 0.0;
    //     galutinisMed = 0.0;
    // }
    //copy constructor
    studentas(const studentas& x) {
        this->vardas = x.vardas;
        this->pavarde = x.pavarde;
        this->egz = x.egz;
        this->galutinisVid = x.galutinisVid;
        this->galutinisMed = x.galutinisMed;
        this->paz.reserve(x.paz.size());
        this->paz.resize(x.paz.size());
        for (int i = 0; i < x.paz.size(); i++)
	    {
		    paz[i] = x.paz[i];
	    }
    }
    //move constructor
    studentas(studentas&& x) {
        this->vardas = move(x.vardas);
        this->pavarde = move(x.pavarde);
        this->egz = move(x.egz);
        this->galutinisVid = move(x.galutinisVid);
        this->galutinisMed = move(x.galutinisMed);
        this->paz = std::move(x.paz);
    }
    //copy assignment operator
    studentas& operator = (const studentas& x) {
        if (&x == this)
            return*this;
        vardas = x.vardas;
        pavarde = x.pavarde;
        paz = x.paz;
	    egz = x.egz;
	    galutinisVid = x.galutinisVid;
        galutinisMed = x.galutinisMed;

	    return *this;
    }
    //move assignment operator
    studentas& operator=(studentas&& x){
        if (this != &x) {
            vardas = move(x.vardas);
            pavarde = move(x.pavarde);
            egz = move(x.egz);
            galutinisVid = move(x.galutinisVid);
            galutinisMed = move(x.galutinisMed);
            paz = move(x.paz);
        }
        return *this;
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

    friend std::ostream& operator<<(std::ostream& out, const studentas& s) {
        out << left << setw(15) << s.getName() << left << setw(15) << s.getSurname();
        out << std::fixed << std::setprecision(2) << left << setw(20) << s.getGalutinisVid() << left << setw(20) << s.getGalutinisMed();
        return out;
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