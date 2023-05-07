#include "funkcijos.h"

int main () {

    int s;
    studentas T;
    vector <studentas> grupe;

    char arGeneruoti = gautiAtsakyma("\nAr norite generuoti studento duomenu faila (t/n): ");

    if (arGeneruoti == 'n') {
        char arFailas = gautiAtsakyma("\nAr duomenis norite skaityti is failo (t/n): ");

        if (arFailas == 'n') {
            //duomenu ivedimas ranka
            userioIvedimas (grupe, T);
        } else {
            //nuskaitymas is failo   
            skaitymas(grupe, T);
        }
    } else {
        //failo generavimas
        generavimas ();

        while (true){
            int pasirinkimas;
            cout << "\nPasirinkite:\n1. Sukurti nauja faila\n2. Sustabdyti programos veikima\n3. Skaityti duomenis is failo\n4. Ivesti duomenis ranka" << endl;
            cin >> pasirinkimas;
            if (pasirinkimas == 1) {
                //generuojamas dar vienas failas
                generavimas ();
            }
            else if (pasirinkimas == 2) {
                //programa baigia darba po generavimo - testavimui
                exit (0);
            }
            else if (pasirinkimas == 3){
                //nuskaito duomenis is pasirinkto failo
                skaitymas(grupe, T);
                break;
            }
            else if (pasirinkimas == 4) {
                //vedimas ranka
                userioIvedimas (grupe, T);
                break;
            }
            else {
                cout << "Netinkama ivestis. Bandykite dar karta." << endl;
            }
        }
    }
    grupe.clear();
}