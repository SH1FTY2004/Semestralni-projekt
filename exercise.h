#pragma once
#include <string>
using namespace std;

// =========================
// CVIKY
// =========================

// Svalová skupina
struct Muscle {
    string name;
};

// Jeden cvik
class Exercise {
private:
    string name;
    Muscle primary;
    Muscle secondary[5];
    int secondaryCount = 0;

public:
    Exercise() {}
    Exercise(string n, Muscle p) : name(n), primary(p) {}

    void setName(string n) { name = n; }
    void setPrimary(Muscle p) { primary = p; }
    void addSecondary(Muscle m);

    string getName() const { return name; }
    Muscle getPrimary() const { return primary; }
};

// Databáze cviků
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
