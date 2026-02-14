#pragma once
#include "exercise_database.h"
#include "measurements.h"


// Reprezentuje jednu položku ve workoutu – jeden cvik se všemi sériemi
struct ExerciseEntry {
    Exercise exercise;       // cvik
    float weight[20];        // váhy pro jednotlivé série (max 20 sérií)
    int reps[20];            // počet opakování pro každou sérii
    int sets;                // počet sérií pro tento cvik
};



// Reprezentuje celý trénink (workout), který může obsahovat až 20 cviků
class Workout {
private:
    ExerciseEntry entries[20];  // pole cviků v workoutu
    int count = 0;              // aktuální počet cviků v workoutu

public:
    // Přidá cvik do workoutu
    void addExercise(const ExerciseEntry& entry);

    // Vypíše celý workout (včetně sérií, vah a opakování)
    void print() const;

    // Interaktivní tvorba workoutu – vybírá cviky z databáze a zadává váhy/opakování
    void createInteractive(ExerciseDatabase& db, const Measurements& user);

    // Vypíše statistiky workoutu (celková váha zvednutá, počet sérií, rozdělení podle svalů)
    void printStats() const;

    // Odstraní workout podle čísla z uloženého souboru (např. "workouts.txt")
    void deleteWorkoutByNumber(int number, const std::string& filename = "workouts.txt");

    // Vymaže všechny cviky v aktuálním objektu workoutu
    void clear();

    // Getter – počet cviků v workoutu
    int getCount() const { return count; }

    // Getter – přístup k jednotlivé položce workoutu
    const ExerciseEntry& getEntry(int i) const { return entries[i]; }

    // Výpis celé historie workoutů ze souboru
    void printHistory(const std::string& filename = "workouts.txt");

    // Uloží aktuální workout do souboru
    void saveWorkoutToFile(const Workout& workout, const std::string& filename = "workouts.txt");
};
