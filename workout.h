#pragma once
#include <string>
#include "exercise.h"
#include "measurements.h"
using namespace std;

// =========================
// WORKOUTS
// =========================

// Jeden cvik v workoutu
struct ExerciseEntry {
    Exercise exercise;
    float weight[20];
    int reps[20];
    int sets;
};

// Workout (sada cviku)
class Workout {
private:
    ExerciseEntry entries[20];
    int count = 0;

public:
    void addExercise(const ExerciseEntry& entry);
    void print() const;
    void printStats() const;
    void createInteractive(ExerciseDatabase& db, const Measurements& user);
    void saveToFile() const;
    void deleteWorkoutByNumber(int number, const string& filename = "workouts.txt");
    void clear();
    int getCount() const { return count; }
    const ExerciseEntry& getEntry(int i) const { return entries[i]; }
    static void printHistory(const string& filename = "workouts.txt");
};
