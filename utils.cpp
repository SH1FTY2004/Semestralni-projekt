#include "utils.h"
#include <fstream>
#include <iostream>
using namespace std;

void saveWorkoutToFile(const Workout& workout, const string& filename) {
    ofstream out(filename, ios::app);
    if (!out.is_open()) { cout << "Nelze otevrit " << filename << "\n"; return; }

    int totalSets = 0, totalReps = 0;
    float totalVolume = 0.0f, maxSingleSet = 0.0f;
    static int workoutCounter = 1;

    out << "Workout " << workoutCounter++ << "\n";

    for (int i = 0; i < workout.getCount(); i++) {
        const ExerciseEntry& e = workout.getEntry(i);
        out << e.exercise.getName() << ":\n";
        for (int s = 0; s < e.sets; s++) {
            out << "  " << (s+1) << ". serie: " << e.weight[s] << " kg, " << e.reps[s] << " reps\n";

            totalSets++;
            totalReps += e.reps[s];
            float volume = e.weight[s] * e.reps[s];
            totalVolume += volume;
            if (volume > maxSingleSet) maxSingleSet = volume;
        }
    }

    out << "--- STATS ---\n";
    out << "TotalSets=" << totalSets << "\n";
    out << "TotalReps=" << totalReps << "\n";
    out << "TotalVolume=" << totalVolume << "\n";
    out << "MaxSingleSet=" << maxSingleSet << "\n";
    out << "--------------\n\n";
    out.close();
}
