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


// Přepočítá achievements z workouts.txt

void rebuildAchievementsFromHistory(
    const string& workoutsFile,      // soubor s historií workoutů
    const string& achievementsFile   // soubor, kam se uloží přepočítané achievements
) {
    ifstream file(workoutsFile);
    if (!file.is_open()) {            // kontrola, zda soubor existuje
        cout << "Nelze otevrit workouts.txt\n";
        return;
    }

    // Používáme mapu pro uložení statistik pro každý cvik
    map<string, Achievement> stats;

    string line;               // aktuální řádek souboru
    string currentExercise;    // jméno cviku, který momentálně zpracováváme

    // ===== Čtení souboru a výpočet statistik =====
    while (getline(file, line)) {

        // Radek s nazvem cviku, končí ':'
        // Např.: "Bench Press:"
        if (!line.empty() && line.back() == ':') {
            currentExercise = line.substr(0, line.size() - 1);
            continue;
        }

        // Radek se serii
        if (line.find("serie:") != string::npos) {
            float weight = 0.0f;  // váha série
            int reps = 0;          // počet opakování

            size_t kgPos = line.find("kg");
            size_t commaPos = line.find(",");

            if (kgPos == string::npos || commaPos == string::npos)
                continue;  // špatně formátovaný řádek

            try {
                // Extrahujeme váhu a počet opakování
                weight = stof(line.substr(commaPos - 6, 6));
                reps = stoi(line.substr(kgPos + 4));
            }
            catch (...) { 
                continue;  // pokud se nepodaří převést číslo, přeskočíme
            }

            Achievement& a = stats[currentExercise]; // reference na statistiky pro daný cvik

            // ===== Aktualizace statistik =====
            if (weight > a.maxWeight)           // max váha
                a.maxWeight = weight;

            float volume = weight * reps;       // objem série
            if (volume > a.maxVolume)           // max objem
                a.maxVolume = volume;

            float oneRM = weight * (1.0f + reps / 30.0f); // výpočet 1RM metodou Epley
            if (oneRM > a.oneRM)                // max 1RM
                a.oneRM = oneRM;
        }
    }

    file.close(); // zavřeme vstupní soubor

    // ===== Zápis přepočítaných statistik do souboru achievements.txt =====
    ofstream out(achievementsFile);
    if (!out.is_open()) {
        cout << "Nelze otevrit achievements.txt\n";
        return;
    }

    // Pro každý cvik uložíme blok s max hodnotami
    for (const auto& pair : stats) {
        out << "=== " << pair.first << " ===\n";            // jméno cviku
        out << "Maximalni vaha=" << pair.second.maxWeight << "\n";
        out << "Maximalni volume=" << pair.second.maxVolume << "\n";
        out << "1RM=" << pair.second.oneRM << "\n\n";
    }

    out.close();
    cout << "Achievements byly prepocitany.\n";
}


// Vypis achievements.txt

void printAchievements(const string& filename) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Zadne achievements zatim nejsou.\n";
        return;
    }

    string line;
    cout << "\n=== NEJLEPSI VYKONY ===\n\n";
    while (getline(file, line)) {   // vypsání každého řádku
        cout << line << "\n";
    }
    cout << "\n======================\n";

    file.close();
}


// Získání konkrétního achievement pro daný cvik

Achievement getAchievementByName(const string& exerciseName,
                                 const string& achievementsFile) {
    ifstream f(achievementsFile);
    Achievement a;
    if (!f.is_open()) return a;

    a.exerciseName = exerciseName;  // uložíme jméno cviku do struktury
    string line;
    bool found = false;

    // Procházíme soubor a hledáme blok pro daný cvik
    while (getline(f, line)) {
        if (line.find(exerciseName) != string::npos) {
            found = true;    // našli jsme blok cviku
        } else if (found) {
            if (line.find("MaxWeight=") != string::npos)
                a.maxWeight = stof(line.substr(10));
            else if (line.find("MaxVolume=") != string::npos)
                a.maxVolume = stof(line.substr(10));
            else if (line.find("1RM=") != string::npos)
                a.oneRM = stof(line.substr(4));
            else if (line.empty())
                break;          // konec bloku cviku
        }
    }

    return a;  // vrátíme naplněnou strukturu Achievement
}
