#include "exercise.h"
#include "workout.h"
#include "utils.h"
#include "exercise_database.h"
#include "measurements.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <map>
#include <sstream>
using namespace std;

// ===== Spočítá počet workoutů v souboru =====
int countWorkoutsInFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return 0; // pokud se soubor nepodaří otevřít, vrátí 0

    string line;
    int count = 0;

    // Procházení souboru a hledání řádků obsahujících "=== WORKOUT"
    while (getline(file, line)) {
        if (line.find("=== WORKOUT") != string::npos)
            count++;
    }

    file.close();
    return count; // vrátí celkový počet workoutů
}

// ===== Uloží tělesné údaje do souboru =====
void saveMeasurements(const Measurements& m) {
    ofstream file("measurements.txt");
    if (!file.is_open()) {
        cout << "Nelze otevrit measurements.txt\n";
        return;
    }

    // Uloží jednotlivé hodnoty do souboru
    file << "weight=" << m.weight << "\n";
    file << "height=" << m.height << "\n";
    file << "age=" << m.age << "\n";
    file << "chest=" << m.chest << "\n";
    file << "waist=" << m.waist << "\n";
    file << "arms=" << m.arms << "\n";
    file << "thighs=" << m.thighs << "\n";

    file.close();
}

// ===== Načte tělesné údaje ze souboru =====
void loadMeasurements(Measurements& m) {
    ifstream file("measurements.txt");
    if (!file.is_open()) {
        // Pokud soubor neexistuje, nastavíme všechny hodnoty na nulu
        m = {0,0,0,0,0,0,0};
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t pos = line.find('=');
        if (pos == string::npos) continue; // ignorujeme špatně formátované řádky

        string key = line.substr(0,pos);     // klíč (např. weight)
        string value = line.substr(pos+1);   // hodnota

        // Podle klíče nastavíme odpovídající pole v Measurements
        if(key=="weight") m.weight=stof(value);
        else if(key=="height") m.height=stoi(value);
        else if(key=="age") m.age=stoi(value);
        else if(key=="chest") m.chest=stof(value);
        else if(key=="waist") m.waist=stof(value);
        else if(key=="arms") m.arms=stof(value);
        else if(key=="thighs") m.thighs=stof(value);
    }

    file.close();
}

// ===== Interaktivní správa tělesných údajů =====
void manageMeasurements(Measurements& m) {
    loadMeasurements(m); // načteme aktuální hodnoty

    int volba=-1;
    cout << "\nAktualni telesne udaje:\n";
    cout << "Vaha (kg): " << m.weight << "\n";
    cout << "Vyska (cm): " << m.height << "\n";
    cout << "Vek: " << m.age << "\n";
    cout << "Hrudnik (cm): " << m.chest << "\n";
    cout << "Pas (cm): " << m.waist << "\n";
    cout << "Ruce (cm): " << m.arms << "\n";
    cout << "Stehna (cm): " << m.thighs << "\n\n";

    cout << "Zadej nove hodnoty (0 pro ponechani aktualni hodnoty):\n";
    cin >> volba;

    if(volba==0) {
        cout << "Zadane hodnoty ponechany.\n\n";
        return;
    }

    float inputFloat; 
    int inputInt;

    // Interaktivní zadání nových hodnot, pokud uživatel zadá 0, hodnota zůstane
    cout << "Vaha (kg): "; cin >> inputFloat; if(inputFloat!=0)m.weight=inputFloat;
    cout << "Vyska (cm): "; cin >> inputInt; if(inputInt!=0)m.height=inputInt;
    cout << "Vek: "; cin >> inputInt; if(inputInt!=0)m.age=inputInt;
    cout << "Hrudnik (cm): "; cin >> inputFloat; if(inputFloat!=0)m.chest=inputFloat;
    cout << "Pas (cm): "; cin >> inputFloat; if(inputFloat!=0)m.waist=inputFloat;
    cout << "Ruce (cm): "; cin >> inputFloat; if(inputFloat!=0)m.arms=inputFloat;
    cout << "Stehna (cm): "; cin >> inputFloat; if(inputFloat!=0)m.thighs=inputFloat;

    saveMeasurements(m); // uložíme nové hodnoty
    cout << "Telesne udaje ulozeny.\n\n";
}
