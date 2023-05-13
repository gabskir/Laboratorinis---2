#include "funkcijos.h"

//patikrinimai-------------------------------------------------------------
bool taipArNe(char atsakymas) {
    return atsakymas == 't' || atsakymas == 'n';
}

char gautiAtsakyma(string klausimas) {
    char atsakymas;
    cout << klausimas;
    cin >> atsakymas;
    while (!taipArNe(atsakymas)) {
        cout << "Iveskite tik t arba n priklausomai nuo jusu pasirinkimo. " << klausimas;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> atsakymas;
    }
    return atsakymas;
}

bool arZodis (string tekstas) {
    for (char i : tekstas)
        {
        if (!isalpha(i))
        {
            cout << "Teksto ivedimui naudokite tik raides. Iveskite is naujo: " << endl;
            return false;
        }
    }
    return true;
}  

//atsitiktiniu skaiciu generavimas------------------------------------------
int randomPazymiai(int min, int max) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

void atsitiktinisEgz (studentas& temp){
    int random_num = randomPazymiai(0, 10);
    cout << "Atsitiktinai sugeneruotas egzamino pazymys: " << random_num << endl;
    temp.setEgz(random_num);
}

void atsitiktiniaiPazymiai (studentas& temp, int s) {
    for (int i = 0; i < s; ++i) {
        int x = randomPazymiai(0, 10);
        temp.setMark(x);
    }

    cout << "Atsitiktinai sugeneruoti studento namu darbu ivertinimai: ";
    for (int i = 0; i < temp.getMarks().size(); i++) {
        cout << temp.getMarks(i) << " ";
    }
    cout << endl;
}


void lentele(std::ostream& output) {
    output << left << setw(15) << "Vardas" << left << setw(15) << "Pavarde" << left << setw (20) << "Galutinis (Vid.)" << left << setw (20) << "Galutinis (Med.)" << endl;
    output << "--------------------------------------------------------------------------------" << endl;
}

bool lyginam_vardus(studentas& a, studentas& b) {
    return a.getName()< b.getName();
}

bool lyginam_pavardes(studentas& a, studentas& b) {
    return a.getSurname() < b.getSurname();
}


