#pragma once
#include <string>
#include "workout.h"

// Přepočet a ukládání statistiky workoutu do souboru
void saveWorkoutToFile(const Workout& workout, const std::string& filename = "workouts.txt");
