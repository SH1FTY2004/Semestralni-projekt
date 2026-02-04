#pragma once
#include <string>
using namespace std;

// =========================
// MĚŘENÍ UŽIVATELE
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

// Funkce pro načtení a uložení měření
void saveMeasurements(const Measurements& m);
void loadMeasurements(Measurements& m);

// Interaktivní změna měření
void manageMeasurements(Measurements& m);
