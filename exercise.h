#pragma once
#include <string>
#include "muscle.h"
using namespace std;

// =========================
// Třída Exercise
// Reprezentuje jeden cvik s primárním a až pěti sekundárními svaly
// =========================
class Exercise {
private:
    string name;            // Název cviku
    Muscle primary;         // Primární sval, na který cvik cílí
    Muscle secondary[5];    // Pole pro až 5 sekundárních svalů
    int secondaryCount = 0; // Počet aktuálně přidaných sekundárních svalů

public:
    // ===== Konstruktor =====
    Exercise() {}                      // Default konstruktor
    Exercise(string n, Muscle p) : name(n), primary(p) {} // Konstruktor s názvem a primárním svalem

    // ===== Settery =====
    void setName(string n) { name = n; }   // Nastavení názvu cviku
    void setPrimary(Muscle p) { primary = p; } // Nastavení primárního svalu

    // ===== Přidání sekundárního svalu =====
    void addSecondary(Muscle m); // Přidá sval do pole sekundárních svalů (max 5)

    // ===== Gettery =====
    string getName() const { return name; }  // Získání názvu cviku
    Muscle getPrimary() const { return primary; } // Získání primárního svalu
};
