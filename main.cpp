#include "funkcijos.h"

int main () {

    studentas s1("Algirdas", "Brazauskas", 10, {8, 9, 10});
    cout << "COPY CONSTRUCTOR TESTAS:" << endl;
    cout << "Studentas 1 pries: "<< s1 << endl;
    studentas s2(s1);
    cout << "Studentas 1 po: "<< s1 << endl;
    cout << "Studentas 2 po: "<< s2 << endl;

    studentas s3("Dalia", "Grybauskaite", 8, {4, 8, 3});
    cout << "MOVE CONSTRUCTOR TESTAS:" << endl;
    cout << "Studentas 3 pries: "<< s3 << endl;
    studentas s4 = move(s3);
    cout << "Studentas 3 po: "<< s3 << endl;
    cout << "Studentas 4 po: "<< s4 << endl;

    studentas s5;
    cout << "COPY ASSIGNMENT OPERATOR TEST:" << endl;
    cout << "Studentas 2 pries: "<< s2 << endl;
    cout << "Studentas 5 pries: "<< s5 << endl;
    s5 = s2;
    cout << "Studentas 2 po: "<< s2 << endl;
    cout << "Studentas 5 po: "<< s5 << endl;

    studentas s6;
    cout << "MOVE ASSIGNMENT OPERATOR TESTAS:" << endl;
    cout << "Studentas 4 pries: "<< s4 << endl;
    cout << "Studentas 6 pries: "<< s6 << endl;
    s6 = move(s4);
    cout << "Studentas 4 po: "<< s4 << endl;
    cout << "Studentas 6 po: "<< s6 << endl;

    // int s;
    // studentas T;
    // vector <studentas> grupe;

    // char arGeneruoti = gautiAtsakyma("\nAr norite generuoti studento duomenu faila (t/n): ");

    // if (arGeneruoti == 'n') {
    //     char arFailas = gautiAtsakyma("\nAr duomenis norite skaityti is failo (t/n): ");

    //     if (arFailas == 'n') {
    //         //duomenu ivedimas ranka
    //         userioIvedimas (grupe, T);
    //     } else {
    //         //nuskaitymas is failo   
    //         skaitymas(grupe, T);
    //     }
    // } else {
    //     //failo generavimas
    //     generavimas ();

    //     while (true){
    //         int pasirinkimas;
    //         cout << "\nPasirinkite:\n1. Sukurti nauja faila\n2. Sustabdyti programos veikima\n3. Skaityti duomenis is failo\n4. Ivesti duomenis ranka" << endl;
    //         cin >> pasirinkimas;
    //         if (pasirinkimas == 1) {
    //             //generuojamas dar vienas failas
    //             generavimas ();
    //         }
    //         else if (pasirinkimas == 2) {
    //             //programa baigia darba po generavimo - testavimui
    //             exit (0);
    //         }
    //         else if (pasirinkimas == 3){
    //             //nuskaito duomenis is pasirinkto failo
    //             skaitymas(grupe, T);
    //             break;
    //         }
    //         else if (pasirinkimas == 4) {
    //             //vedimas ranka
    //             userioIvedimas (grupe, T);
    //             break;
    //         }
    //         else {
    //             cout << "Netinkama ivestis. Bandykite dar karta." << endl;
    //         }
    //     }
    // }
    // grupe.clear();
}