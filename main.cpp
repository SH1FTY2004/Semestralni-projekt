#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

struct Muscle {
    string name;
};

struct Measurements {
    float weight;
    int height;
    int age;
    float chest;
    float waist;
    float arms;
    float thighs;
};

int countWorkoutsInFile(const string& filename = "workouts.txt") {
        ifstream file(filename);
        if (!file.is_open()) return 0;

        string line;
        int count = 0;
        while (getline(file, line)) {
            if (line.find("=== WORKOUT") != string::npos) {
                count++;
            }
        }

        file.close();
        return count;
    }

void saveMeasurements(const Measurements& m) {
    ofstream file("measurements.txt");

    if (!file.is_open()) {
        cout << "Nelze otevrit measurements.txt\n";
        return;
    }

    file << "weight=" << m.weight << "\n";
    file << "height=" << m.height << "\n";
    file << "age=" << m.age << "\n";
    file << "chest=" << m.chest << "\n";
    file << "waist=" << m.waist << "\n";
    file << "arms=" << m.arms << "\n";
    file << "thighs=" << m.thighs << "\n";

    file.close();
}


void loadMeasurements(Measurements& m) {
    ifstream file("measurements.txt");

    if (!file.is_open()) {
        // default hodnoty
        m.weight = 0;
        m.height = 0;
        m.age = 0;
        m.chest = 0;
        m.waist = 0;
        m.arms = 0;
        m.thighs = 0;
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t pos = line.find('=');
        if (pos == string::npos) continue;

        string key = line.substr(0, pos);
        string value = line.substr(pos + 1);

        if (key == "weight") m.weight = stof(value);
        else if (key == "height") m.height = stoi(value);
        else if (key == "age") m.age = stoi(value);
        else if (key == "chest") m.chest = stoi(value);
        else if (key == "waist") m.waist = stoi(value);
        else if (key == "arms") m.arms = stoi(value);
        else if (key == "thighs") m.thighs = stoi(value);
    }

    file.close();
}

void manageMeasurements(Measurements& m) {
    loadMeasurements(m);
    
    int volba = -1;

    cout << "\nAktualni telesne udaje:\n";
    cout << "Vaha (kg): " << m.weight << "\n";
    cout << "Vyska (cm): " << m.height << "\n";
    cout << "Vek: " << m.age << "\n";
    cout << "Hrudnik (cm): " << m.chest << "\n";
    cout << "Pas (cm): " << m.waist << "\n";
    cout << "Ruce (cm): " << m.arms << "\n";
    cout << "Stehna (cm): " << m.thighs << "\n\n";

    cout << "Zadej nove hodnoty (0 pro ponechani aktualni hodnoty):\n";
    cin >> volba;

    if (volba == 0) {

        cout << "Zadane hodnoty ponechany.\n\n";
    } else {
        float inputFloat;
        int inputInt;

        cout << "Vaha (kg): ";
        cin >> inputFloat;
        if (inputFloat != 0) m.weight = inputFloat;

        cout << "Vyska (cm): ";
        cin >> inputInt;
        if (inputInt != 0) m.height = inputInt;

        cout << "Vek: ";
        cin >> inputInt;
        if (inputInt != 0) m.age = inputInt;

        cout << "Hrudnik (cm): ";
        cin >> inputFloat;
        if (inputFloat != 0) m.chest = inputFloat;

        cout << "Pas (cm): ";
        cin >> inputFloat;
        if (inputFloat != 0) m.waist = inputFloat;

        cout << "Ruce (cm): ";
        cin >> inputFloat;
        if (inputFloat != 0) m.arms = inputFloat;

        cout << "Stehna (cm): ";
        cin >> inputFloat;
        if (inputFloat != 0) m.thighs = inputFloat;

        saveMeasurements(m);
        cout << "Telesne udaje ulozeny.\n\n";
    }
}

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
    void addSecondary(Muscle m) {
        if (secondaryCount < 5) {
            secondary[secondaryCount++] = m;
        } else {
            cout << "Maximalni pocet sekundarnich svalu dosazen.\n";
        }
    }

    string getName() const { return name; }
    Muscle getPrimary() const { return primary; }

};



class ExerciseDatabase {
private:
    Exercise exercises[200];   
    int count = 0;             

public:

    
    void addExercise(const Exercise& e) {
        if (count < 200) {
            exercises[count++] = e;
        } else {
            cout << "Databaze je plna!\n";
        }
    }

    
    Exercise* findByName(const string& name) {
        for (int i = 0; i < count; i++) {
            if (exercises[i].getName() == name) {
                return &exercises[i];
            }
        }
        return nullptr;
    }

    
    void printAllByMuscle() const {
    if (count == 0) {
        cout << "Zadne cviky nejsou ulozeny.\n";
        return;
    }

    
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


    
    void loadFromFile(const string& filename = "exercise.txt") {
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
             << " (" << entries[i].exercise.getPrimary().name << ")\n";

        for (int s = 0; s < entries[i].sets; s++) {
            cout << "  " << (s + 1) << ". serie: "
                 << entries[i].weight[s] << " kg, "
                 << entries[i].reps[s] << " opakovani\n\n";
        }
    }
}


    void saveToFile() const {
    string filename = "workouts.txt";

    int workoutNumber = countWorkoutsInFile(filename) + 1;

    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Nepodarilo se otevrit soubor.\n";
        return;
    }

    file << "\n=== WORKOUT " << workoutNumber << " ===\n";

