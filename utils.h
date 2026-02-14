#pragma once
#include <string>


// Achievement (statistiky cviku)

struct Achievement {
    std::string exerciseName; // jméno cviku
    float maxWeight = 0;      // největší váha, kterou někdo zvedl
    float maxVolume = 0;      // největší objem jedné série (vaha * opakování)
    float oneRM = 0;          // největší odhadnutý 1RM (metoda Epley)
};


// Přepočítá achievements z historie workoutů

void rebuildAchievementsFromHistory(
    const std::string& workoutsFile = "workouts.txt",      // vstupní soubor s historií workoutů
    const std::string& achievementsFile = "achievements.txt" // výstupní soubor pro achievements
);


// Vypíše všechny achievements z achievements.txt

void printAchievements(const std::string& filename = "achievements.txt");


// Načte achievement pro konkrétní cvik podle jména

Achievement getAchievementByName(
    const std::string& exerciseName,
    const std::string& achievementsFile = "achievements.txt"
);
