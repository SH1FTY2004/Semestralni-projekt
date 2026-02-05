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

// ================================
// Přepočítá achievements z workouts.txt
// ================================
void rebuildAchievementsFromHistory(
    const string& workoutsFile,
    const string& achievementsFile
) {
    ifstream file(workoutsFile);
    if (!file.is_open()) {
        cout << "Nelze otevrit workouts.txt\n";
        return;
    }

    /*struct Achievement {
        float maxWeight = 0.0f;
        float maxVolume = 0.0f;
        float oneRM = 0.0f;
    };*/

    map<string, Achievement> stats;

    string line;
    string currentExercise;

    while (getline(file, line)) {

        // Radek s nazvem cviku
        // Napr: Bench Press:
        if (!line.empty() && line.back() == ':') {
            currentExercise = line.substr(0, line.size() - 1);
            continue;
        }

        // Radek se serii
        // Napr: "  1. serie: 80 kg, 5 opakovani"
        if (line.find("serie:") != string::npos) {
            float weight = 0.0f;
            int reps = 0;

            size_t kgPos = line.find("kg");
            size_t commaPos = line.find(",");

            if (kgPos == string::npos || commaPos == string::npos)
                continue;

            try {
                weight = stof(line.substr(commaPos - 6, 6));
                reps = stoi(line.substr(kgPos + 4));
            }
            catch (...) {
                continue;
            }

            Achievement& a = stats[currentExercise];

            // Max vaha
            if (weight > a.maxWeight)
                a.maxWeight = weight;

            // Max volume jedne serie
            float volume = weight * reps;
            if (volume > a.maxVolume)
                a.maxVolume = volume;

            // 1RM (Epley)
            float oneRM = weight * (1.0f + reps / 30.0f);
            if (oneRM > a.oneRM)
                a.oneRM = oneRM;
        }
    }

    file.close();

    ofstream out(achievementsFile);
    if (!out.is_open()) {
        cout << "Nelze otevrit achievements.txt\n";
        return;
    }

    for (const auto& pair : stats) {
        out << "=== " << pair.first << " ===\n";
        out << "MaxWeight=" << pair.second.maxWeight << "\n";
        out << "MaxVolume=" << pair.second.maxVolume << "\n";
        out << "1RM=" << pair.second.oneRM << "\n\n";
    }

    out.close();
    cout << "Achievements byly prepocitany.\n";
}

// ================================
// Vypis achievements.txt
// ================================
void printAchievements(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Zadne achievements zatim nejsou.\n";
        return;
    }

    string line;
    cout << "\n=== NEJLEPSI VYKONY ===\n\n";
    while (getline(file, line)) {
        cout << line << "\n";
    }
    cout << "\n======================\n";

    file.close();
}
