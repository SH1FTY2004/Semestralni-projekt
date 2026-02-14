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

// ===== Přidání cviku do databáze =====
void ExerciseDatabase::addExercise(const Exercise& e) {
    // Pokud není databáze plná, uložíme nový cvik
    if (count < 200) exercises[count++] = e;
    else cout << "Databaze je plna!\n";
}

// ===== Hledání cviku podle jména =====
Exercise* ExerciseDatabase::findByName(const string& name) {
    // Prochází pole cviků a hledá podle přesného jména
    for (int i = 0; i < count; i++)
        if (exercises[i].getName() == name) return &exercises[i];
    return nullptr; // Pokud nenalezen, vrací nullptr
}

// ===== Výpis všech cviků podle primárního svalu =====
void ExerciseDatabase::printAllByMuscle() const {
    if (count == 0) { cout << "Zadne cviky nejsou ulozeny.\n"; return; }

    string muscles[100]; // Pole unikátních svalů
    int muscleCount = 0;

    // Procházení všech cviků a sběr unikátních svalů
    for (int i = 0; i < count; i++) {
        string m = exercises[i].getPrimary().name;
        bool exists = false;
        for (int j = 0; j < muscleCount; j++) 
            if (muscles[j] == m) { exists = true; break; }
        if (!exists) muscles[muscleCount++] = m;
    }

    // Vypíše cviky podle svalových partií
    for (int i = 0; i < muscleCount; i++) {
        cout << muscles[i] << ":\n";
        for (int j = 0; j < count; j++)
            if (exercises[j].getPrimary().name == muscles[i])
                cout << "  - " << exercises[j].getName() << "\n";
        cout << "\n";
    }
}

// ===== Interaktivní přidání cviku =====
void ExerciseDatabase::addExerciseInteractive() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // vyčistí buffer po předchozím cin
    string name, primaryName;

    cout << "Zadej nazev cviku: "; getline(cin, name);             // název cviku
    cout << "Zadej primarni sval: "; getline(cin, primaryName);   // primární sval

    Muscle p; p.name = primaryName;
    Exercise e(name, p);

    // Možnost přidat sekundární svaly
    int more = 1;
    while (more) {
        cout << "Chces pridat sekundarni sval? (1=ano,0=ne): "; cin >> more;
        if (more) {
            Muscle m; cout << "Nazev svalu: "; cin >> m.name;
            e.addSecondary(m); // Přidání sekundárního svalu do cviku
        }
    }

    addExercise(e); // Přidání cviku do databáze

    // Zápis cviku do souboru
    ofstream file("exercise.txt", ios::app);
    if (file.is_open()) {
        file << "\n" << name << ";" << p.name << ";";
        file.close();
    } else cout << "Nepodarilo se otevrit soubor pro zapis.\n";

    cout << "Cvik ulozen do programu!\n";
}

// ===== Načtení cviků ze souboru =====
void ExerciseDatabase::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) { cout << "Nepodarilo se otevrit soubor " << filename << "\n"; return; }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        size_t pos1 = line.find(';'); if (pos1 == string::npos) continue;
        string name = line.substr(0, pos1);

        size_t pos2 = line.find(';', pos1 + 1); if (pos2 == string::npos) continue;
        string primaryMuscle = line.substr(pos1 + 1, pos2 - pos1 - 1);

        Muscle m; m.name = primaryMuscle;
        Exercise e(name, m);
        addExercise(e); // Přidání cviku načteného ze souboru
    }
    file.close();
}

// ===== Odstranění cviku =====
void ExerciseDatabase::removeExercise(const string& filename) {
    bool found = false;
    string nameToRemove;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cout << "Zadej nazev cviku, ktery chces odstranit: "; getline(cin, nameToRemove);

    // Najde cvik a posune všechny zbylé cviky v poli
    for (int i = 0; i < count; i++) {
        if (exercises[i].getName() == nameToRemove) {
            found = true;
            for (int j = i; j < count - 1; j++) exercises[j] = exercises[j + 1];
            count--; break;
        }
    }

    if (!found) { cout << "Cvik nenalezen.\n"; return; }

    // Přepíšeme soubor
    ofstream file(filename);
    if (!file.is_open()) { cout << "Nepodarilo se otevrit soubor.\n"; return; }
    for (int i = 0; i < count; i++) {
        file << exercises[i].getName() << ";" << exercises[i].getPrimary().name << ";";
        if (i != count - 1) file << "\n";
    }
    file.close();
    cout << "Cvik odstraněn.\n";
}

