#include "funkcijos.h"

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

int randomPazymiai(int min, int max) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

void atsitiktinisEgz (int& egz){
    int random_num = randomPazymiai(0, 10);
    cout << "Atsitiktinai sugeneruotas egzamino pazymys: " << random_num << endl;
    egz = random_num;
}

void atsitiktiniaiPazymiai (studentas& temp, int s) {
    for (int i = 0; i < s; ++i) {
        int x = randomPazymiai(0, 10);
        temp.paz.push_back(x);
    }

    cout << "Atsitiktinai sugeneruoti studento namu darbu ivertinimai: ";
    for (int i = 0; i < temp.paz.size(); i++) {
        cout << temp.paz.at(i) << " ";
    }
    cout << endl;
}

void galutinis(studentas& temp) {
    int s = temp.paz.size();
    temp.galutinisVid = std::accumulate(&temp.paz[0], &temp.paz[s], 0.0);
    temp.galutinisVid = 0.4 * (temp.galutinisVid/(s)) + 0.6 * temp.egz;

    sort(temp.paz.begin(), temp.paz.end());
    temp.galutinisMed = (s % 2 == 0) ? (double)(temp.paz[s/2 - 1] + temp.paz[s/2]) / 2 : (double)temp.paz[s/2];
    temp.galutinisMed = 0.4 * temp.galutinisMed  + 0.6 * temp.egz;
    temp.paz.clear();
}

void lentele(std::ostream& output) {
    output << left << setw(15) << "Vardas" << left << setw(15) << "Pavarde" << left << setw (20) << "Galutinis (Vid.)" << left << setw (20) << "Galutinis (Med.)" << endl;
    output << "--------------------------------------------------------------------------------" << endl;
}

bool lyginam_vardus(studentas a, studentas b) {
    return a.vardas < b.vardas;
}

bool lyginam_pavardes(studentas a, studentas b) {
    return a.pavarde < b.pavarde;
}

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

    failas << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde";
    for (int i = 1; i <= pazKiekis; ++i) {
        failas << "ND" << setw(5) << i;
    }
    failas << left << setw(5) << "Egz" << endl;

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

