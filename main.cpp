#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
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



class ExerciseDatabase {
private:
    Exercise exercises[200];   // jednoduché pole
    int count = 0;             // kolik cviků máme

public:

    // Přidání cviku
    void addExercise(const Exercise& e) {
        if (count < 200) {
            exercises[count++] = e;
        } else {
            cout << "Databaze je plna!\n";
        }
    }

    // Najít cvik podle názvu
    Exercise* findByName(const string& name) {
        for (int i = 0; i < count; i++) {
            if (exercises[i].getName() == name) {
                return &exercises[i];
            }
        }
        return nullptr;
    }

    // Vypsat všechny cviky
    void printAllByMuscle() const {
    if (count == 0) {
        cout << "Zadne cviky nejsou ulozeny.\n";
        return;
    }

    // 1. Nejprve najdeme všechny unikatní svaly
    string muscles[100];
    int muscleCount = 0;

    for (int i = 0; i < count; i++) {
        string m = exercises[i].getPrimary().name;

        bool exists = false;
        for (int j = 0; j < muscleCount; j++) {
            if (muscles[j] == m) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            muscles[muscleCount++] = m;
        }
    }

    // 2. Pro každý sval vypíšeme odpovídající cviky
    for (int i = 0; i < muscleCount; i++) {
        cout << muscles[i] << ":\n";

        for (int j = 0; j < count; j++) {
            if (exercises[j].getPrimary().name == muscles[i]) {
                cout << "  - " << exercises[j].getName() << "\n";
            }
        }

        cout << "\n";
    }
}


    // Interaktivní přidání cviku
    void addExerciseInteractive() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ← KLÍČOVÝ ŘÁDEK

    string name;
    string primaryName;

    cout << "Zadej nazev cviku: ";
    getline(cin, name);

    cout << "Zadej primarni sval: ";
    getline(cin, primaryName);

    Muscle p;
    p.name = primaryName;

    Exercise e(name, p);

    // Sekundární svaly (pokud chceš, můžeš přidat později)
    int more = 1;
    while (more) {
        cout << "Chces pridat sekundarni sval? (1 = ano, 0 = ne): ";
        cin >> more;
        if (more) {
            Muscle m;
            cout << "Nazev svalu: ";
            cin >> m.name;
            e.addSecondary(m);
        }
    }

    // Přidat do databáze v programu
    addExercise(e);

    // Přidat do souboru na konec
    ofstream file("exercise.txt", ios::app); // ios::app = append, přidá na konec
    if (file.is_open()) {
        file <<"\n"<<name << ";" << p.name << ";";
        file.close();
    } else {
        cout << "Nepodarilo se otevrit soubor pro zapis.\n";
    }

    cout << "Cvik ulozen do programu!\n";
}


    // Načti cviky ze souboru
    void loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Nepodarilo se otevrit soubor " << filename << "\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        // Rozdělení podle ;
        size_t pos1 = line.find(';');
        if (pos1 == string::npos) continue;

        string name = line.substr(0, pos1);

        size_t pos2 = line.find(';', pos1 + 1);
        if (pos2 == string::npos) continue;

        string primaryMuscle = line.substr(pos1 + 1, pos2 - pos1 - 1);

        // Vytvoření cviku
        Muscle m;
        m.name = primaryMuscle;
        Exercise e(name, m);

        addExercise(e);
    }

    file.close();
}

    // Odstranění cviku z databáze i souboru
    void removeExercise(const string& filename = "exercise.txt") {
        bool found = false;

         string nameToRemove;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // vyčistí buffer
        cout << "Zadej nazev cviku, ktery chces odstranit: ";
        getline(cin, nameToRemove);

        // 1️⃣ Odstranění z paměti
        for (int i = 0; i < count; i++) {
            if (exercises[i].getName() == nameToRemove) {
            found = true;

                // posunout všechny další cviky o jednu pozici zpět
                for (int j = i; j < count - 1; j++) {
                    exercises[j] = exercises[j + 1];
                }
                count--;
                break;
            }
        }

        if (!found) {
            cout << "Cvik nenalezen.\n";
            return;
        }

        // 2️⃣ Přepsání souboru
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Nepodarilo se otevrit soubor.\n";
            return;
        }

        for (int i = 0; i < count; i++) {
            file << exercises[i].getName() << ";" 
                << exercises[i].getPrimary().name << ";";
            if (i != count - 1) file << "\n"; // oddělení řádků
        }

        file.close();

        cout << "Cvik odstraněn.\n";
}

};

