#pragma once
#include "exercise_database.h"
#include "measurements.h"

struct ExerciseEntry {
    Exercise exercise;
    float weight[20];
    int reps[20];
    int sets;
};

class Workout {
private:
    ExerciseEntry entries[20];
    int count = 0;

public:
    void addExercise(const ExerciseEntry& entry);
    void print() const;
    void createInteractive(ExerciseDatabase& db, const Measurements& user);
    void printStats() const;
    void deleteWorkoutByNumber(int number, const std::string& filename = "workouts.txt");
    void clear();
    int getCount() const { return count; }
    const ExerciseEntry& getEntry(int i) const { return entries[i]; }
    void printHistory(const std::string& filename = "workouts.txt");
    void saveWorkoutToFile(const Workout& workout, const std::string& filename = "workouts.txt");
};