// ===== Pomocná funkce pro převod na malé písmo a odstranění mezer =====
string toLowerTrim(const string& s) {
    string res;
    for (char c : s)
        if (!isspace(c)) res += tolower(c);
    return res;
}

// ===== Vyhledávání cviku v historii tréninků =====
void ExerciseDatabase::searchExerciseHistory() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // vyčistí buffer po předchozím cin

    string exerciseName;
    cout << "Zadej nazev cviku, ktery chce vyhledat: ";
    getline(cin, exerciseName);

    ifstream file("workouts.txt");
    if (!file.is_open()) {
        cout << "Soubor workouts.txt se nepodarilo otevrit.\n";
        return;
    }

    float maxWeight = 0;
    float maxVolume = 0;
    float oneRM = 0;

    string line;
    string currentExercise;
    bool foundExercise = false;

    // ===== Nejprve spočítáme statistiky cviku =====
    while (getline(file, line)) {
        if (line.empty()) continue;

        // Přeskočíme header workoutu
        if (line.rfind("=== WORKOUT", 0) == 0) continue;

        // Získáme název cviku bez závorek
        if (line.back() == ':') {
            string rawName = line.substr(0, line.size() - 1);
            size_t parenPos = rawName.find('(');
            if (parenPos != string::npos) rawName = rawName.substr(0, parenPos);
            currentExercise = rawName;
            continue;
        }

        // Pokud je řádek série pro hledaný cvik, počítáme statistiky
        if (line.find("serie:") != string::npos && currentExercise == exerciseName) {
            foundExercise = true;

            size_t kgPos = line.find("kg");
            size_t commaPos = line.find(",");
            if (kgPos == string::npos || commaPos == string::npos) continue;

            float weight = 0;
            int reps = 0;

            try {
                weight = stof(line.substr(commaPos - 6, 6));
                reps = stoi(line.substr(kgPos + 4));
            } catch (...) { continue; }

            float volume = weight * reps;
            float oneRepMax = weight * (1.0f + reps / 30.0f);

            if (weight > maxWeight) maxWeight = weight;
            if (volume > maxVolume) maxVolume = volume;
            if (oneRepMax > oneRM) oneRM = oneRepMax;
        }
    }

    if (!foundExercise) {
        cout << "Cvik \"" << exerciseName << "\" nebyl nalezen.\n";
        file.close();
        return;
    }

    // ===== Vypíšeme statistiky =====
    cout << "\n=== STATISTIKY CVIKU: " << exerciseName << " ===\n";
    cout << "Max vaha: " << maxWeight << " kg\n";
    cout << "Max volume: " << maxVolume << " kg\n";
    cout << "1RM: " << oneRM << " kg\n";

    // ===== Vypíšeme jen workouty, kde cvik je zahrnut =====
    file.clear();
    file.seekg(0);
    string workoutHeader;
    string workoutContent;
    bool cvikVWorkoutu = false;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line.rfind("=== WORKOUT", 0) == 0) {
            // Pokud jsme předtím našli cvik, vypíšeme celý blok
            if (cvikVWorkoutu) cout << workoutHeader << "\n" << workoutContent;

            workoutHeader = line;
            workoutContent = "";
            cvikVWorkoutu = false;
            continue;
        }

        // Získání názvu cviku pro daný řádek
        if (line.back() == ':') {
            string rawName = line.substr(0, line.size() - 1);
            size_t parenPos = rawName.find('(');
            if (parenPos != string::npos) rawName = rawName.substr(0, parenPos);
            currentExercise = rawName;
            continue;
        }

        // Pokud řádek patří hledanému cviku, uložíme ho do bloku
        if (currentExercise == exerciseName && line.find("serie:") != string::npos) {
            workoutContent += "  " + line + "\n";
            cvikVWorkoutu = true;
        }
    }

    // Vypíšeme poslední workout pokud obsahuje cvik
    if (cvikVWorkoutu) cout << workoutHeader << "\n" << workoutContent;

    file.close();
}
