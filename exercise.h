#pragma once
#include <string>
#include "muscle.h"
using namespace std;

// =========================
// Exercise
// =========================
class Exercise {
private:
    string name;
    Muscle primary;
    Muscle secondary[5];
    int secondaryCount = 0;

public:
    Exercise() {}
    Exercise(string n, Muscle p) : name(n), primary(p) {}
    void setName(string n) { name = n; }
    void setPrimary(Muscle p) { primary = p; }
    void addSecondary(Muscle m);
    string getName() const { return name; }
    Muscle getPrimary() const { return primary; }
};
