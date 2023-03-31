#include "funkcijos.h"

int main () {
    int s;
    studentas T;
    vector <studentas> grupe;

    char arGeneruoti = gautiAtsakyma("Ar norite generuoti studento duomenu faila (t/n): ");

    if (arGeneruoti == 'n') {
        char arFailas = gautiAtsakyma("Ar duomenis norite skaityti is failo (t/n): ");

        if (arFailas == 'n') {
            //duomenu ivedimas ranka
            userioIvedimas (grupe, T);
        } else {
            //nuskaitymas is failo   
            skaitymas(grupe, T);
        }
        grupe.clear();
    } else {
        //failo generavimas
        generavimas (T);

        while (true){
            int pasirinkimas;
            cout << "\nPasirinkite:\n1. Sukurti nauja faila\n2. Sustabdyti programos veikima\n3. Skaityti duomenis is failo\n4. Ivesti duomenis ranka" << endl;
            cin >> pasirinkimas;
            if (pasirinkimas == 1) {
                //generuojamas dar vienas failas
                generavimas (T);
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
}