void skaitymas(list<studentas>& grupe, studentas& temp){

    char arVardas = gautiAtsakyma("\nAr norite nuskaicius faila studentus rusiuoti pagal pavardes? (t/n): ");
    int strategija;
    cout << "\nPasirinkite strategija, kuria norite skaidyti i atskirtus konteinerius: " << endl << "0 - dvieju nauju konteineriu " << endl << "1 - vieno naujo konteinerio" << endl;

    while (true) {
    cout << "Pasirinkimas: ";
    if (cin >> strategija) {
        cout << endl;
        break;
    } else {
        cout << "Neteisingas pasirinkimas. Prašome įvesti teisingą pasirinkimą." << endl;
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    
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
            while (ss>>eil) {kiekis++;}

            int p;
            while (std::getline(in, eil)) {
                std::istringstream ss(eil);
                ss >> temp.vardas >> temp.pavarde;
                for (int i = 0; i < kiekis; i++) {
                    ss >> p;
                    temp.paz.push_back(p);
                }
                ss >> temp.egz;
                galutinis(temp);
                grupe.push_back(temp);
            }
            in.close();
            std::chrono::duration<double> skaitymas = std::chrono::high_resolution_clock::now() - baigiam;
            cout << "\nDUOMENU NUSKAITYMAS IR APDOROJIMAS: " << skaitymas.count() << " s" << endl;
            break;
        }
    }catch (const char* zinute) {
        cout << zinute << "Pabandykite atidaryti kita faila: " << endl;
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
    
    //rusiavimas pagal vardus ar pavardes
    if (arVardas == 't') {
        auto start = std::chrono::high_resolution_clock::now();
        grupe.sort(lyginam_pavardes);
        std::chrono::duration<double> ruspav = std::chrono::high_resolution_clock::now() - start;
        cout << "RUSIAVIMAS PAGAL PAVARDES: " << std::fixed << ruspav.count() << " s" << endl;
    }
    else {
        auto start = std::chrono::high_resolution_clock::now();
        grupe.sort(lyginam_vardus);
        std::chrono::duration<double> rusvar = std::chrono::high_resolution_clock::now() - start;
        cout << "RUSIAVIMAS PAGAL VARDUS: " << std::fixed << rusvar.count() << " s" << endl;
    }

    //padalinimas pagal pazymi (>5 ar <5)
    //pirma strategija kai naudojami du nauji list konteineriai
    if (strategija == 0){    
    list<studentas> broliaiSaunuoliai;
    list<studentas> pasidaveliai;
    budas1(grupe, broliaiSaunuoliai, pasidaveliai);

    //spausdinimas i du failus
    auto start = std::chrono::high_resolution_clock::now();

    auto rasome = std::chrono::high_resolution_clock::now();
    rasytiIFaila(broliaiSaunuoliai, "broliaiSaunuoliai.txt");
    std::chrono::duration<double> brol = std::chrono::high_resolution_clock::now() - rasome;
    cout << "SPAUSDINIMAS I FAILA BROLIAI SAUNUOLIAI: " << brol.count() << " s" << endl;

    auto irasome = std::chrono::high_resolution_clock::now();
    rasytiIFaila(pasidaveliai, "pasidaveliai.txt");
    std::chrono::duration<double> pasid = std::chrono::high_resolution_clock::now() - irasome;
    cout << "SPAUSDINIMAS I FAILA PASIDAVELIAI: " << pasid.count() << " s" << endl;

    std::chrono::duration<double> spausdinimas = std::chrono::high_resolution_clock::now() - start;
    cout << "SPAUSDINIMAS I DU FAILUS: " << spausdinimas.count() << " s" << endl;
    broliaiSaunuoliai.clear();
    pasidaveliai.clear();
    std::chrono::duration<double> kazkas = std::chrono::high_resolution_clock::now() - laikas;
    cout << "\nVISOS PROGRAMOS VEIKIMO LAIKAS: " << kazkas.count() << " s" << endl;
    } else {
        list <studentas> pasidaveliai;
        budas2 (grupe, pasidaveliai);
        
        auto irasome1 = std::chrono::high_resolution_clock::now();
        rasytiIFaila(grupe, "broliaiSaunuoliai.txt");
        std::chrono::duration<double> bendras = std::chrono::high_resolution_clock::now() - irasome1;
        cout << "SPAUSDINIMAS I FAILA BROLIAI SAUNUOLIAI: " << std::fixed << bendras.count() << " s" << endl;

        auto irasome = std::chrono::high_resolution_clock::now();
        rasytiIFaila(pasidaveliai, "pasidaveliai.txt");
        std::chrono::duration<double> pasid = std::chrono::high_resolution_clock::now() - irasome;
        cout << "SPAUSDINIMAS I FAILA PASIDAVELIAI: " << pasid.count() << " s" << endl;

        pasidaveliai.clear();
    }


}

void rasytiIFaila(list<studentas>& grupe, string pavadinimas) {
    std::ofstream out(pavadinimas);
    if (!out.is_open()) {
        cout << "Failo " << pavadinimas << " nepavyko sukurti." << endl;
    } else {
        lentele(out);
        for (auto& i : grupe) {
            out << left << setw(15) << i.vardas << left << setw(15) << i.pavarde;
            out << std::fixed << std::setprecision(2) << left << setw(20) << i.galutinisVid << left << setw(20) << i.galutinisMed << endl;
        }
        out.close();
    }
    
}

void userioIvedimas (list<studentas>& grupe, studentas& T) {
    int s;
    while (true) {
        cout << "Iveskite koks koks yra maksimalus namu darbu ivertinimu kiekis: ";
        if (cin >> s && s > 0) { 
            T.paz.reserve(s);
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
            T.paz.clear();
            duomenys (T, s);
            grupe.push_back(T);
        }
    }

    if (grupe.empty())
        exit(0);

    char arVardas = gautiAtsakyma("Ar norite studentus rusiuoti pagal pavardes? (t/n): ");

    if (arVardas == 't') {
        grupe.sort(lyginam_pavardes);
    }
    else {
        grupe.sort(lyginam_vardus);
    }

    lentele(cout);
        for (auto &i:grupe){    
            galutinis (i);
            cout << left << setw(15) << i.vardas <<
                left << setw(15) << i.pavarde <<
                left << setw(20) << std::fixed << std::setprecision(2) << i.galutinisVid << left << setw(20) << std::fixed << std::setprecision(2) << i.galutinisMed<< endl;
        }   

        T.paz.clear();
        grupe.clear();
}


void duomenys (studentas& temp, int s){
    cout << "Iveskite studento varda: ";
    string vardas;
    do {
           cin >> vardas;
        }
        while(!arZodis(vardas));
    temp.vardas = vardas;


    cout << "Iveskite studento pavarde: ";
    string pavarde;
    do {
           cin >> pavarde;
        }
        while(!arZodis(pavarde));
    temp.pavarde = pavarde;

    char arAtsitiktinai = gautiAtsakyma("Ar norite namu darbu ir egzamino ivertinimus generuoti atsitiktinai?(t/n): ");

    if (arAtsitiktinai == 't')
    {
        atsitiktiniaiPazymiai (temp, s);
        atsitiktinisEgz(temp.egz);
       
    }
    else {
        bool stop = false;
        cout << "Iveskite pazymi (ivede pazymi paspauskite enter, jei norite baigti vesti, spauskite n): " << endl;

        int i = 0;
        do{
            int pazymys;
            if (cin >> pazymys) {
                if (pazymys >= 0 && pazymys <= 10) {
                    temp.paz.push_back(pazymys);
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
            temp.paz.push_back(0);
        }
        for (int j = 0; j < s; j++) {
            cout << "Pazymys " << j+1 << ": " << temp.paz.at(j)<< endl;
        }

        while (true) {
        cout << "Iveskite egzamino ivertinima: ";
            if (cin >> temp.egz) { 
                if (temp.egz >= 1 && temp.egz <= 10) {
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
}

void budas1 (list<studentas>& grupe, list<studentas>& broliaiSaunuoliai, list<studentas>& pasidaveliai) {
    auto start = std::chrono::high_resolution_clock::now();

    for (auto& j : grupe) {
        if (j.galutinisVid < 5) {
            pasidaveliai.push_back(j);
        }
        else {
            broliaiSaunuoliai.push_back(j);
        }
    }
    std::chrono::duration<double> dalinimas = std::chrono::high_resolution_clock::now() - start;
    cout << "STUDENTU DALINIMAS I DVI GRUPES: " << dalinimas.count() << " s" << endl;
}

void budas2(list<studentas>& grupe, list<studentas>& pasidaveliai) {
    auto start = std::chrono::high_resolution_clock::now();
    grupe.remove_if([&](studentas &j) {
        if (j.galutinisVid < 5) {
            pasidaveliai.push_back(j);
            return true;
        }
        return false;
    });

    std::chrono::duration<double> dalinimas = std::chrono::high_resolution_clock::now() - start;
    cout << "STUDENTU DALINIMAS I DVI GRUPES (VIENAS KONTEINERIS): " << dalinimas.count() << " s" << endl;
}
