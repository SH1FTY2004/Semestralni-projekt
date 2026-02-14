#include "exercise.h"
#include "workout.h"
#include "utils.h"
#include "exercise_database.h"
#include "measurements.h"
#include <iostream>
using namespace std;

// ===== Přidání sekundárního svalu ke cviku =====
// Funkce přidá sval do pole sekundárních svalů cviku.
// Pokud je již počet sekundárních svalů 5, vypíše hlášku.
void Exercise::addSecondary(Muscle m) {
    if (secondaryCount < 5) 
        secondary[secondaryCount++] = m;  // přidání svalu do pole a inkrementace počtu
    else 
        cout << "Maximalni pocet sekundarnich svalu dosazen.\n";  // hláška při překročení limitu
}

