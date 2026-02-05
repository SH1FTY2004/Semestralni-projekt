#pragma once
#include <string>

struct Achievement {
    std::string exerciseName;
    float maxWeight = 0;
    float maxVolume = 0;
    float oneRM = 0;
};
void rebuildAchievementsFromHistory(
    const std::string& workoutsFile = "workouts.txt",
    const std::string& achievementsFile = "achievements.txt"
);

void printAchievements(const std::string& filename = "achievements.txt");