    for (int i = 0; i < count; i++) {
        file << entries[i].exercise.getName()
             << " (" << entries[i].exercise.getPrimary().name << "):\n";

        for (int s = 0; s < entries[i].sets; s++) {
            file << "  " << (s + 1) << ". serie: "
                 << entries[i].weight[s] << " kg, "
                 << entries[i].reps[s] << " opakovani\n";
        }
    }

    file.close();
    cout << "Workout #" << workoutNumber << " ulozen.\n\n";
}


    void createInteractive(ExerciseDatabase& db, const Measurements& user) {
    while (true) {
        string name;
        cout << "\nZadej nazev cviku (0 pro konec): ";
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
        cout << "\n";
        
        if (entry.sets > 20) entry.sets = 20;

        float addWeight = 0.0f;

        
        bool bodyweightExercise = (name == "Pull Ups" || name == "Triceps Dip");
        if (bodyweightExercise) {
            cout << "Tento cvik se počítá s vlastní vahou (" << user.weight << " kg).\n";
            cout << "Zadej přídavnou váhu (0 pokud žádná): ";
            cin >> addWeight;
            cout << "\n";
        }

        for (int s = 0; s < entry.sets; s++) {
            cout << (s + 1) << ". serie:\n";

            if (!bodyweightExercise) {
                cout << "Vaha (kg): ";
                cin >> entry.weight[s];
            } else {
            
                entry.weight[s] = user.weight + addWeight;
                cout << "Vaha (kg): " << entry.weight[s] << " (vlastní + pridavna)\n";
            }

            cout << "Opakovani: ";
            cin >> entry.reps[s];
            cout << "\n";
        }

        addExercise(entry);
        cout << "Cvik pridan do workoutu.\n";
    }
}


    void printStats() const {
    if (count == 0) {
        cout << "Workout je prazdny.\n";
        return;
    }

    string muscles[50];
    float totalWeight[50] = {0};
    int totalSets[50] = {0};
    int muscleCount = 0;

    float workoutTotalWeight = 0;
    int workoutTotalSets = 0;

    for (int i = 0; i < count; i++) {
        const ExerciseEntry& e = entries[i];
        string muscleName = e.exercise.getPrimary().name;

        // najdi index svalu
        int index = -1;
        for (int j = 0; j < muscleCount; j++) {
            if (muscles[j] == muscleName) {
                index = j;
                break;
            }
        }

        if (index == -1) {
            index = muscleCount;
            muscles[muscleCount++] = muscleName;
        }

        // Přičti série
        totalSets[index] += e.sets;
        workoutTotalSets += e.sets;

        // Přičti celkovou váhu (váha * opakování * série)
        // Přičti váhu všech sérií pro tento cvik
        float lifted = 0;
        for (int s = 0; s < e.sets; s++) {
            lifted += e.weight[s] * e.reps[s];
        }
        totalWeight[index] += lifted;
        workoutTotalWeight += lifted;

    }

    // Výpis statistik
    cout << "\n=== STATISTIKY WORKOUTU ===\n";
    for (int i = 0; i < muscleCount; i++) {
        cout << muscles[i] << ":\n";
        cout << "  Serie: " << totalSets[i] << "\n";
        cout << "  Zvednuto: " << totalWeight[i] << " kg\n\n";
    }

    cout << "=== CELKEM ===\n";
    cout << "Serie celkem: " << workoutTotalSets << "\n";
    cout << "Zvednuto celkem: " << workoutTotalWeight << " kg\n\n";
}


    static void printHistory(const string& filename = "workouts.txt") {
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "Historie treninku neexistuje.\n";
            return;
        }

        cout << "\n=== HISTORIE TRENINKU ===\n\n";

        string line;
        bool empty = true;

        while (getline(file, line)) {
            cout << line << "\n";
            empty = false;
        }

        if (empty) {
            cout << "Zadne treninky zatim nejsou ulozeny.\n";
        }

        cout << "\n========================\n";

        file.close();
    }


    static void deleteWorkoutByNumber(int number, const string& filename = "workouts.txt") {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Soubor s treninky neexistuje.\n";
            return;
        }

        vector<string> lines;
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();

        string startTag = "=== WORKOUT " + to_string(number) + " ===";
        string nextTag  = "=== WORKOUT " + to_string(number + 1) + " ===";

        vector<string> output;
        bool skip = false;
        bool found = false;

        for (size_t i = 0; i < lines.size(); i++) {
            if (lines[i] == startTag) {
                skip = true;
                found = true;
                continue;
            }

            if (skip && lines[i].find("=== WORKOUT") != string::npos) {
                skip = false;
            }

            if (!skip) {
                output.push_back(lines[i]);
            }
        }

        if (!found) {
            cout << "Workout s timto cislem neexistuje.\n";
            return;
        }

        ofstream out(filename);
        for (const string& l : output) {
            out << l << "\n";
        }
        out.close();

        cout << "Workout #" << number << " byl odstraněn.\n";
    }


    void clear() {
    count = 0;
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
        //cout << "6. Nejlepší výkony\n";
        cout << "7. Nastavení tělesných údajů\n";
        cout << "8. Odstranit trénink\n";
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
                db.removeExercise(); 
                break;

            case 4:
                Measurements user;
                loadMeasurements(user);
                w.createInteractive(db, user);
                w.print();
                w.printStats();
                w.saveToFile();
                w.clear();
                break;

            case 5:
                w.printHistory();
                 break;
            case 6:
            
                break;

            case 7: 
                Measurements m;
                manageMeasurements(m);
                break;
            case 8: {
                w.printHistory();
                int num;
                cout << "Zadej cislo workoutu ke smazani: ";
                cin >> num;
                w.deleteWorkoutByNumber(num);
                break;
}

                return 0;

            default:
                cout << "Neplatná volba!\n";
        }
    }
}