struct ExerciseEntry {
    Exercise exercise;
    float weight[20];
    int reps[20]; 
    int sets;
};

// ================= WORKOUT =================
class Workout {
private:
    ExerciseEntry entries[20];
    int count = 0;

public:
    void addExercise(const ExerciseEntry& entry) {
        if (count < 20) {
            entries[count++] = entry;
        } else {
            cout << "Workout je plny.\n";
        }
    }

    void print() const {
    
        if (count == 0) {
            cout << "Workout je prazdny.\n";
            return;
        }

        cout << "\n=== WORKOUT ===\n";
        for (int i = 0; i < count; i++) {
            cout << "- " << entries[i].exercise.getName()
                 << " (" << entries[i].exercise.getPrimary().name << ") "
                 << entries[i].weight << " kg, "
                 << entries[i].sets << "x" << entries[i].reps << endl;
        }
    }

    // Uložení workoutu do souboru
    void saveToFile() const {
    string filename = "workouts.txt";
    ofstream file(filename, ios::app); // přidá na konec
    if (!file.is_open()) {
        cout << "Nepodarilo se otevrit soubor.\n";
        return;
    }

    file << "\n=== WORKOUT ===\n";

    for (int i = 0; i < count; i++) {
        file << entries[i].exercise.getName() 
             << " (" << entries[i].exercise.getPrimary().name << "):\n";

        for (int s = 0; s < entries[i].sets; s++) {
            file << "  " << (s + 1) << ". serie: "
                 << entries[i].weight[s] << " kg, "
                 << entries[i].reps[s] << " opakovani;\n";
        }
    }

    file.close();
    cout << "Workout ulozen do souboru " << filename << "\n";
}


    // Interaktivní vytvoření workoutu
     void createInteractive(ExerciseDatabase& db) {
    while (true) {
        string name;
        cout << "Zadej nazev cviku (0 pro konec): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        if (name == "0") break;

        Exercise* e = db.findByName(name);
        if (!e) {
            cout << "Cvik nenalezen!\n";
            continue;
        }

        ExerciseEntry entry;
        entry.exercise = *e;

        cout << "Pocet serii: ";
        cin >> entry.sets;

        for (int s = 0; s < entry.sets; s++) {
            cout << (s + 1) << ". serie:\n";
            cout << "  Vaha (kg): ";
            cin >> entry.weight[s];
            cout << "  Opakovani: ";
            cin >> entry.reps[s];
        }

        addExercise(entry); // uložíme celý cvik se všemi sériemi do paměti
    }
}


};

int main() {
    Workout w;
    ExerciseDatabase db;
    db.loadFromFile("exercise.txt");
    int choice = -1;

    while (choice != 0) {
        cout << "=== MENU ===\n";
        cout << "1. Vypsat všechny cviky\n";
        cout << "2. Přidat nový cvik\n";
        cout << "3. Odstranit cvik\n";
        cout << "4. Vytvořit trénink\n";
        cout << "5. Historie tréninků\n";
        cout << "6. Nejlepší výkony\n";
        cout << "0. Konec\n";
        cout << "Vyber: ";
        cin >> choice;

        switch (choice) {
            case 1:
                db.printAllByMuscle();
                break;

            case 2:
                db.addExerciseInteractive();
                break;

            case 3: 
                db.removeExercise(); // odstraní cvik z paměti i ze souboru
                break;

            case 4:
                w.createInteractive(db);
                w.print();
                w.saveToFile();
                break;

            case 5:
                
                 break;
            case 0:
                return 0;

            default:
                cout << "Neplatná volba!\n";
        }
    }
}