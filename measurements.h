#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

// =========================
// Measurements (tělesné údaje)
// =========================
struct Measurements {
    float weight;   // váha v kg
    int height;     // výška v cm
    int age;        // věk
    float chest;    // obvod hrudníku v cm
    float waist;    // obvod pasu v cm
    float arms;     // obvod paží v cm
    float thighs;   // obvod stehen v cm
};

// ===== Uloží měření do souboru =====
// Parametr m: struktura Measurements obsahující aktuální hodnoty
void saveMeasurements(const Measurements& m);

// ===== Načte měření ze souboru =====
// Parametr m: struktura Measurements, do které se načtou hodnoty
void loadMeasurements(Measurements& m);

// ===== Interaktivní nastavení měření =====
// Uživatel může zadat nové hodnoty, nebo ponechat aktuální
void manageMeasurements(Measurements& m);

// ===== Spočítá počet workoutů v souboru =====
// filename: název souboru, default "workouts.txt"
// Vrací počet workoutů (řádků obsahujících "=== WORKOUT")
int countWorkoutsInFile(const string& filename = "workouts.txt");