//darbas su failais-------------------------------------
void generavimas () {

    string failoPavadinimas;
    cout << "Iveskite generuojamo failo pavadinima: ";
	cin >> failoPavadinimas;
	failoPavadinimas = failoPavadinimas += ".txt";

    int kiekis;
    while (true) {
        cout << "Iveskite norima studentu kieki faile: ";
        if (cin >> kiekis && kiekis > 0) { 
            break;
        } else { 
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Iveskite tik sveikaji skaiciu." <<endl;
        }
    }

    int pazKiekis;
    while (true) {
        cout << "Iveskite norima namu darbu ivertinimu kieki faile: ";
        if (cin >> pazKiekis && pazKiekis > 0) { 
            break;
        } else { 
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Iveskite tik sveikaji skaiciu." <<endl;
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::stringstream failas;

//sugeneruojamas header
    failas << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde";
    for (int i = 1; i <= pazKiekis; ++i) {
        failas << "ND" << setw(5) << i;
    }
    failas << left << setw(5) << "Egz" << endl;

//sugeneruojami duomenys pavidalu Vardas1 Pavarde1...
    for (int i = 0; i < kiekis; i++) {
        failas << setw(20) << left << "Vardas" + std::to_string(i+1) << setw (20) << left << "Pavarde" + std::to_string(i+1);
        for (int j = 0; j < pazKiekis; j++) {
            failas << setw(7) << left << randomPazymiai(0,10);
        }
        failas << setw(7) << left << randomPazymiai(0,10) << endl;
    }
    std::ofstream out(failoPavadinimas);
    out << failas.str();
	out.close();
    std::chrono::duration<double> generavimas = std::chrono::high_resolution_clock::now() - start;

    cout << "\nFAILO GENERAVIMAS: " << generavimas.count() << " s" << endl;
}

void skaitymas(vector<studentas>& grupe, studentas& temp){
    char arVardas = gautiAtsakyma("\nAr norite nuskaicius faila studentus rusiuoti pagal pavardes? (t/n): ");
    
    string dirPath = "./";
    vector<string> failai;
    for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            failai.push_back(entry.path().filename().string());
        }
    }

    cout << "\nGalimi failai:" << std::endl;
    for (int i = 0; i < failai.size(); ++i) {
        cout << i + 1 << ". " << failai[i] << endl;
    }

    int failoPasirinkimas;
    while (true) {
        try {
            cout << "\nNurodykite failo, is kurio norite nuskaityti duomenis, numeri: ";
            if (!(cin >> failoPasirinkimas) || failoPasirinkimas < 1 || failoPasirinkimas > failai.size()) {
                throw "Bloga ivestis.";
            }
            break;
        }
        catch (const char* erroras) {
            cout << erroras << std::endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    //duomenu is failo nuskaitymas ir apdorojimas (t.y. - vidurkiu skaiciavimas)
    string pavadinimas = failai[failoPasirinkimas-1];
    auto laikas = std::chrono::high_resolution_clock::now();
    auto baigiam = std::chrono::high_resolution_clock::now();
    std::ifstream in(pavadinimas);
    while (true) {
    try{
        if (!in.is_open()) {
            throw "Failo nepavyko atidaryti.";
        } else{
            cout << "\nFAILAS NUSKAITOMAS..." << endl;
            int kiekis = -3;
            string eil;
            getline(in, eil);
            std::istringstream ss(eil);
            while (ss >> eil) {kiekis++;}
            while (std::getline(in, eil)) {
                std::istringstream ss(eil);
                string name, surname;
                ss >> name >> surname;
                vector<int> marks(kiekis);
                for (int i = 0; i < kiekis; i++) {
                    ss >> marks[i];
                }
                int exam;
                ss >> exam;
                studentas temp(name, surname, exam, marks);
                grupe.push_back(temp);
                marks.clear();
            }
            in.close();
            std::chrono::duration<double> skaitymas = std::chrono::high_resolution_clock::now() - baigiam;
            cout << "\nDUOMENU NUSKAITYMAS IR APDOROJIMAS: " << skaitymas.count() << " s" << endl;
            break;
        }
    }catch (const char* zinute) {
        cout << zinute << " Pabandykite atidaryti kita faila: " << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        while (true) {
            try {
                if (!(cin >> failoPasirinkimas) || failoPasirinkimas < 1 || failoPasirinkimas > failai.size())
                throw "Bloga ivestis.";
                in.open(failai[failoPasirinkimas-1]);
                break;
            }
            catch (const char* erroras) {
                cout << erroras << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    }
    
    failai.clear();

    if (arVardas == 't') {
        auto start = std::chrono::high_resolution_clock::now();
        sort(grupe.begin(), grupe.end(), lyginam_pavardes);
        std::chrono::duration<double> ruspav = std::chrono::high_resolution_clock::now() - start;
        cout << "RUSIAVIMAS PAGAL PAVARDES: " << std::fixed << ruspav.count() << " s" << endl;
    } else {
        auto start = std::chrono::high_resolution_clock::now();
        sort(grupe.begin(), grupe.end(), lyginam_vardus);
        std::chrono::duration<double> rusvar = std::chrono::high_resolution_clock::now() - start;
        cout << "RUSIAVIMAS PAGAL VARDUS: " << std::fixed << rusvar.count() << " s" << endl;
    }

        vector<studentas> pasidaveliai;
        rusiavimasIGrupes(grupe, pasidaveliai);

        auto irasome1 = std::chrono::high_resolution_clock::now();
        rasytiIFaila(grupe, "broliaiSaunuoliai.txt");
        std::chrono::duration<double> bendras = std::chrono::high_resolution_clock::now() - irasome1;
        cout << "SPAUSDINIMAS I FAILA BROLIAI SAUNUOLIAI: " << std::fixed << bendras.count() << " s" << endl;

        auto irasome = std::chrono::high_resolution_clock::now();
        rasytiIFaila(pasidaveliai, "pasidaveliai.txt");
        std::chrono::duration<double> pasid = std::chrono::high_resolution_clock::now() - irasome;
        cout << "SPAUSDINIMAS I FAILA PASIDAVELIAI: " << pasid.count() << " s" << endl;
        std::chrono::duration<double> kazk = std::chrono::high_resolution_clock::now() - laikas;
        cout << "VISOS PROGRAMOS VEIKIMO LAIKAS: " << kazk.count() << " s" << endl;

        pasidaveliai.clear();
    }


void rasytiIFaila(vector<studentas>& grupe, string pavadinimas) {
    std::ofstream out(pavadinimas);
    if (!out.is_open()) {
        cout << "Failo " << pavadinimas << " nepavyko sukurti." << endl;
    } else {
        lentele(out);
        for (auto& i : grupe) {
            out << i << endl;
        }
        out.close();
    }
}

void userioIvedimas (vector<studentas>& grupe, studentas& T) {
    int s;
    while (true) {
        cout << "Iveskite koks koks yra maksimalus namu darbu ivertinimu kiekis: ";
        if (cin >> s && s > 0) { 
            T.setSize(s);
            break;
        } else { 
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Iveskite tik sveikaji skaiciu." <<endl;
        }
    }

    while (true){
        char arStudentas = gautiAtsakyma("Ar norite ivesti papildomo studento duomenis(t/n): ");
        if (arStudentas == 'n'){
            break;
        }
        else{
            T.clearMarks();
            duomenys (T, s);
            grupe.push_back(T);
        }
    }

    if (grupe.empty())
        exit(0);

    char arVardas = gautiAtsakyma("Ar norite studentus rusiuoti pagal pavardes? (t/n): ");

    if (arVardas == 't') {
        sort(grupe.begin(), grupe.end(), lyginam_pavardes);
    }
    else {
        sort(grupe.begin(), grupe.end(), lyginam_vardus);
    }

    lentele(cout);
        for (auto &i:grupe){
            cout << i << endl;
        }   

        T.clearMarks();
        grupe.clear();
}


void duomenys (studentas& temp, int s){
    cout << "Iveskite studento varda: ";
    string vardas;
    do {
           cin >> vardas;
        }
        while(!arZodis(vardas));
    temp.setName(vardas);

    cout << "Iveskite studento pavarde: ";
    string pavarde;
    do {
           cin >> pavarde;
        }
        while(!arZodis(pavarde));
    temp.setSurname(pavarde);

    char arAtsitiktinai = gautiAtsakyma("Ar norite namu darbu ir egzamino ivertinimus generuoti atsitiktinai?(t/n): ");

    if (arAtsitiktinai == 't')
    {
        atsitiktiniaiPazymiai (temp, s);
        atsitiktinisEgz(temp);
       
    }
    else {
        bool stop = false;
        vector<int> pazymiai(s,0);
        cout << "Iveskite pazymi (ivede pazymi paspauskite enter, jei norite baigti vesti, spauskite n): " << endl;

        int i = 0;
        do{
            int pazymys;
            if (cin >> pazymys) {
                if (pazymys >= 0 && pazymys <= 10) {
                     temp.setMark(pazymys);
                     i++;
                } else {
                    cout << "Ivestas pazymys turi buti nuo 0 iki 10. Bandykite dar karta." << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } else {
                char c;
                cin.clear();
                cin >> c;
                if (c == 'n') {
                    stop = true;
                    break;
                } else {
                    cout << "Ivestis turi buti sveikasis skaicius. Bandykite pazymi ivesti dar karta." << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }  
            }
        } while (!stop && i < s);

        for (int j = i; j < s; j++) { 
            temp.setMark(0);
        }
        for (int j = 0; j < temp.getMarks().size(); j++) {
            cout << "Pazymys " << j+1 << ": " << temp.getMarks(j)<< endl;
        }

        while (true) {
        cout << "Iveskite egzamino ivertinima: ";
        int egz;
            if (cin >> egz) { 
                if (egz >= 1 && egz <= 10) {\
                    temp.setEgz(egz);
                    break;
                } else {
                    cin.clear(); 
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Ivertinimas turi buti tarp 1 ir 10. Bandykite dar karta." << endl;
                }    
            } else { 
                cin.clear(); 
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Iveskite tik sveikaji skaiciu." <<endl;
            }
        } 
    }
    temp.galutinis();
}

void rusiavimasIGrupes(vector<studentas>& grupe, vector<studentas>& pasidaveliai) {
    auto start = std::chrono::high_resolution_clock::now();
    grupe.erase(std::remove_if(grupe.begin(), grupe.end(), [&](studentas &j) {
        if (j.getGalutinisVid()< 5) {
            pasidaveliai.push_back(j);
            return true;
        }
        return false;
    }), grupe.end());
    
    grupe.shrink_to_fit();
    pasidaveliai.shrink_to_fit();

    std::chrono::duration<double> dalinimas = std::chrono::high_resolution_clock::now() - start;
    cout << "STUDENTU DALINIMAS I DVI GRUPES (VIENAS KONTEINERIS): " << dalinimas.count() << " s" << endl;
}
