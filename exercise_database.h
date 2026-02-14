#pragma once
#include "exercise.h"
#include <string>
using namespace std;

class ExerciseDatabase {
private:
    Exercise exercises[200];  // Pole pro uložení cviků (max 200)
    int count = 0;            // Počet aktuálně uložených cviků

public:
    // ===== Přidání cviku do databáze =====
    void addExercise(const Exercise& e);  

    // ===== Hledání cviku podle jména =====
    Exercise* findByName(const string& name);  

    // ===== Výpis všech cviků podle primárního svalu =====
    void printAllByMuscle() const;  

    // ===== Interaktivní přidání cviku =====
    void addExerciseInteractive();  

    // ===== Načtení cviků ze souboru =====
    void loadFromFile(const string& filename = "exercise.txt");  

    // ===== Odstranění cviku ze souboru a z databáze =====
    void removeExercise(const string& filename = "exercise.txt");  

    // ===== Vyhledávání cviku v historii tréninků a výpis statistik =====
    void searchExerciseHistory();  
};
