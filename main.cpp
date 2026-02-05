#include "exercise.h"
#include "workout.h"
#include "utils.h"
#include "exercise_database.h"
#include "measurements.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <map>
#include <sstream>
using namespace std;

int main() {
    Workout w;
    ExerciseDatabase db;
    db.loadFromFile("exercise.txt");
    int choice = -1;


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
        int sub = -1;
        while (sub != 0) {
            cout << "\n=== CVIKY ===\n";
            cout << "[1] Vypsat vsechny cviky\n";
            cout << "[2] Pridat novy cvik\n";
            cout << "[3] Odstranit cvik\n";
            cout << "[0] Zpet\n";
            cout << "Vyber: ";
            cin >> sub;

            switch (sub) {
            case 1:
                db.printAllByMuscle();
                break;
            case 2:
                db.addExerciseInteractive();
                break;
            case 3:
                db.removeExercise();
                break;
            case 0:
                break;
            default:
                cout << "Neplatna volba!\n";
            }
        }
        break;
    }

    // ===== TRENINKY =====
    case 2: {
        int sub = -1;
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
                Measurements user;
                loadMeasurements(user);
                w.createInteractive(db, user);
                w.print();
                w.printStats();
                rebuildAchievementsFromHistory();
                w.saveWorkoutToFile(w);
                w.clear();
                break;
            }
            case 2:
                w.printHistory();
                break;
            case 3: {
                w.printHistory();
                int num;
                cout << "Zadej cislo workoutu ke smazani: ";
                cin >> num;
                w.deleteWorkoutByNumber(num);
                rebuildAchievementsFromHistory();
                cout << "\nAktualizovana historie workoutu:\n";
                w.printHistory();
                break;
            }
            case 0:
                break;
            default:
                cout << "Neplatna volba!\n";
            }
        }
        break;
    }
    
    case 3:
        printAchievements();
        break;

    case 4: {
        Measurements m;
        manageMeasurements(m);
        break;
    }

    case 0:
        cout << "Konec programu.\n";
        break;

    default:
        cout << "Neplatna volba!\n";
    }
}

}