#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Muscle {
    string name;
};


class Exercise {
private:
    string name;
    Muscle primary;
    Muscle secondary[5];  
    int secondaryCount = 0;


public:
    Exercise() {} // prázdný konstruktor

    Exercise(string n, Muscle p) : name(n), primary(p) {}

    // Settery
    void setName(string n) { name = n; }
    void setPrimary(Muscle p) { primary = p; }
    void addSecondary(Muscle m) {
        if (secondaryCount < 5) {
            secondary[secondaryCount++] = m;
        } else {
            cout << "Maximalni pocet sekundarnich svalu dosazen.\n";
        }
    }

    // Gettery
    string getName() const { return name; }
    Muscle getPrimary() const { return primary; }

};



int main() {

    int choice;

    while (true) {
        cout << "=== MENU ===\n";
        cout << "1. Vypsat všechny cviky\n";
        cout << "2. Přidat nový cvik\n";
        cout << "3. Vytvořit trénink\n";
        cout << "4. Historie tréninků\n";
        cout << "0. Konec\n";
        cout << "Vyber: ";
        cin >> choice;

        switch (choice) {
            case 1:
                
                break;

            case 2:
               
                break;

            case 3: {
                
                break;
            }

            case 4:
               
                break;

            case 0:
                return 0;

            default:
                cout << "Neplatná volba!\n";
        }
    }
}


