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

void Exercise::addSecondary(Muscle m) {
    if(secondaryCount<5) secondary[secondaryCount++]=m;
    else cout<<"Maximalni pocet sekundarnich svalu dosazen.\n";
}
