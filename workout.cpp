#include "workout.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void Workout::addExercise(const ExerciseEntry& entry) {
    if (count < 20) entries[count++] = entry;
    else cout << "Workout je plny.\n";
}

void Workout::print() const {
    if (count == 0) { cout << "Workout je prazdny.\n"; return; }

    cout << "\n=== WORKOUT ===\n";
    for (int i = 0; i < count; i++) {
        cout << "- " << entries[i].exercise.getName() << " (" << entries[i].exercise.getPrimary().name << ")\n";
        for (int s = 0; s < entries[i].sets; s++)
            cout << "  " << (s+1) << ". serie: " << entries[i].weight[s] << " kg, " << entries[i].reps[s] << " opakovani\n";
    }
}

void Workout::printStats() const {
    if (count == 0) { cout << "Workout je prazdny.\n"; return; }

    string muscles[50];
    float totalWeight[50] = {0};
    int totalSets[50] = {0};
    int muscleCount = 0;

    float workoutTotalWeight = 0;
    int workoutTotalSets = 0;

    for (int i = 0; i < count; i++) {
        const ExerciseEntry& e = entries[i];
        string muscleName = e.exercise.getPrimary().name;

        int index = -1;
        for (int j = 0; j < muscleCount; j++) if (muscles[j] == muscleName) { index = j; break; }
        if (index == -1) { index = muscleCount; muscles[muscleCount++] = muscleName; }

        totalSets[index] += e.sets;
        workoutTotalSets += e.sets;

        float lifted = 0;
        for (int s = 0; s < e.sets; s++) lifted += e.weight[s] * e.reps[s];
        totalWeight[index] += lifted;
        workoutTotalWeight += lifted;
    }

    cout << "\n=== STATISTIKY WORKOUTU ===\n";
    for (int i = 0; i < muscleCount; i++) {
        cout << muscles[i] << ":\n";
        cout << "  Serie: " << totalSets[i] << "\n";
        cout << "  Zvednuto: " << totalWeight[i] << " kg\n\n";
    }

    cout << "=== CELKEM ===\n";
    cout << "Serie celkem: " << workoutTotalSets << "\n";
    cout << "Zvednuto celkem: " << workoutTotalWeight << " kg\n\n";
}

void Workout::saveToFile() const {
    saveWorkoutToFile(*this, "workouts.txt");
}

void Workout::clear() { count = 0; }

void Workout::printHistory(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) { cout << "Historie treninku neexistuje.\n"; return; }

    string line;
    cout << "\n=== HISTORIE TRENINKU ===\n\n";
    bool empty = true;
    while (getline(file, line)) { cout << line << "\n"; empty = false; }
    if (empty) cout << "Zadne treninky zatim nejsou ulozeny.\n";
    cout << "\n========================\n";
    file.close();
}

void Workout::deleteWorkoutByNumber(int number, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) { cout << "Soubor s treninky neexistuje.\n"; return; }

    vector<string> lines;
    string line;
    while (getline(file, line)) lines.push_back(line);
    file.close();

    vector<int> workoutStartIndices;
    for (size_t i = 0; i < lines.size(); i++)
        if (lines[i].find("Workout ") != string::npos)
            workoutStartIndices.push_back(i);

    if (number < 1 || number > workoutStartIndices.size()) { cout << "Workout s timto cislem neexistuje.\n"; return; }

    int start = workoutStartIndices[number - 1];
    int end = (number < workoutStartIndices.size()) ? workoutStartIndices[number] : lines.size();
    lines.erase(lines.begin() + start, lines.begin() + end);

    int workoutCounter = 1;
    for (size_t i = 0; i < lines.size(); i++)
        if (lines[i].find("Workout ") != string::npos)
            lines[i] = "Workout " + to_string(workoutCounter++) + "\n";

    ofstream out(filename);
    for (const string& l : lines) out << l << "\n";
    out.close();

    cout << "Workout #" << number << " byl odstraněn.\n";
}
