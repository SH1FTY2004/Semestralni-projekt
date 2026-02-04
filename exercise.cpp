#include "exercise.h"
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

// ===== IMPLEMENTACE CVIKU =====
void Exercise::addSecondary(Muscle m) {
    if (secondaryCount < 5)
        secondary[secondaryCount++] = m;
    else
        cout << "Maximalni pocet sekundarnich svalu dosazen.\n";
}

// ===== IMPLEMENTACE DATABÁZE CVIKŮ =====
void ExerciseDatabase::addExercise(const Exercise& e) {
    if (count < 200)
        exercises[count++] = e;
    else
        cout << "Databaze je plna!\n";
}

Exercise* ExerciseDatabase::findByName(const string& name) {
    for (int i = 0; i < count; i++)
        if (exercises[i].getName() == name)
            return &exercises[i];
    return nullptr;
}

void ExerciseDatabase::printAllByMuscle() const {
    if (count == 0) { cout << "Zadne cviky nejsou ulozeny.\n"; return; }

    string muscles[100];
    int muscleCount = 0;

    for (int i = 0; i < count; i++) {
        string m = exercises[i].getPrimary().name;
        bool exists = false;
        for (int j = 0; j < muscleCount; j++)
            if (muscles[j] == m) { exists = true; break; }
        if (!exists) muscles[muscleCount++] = m;
    }

    for (int i = 0; i < muscleCount; i++) {
        cout << muscles[i] << ":\n";
        for (int j = 0; j < count; j++)
            if (exercises[j].getPrimary().name == muscles[i])
                cout << "  - " << exercises[j].getName() << "\n";
        cout << "\n";
    }
}

void ExerciseDatabase::addExerciseInteractive() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string name, primaryName;
    cout << "Zadej nazev cviku: ";
    getline(cin, name);
    cout << "Zadej primarni sval: ";
    getline(cin, primaryName);

    Muscle p; p.name = primaryName;
    Exercise e(name, p);

    int more = 1;
    while (more) {
        cout << "Chces pridat sekundarni sval? (1 = ano, 0 = ne): ";
        cin >> more;
        if (more) { Muscle m; cout << "Nazev svalu: "; cin >> m.name; e.addSecondary(m); }
    }

    addExercise(e);

    ofstream file("exercise.txt", ios::app);
    if (file.is_open()) file << name << ";" << p.name << ";\n";
    else cout << "Nepodarilo se otevrit soubor pro zapis.\n";

    cout << "Cvik ulozen do programu!\n";
}

void ExerciseDatabase::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) { cout << "Nepodarilo se otevrit soubor " << filename << "\n"; return; }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t pos1 = line.find(';');
        if (pos1 == string::npos) continue;
        string name = line.substr(0, pos1);
        size_t pos2 = line.find(';', pos1 + 1);
        if (pos2 == string::npos) continue;
        string primaryMuscle = line.substr(pos1 + 1, pos2 - pos1 - 1);

        Muscle m; m.name = primaryMuscle;
        Exercise e(name, m);
        addExercise(e);
    }
    file.close();
}

void ExerciseDatabase::removeExercise(const string& filename) {
    string nameToRemove;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Zadej nazev cviku k odstraneni: ";
    getline(cin, nameToRemove);

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (exercises[i].getName() == nameToRemove) {
            found = true;
            for (int j = i; j < count - 1; j++) exercises[j] = exercises[j + 1];
            count--;
            break;
        }
    }

    if (!found) { cout << "Cvik nenalezen.\n"; return; }

    ofstream file(filename);
    for (int i = 0; i < count; i++)
        file << exercises[i].getName() << ";" << exercises[i].getPrimary().name << ";\n";
    file.close();

    cout << "Cvik odstraněn.\n";
}
