#pragma once
#include "exercise.h"
#include <string>
using namespace std;

class ExerciseDatabase {
private:
    Exercise exercises[200];
    int count = 0;

public:
    void addExercise(const Exercise& e);
    Exercise* findByName(const string& name);
    void printAllByMuscle() const;
    void addExerciseInteractive();
    void loadFromFile(const string& filename = "exercise.txt");
    void removeExercise(const string& filename = "exercise.txt");
};
