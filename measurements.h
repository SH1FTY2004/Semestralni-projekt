#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

// =========================
// Measurements (tělesné údaje)
// =========================
struct Measurements {
    float weight;
    int height;
    int age;
    float chest;
    float waist;
    float arms;
    float thighs;
};

// Uloží měření do souboru
void saveMeasurements(const Measurements& m);

// Načte měření ze souboru
void loadMeasurements(Measurements& m);

// Interaktivní nastavení měření
void manageMeasurements(Measurements& m);

// Spočítá počet workoutů v souboru
int countWorkoutsInFile(const string& filename = "workouts.txt");
