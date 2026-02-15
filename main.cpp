#include "exercise.h"            // Deklarace třídy Exercise
#include "workout.h"             // Deklarace třídy Workout
#include "utils.h"               // Funkce pro achievements a measurements
#include "exercise_database.h"   // Třída pro správu databáze cviků
#include "measurements.h"        // Struktura a funkce pro uživatelovy údaje
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <map>
#include <sstream>
using namespace std;

int main() {
    Workout w;               // Objekt pro práci s jedním tréninkem / historií
    ExerciseDatabase db;     // Objekt pro správu databáze cviků
    db.loadFromFile("exercise.txt"); // Načtení cviků ze souboru
    int choice = -1;         // Proměnná pro volbu v menu
    
    // Hlavní smyčka programu, běží dokud uživatel nezvolí 0
    while (choice != 0) {
        cout << "\n=== HLAVNI MENU ===\n";
        cout << "[1] Cviky\n";
        cout << "[2] Treninky\n";
        cout << "[3] Nejlepsi vykony\n";
        cout << "[4] Nastaveni telesnych udaju\n";
        cout << "[0] Konec\n";
        cout << "Vyber: ";
        cin >> choice;

        switch (choice) {

        // ===== CVIKY =====
        case 1: {
            int sub = -1; // Proměnná pro volbu v podmenu cviků
            while (sub != 0) {
                cout << "\n=== CVIKY ===\n";
                cout << "[1] Vypsat vsechny cviky\n";
                cout << "[2] Pridat novy cvik\n";
                cout << "[3] Odstranit cvik\n";
                cout << "[4] Vyhledat cvik\n";
                cout << "[0] Zpet\n";
                cout << "Vyber: ";
                cin >> sub;

                switch (sub) {
                case 1:
                    db.printAllByMuscle();   // Vypíše všechny cviky podle svalových partií
                    break;
                case 2:
                    db.addExerciseInteractive(); // Přidání nového cviku uživatelem
                    break;
                case 3:
                    db.removeExercise();     // Odstranění cviku
                    break;
                case 4:
                    db.searchExerciseHistory(); // Vyhledání cviku v historii a zobrazení statistik
                    break;
                case 0:
                    break; // Návrat zpět do hlavního menu
                default:
                    cout << "Neplatna volba!\n"; // Chybné zadání
                }
            }
            break;
        }

        // ===== TRENINKY =====
        case 2: {
            int sub = -1; // Proměnná pro volbu v podmenu tréninků
            while (sub != 0) {
                cout << "\n=== TRENINKY ===\n";
                cout << "[1] Vytvorit trenink\n";
                cout << "[2] Historie treninku\n";
                cout << "[3] Odstranit trenink\n";
                cout << "[0] Zpet\n";
                cout << "Vyber: ";
                cin >> sub;

                switch (sub) {
                case 1: {
                    Measurements user;       // Struktura pro uživatelská data (hmotnost, výška, ...)
                    loadMeasurements(user);  // Načtení údajů
                    w.createInteractive(db, user); // Vytvoření tréninku interaktivně
                    w.print();               // Vypíše právě vytvořený trénink
                    w.printStats();          // Vypíše statistiky tréninku
                    w.saveWorkoutToFile(w);  // Uloží trénink do souboru
                    rebuildAchievementsFromHistory(); // Přepočítání achievements z historie
                    w.clear();               // Vyčistí objekt tréninku
                    break;
                }
                case 2:
                    w.printHistory();         // Vypíše všechny uložené tréninky
                    break;
                case 3: {
                    w.printHistory();         // Nejprve vypíše historii
                    int num;
                    cout << "Zadej cislo workoutu ke smazani: ";
                    cin >> num;               // Zvolí, který trénink smazat
                    w.deleteWorkoutByNumber(num); // Smazání vybraného tréninku
                    rebuildAchievementsFromHistory(); // Přepočítání achievements po smazání
                    cout << "\nAktualizovana historie workoutu:\n";
                    w.printHistory();         // Zobrazení aktualizované historie
                    break;
                }
                case 0:
                    break; // Návrat zpět do hlavního menu
                default:
                    cout << "Neplatna volba!\n";
                }
            }
            break;
        }

        // ===== NEJLEPSI VYKONY =====
        case 3:
            printAchievements(); // Vypíše achievements (statistiky) ze souboru
            break;

        // ===== NASTAVENI TELESNYCH UDAJU =====
        case 4: {
            Measurements m;        // Objekt pro zadání údajů
            manageMeasurements(m); // Správa údajů (hmotnost, výška, ...)
            break;
        }

        // ===== UKONCENI PROGRAMU =====
        case 0:
            cout << "Konec programu.\n";
            break;

        default:
            cout << "Neplatna volba!\n"; // Chybné zadání
        }
    }

}
