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

// ===== Přidání cviku do workoutu =====
void Workout::addExercise(const ExerciseEntry& entry){
    if(count<20) entries[count++]=entry;
    else cout<<"Workout je plny.\n";
}

// ===== Výpis workoutu =====
void Workout::print() const{
    if(count==0){cout<<"Workout je prazdny.\n"; return;}
    cout<<"\n=== WORKOUT ===\n";
    for(int i=0;i<count;i++){
        cout<<"- "<<entries[i].exercise.getName()<<" ("<<entries[i].exercise.getPrimary().name<<")\n";
        for(int s=0;s<entries[i].sets;s++)
            cout<<"  "<<s+1<<". serie: "<<entries[i].weight[s]<<" kg, "<<entries[i].reps[s]<<" opakovani\n\n";
    }
}

// ===== Uloží workout do souboru =====
void Workout::saveWorkoutToFile(const Workout& workout, const string& filename){
    ofstream out(filename, ios::app);
    if(!out.is_open()){cout<<"Nelze otevrit "<<filename<<"\n"; return;}

    static int workoutCounter=1;
    out<<"=== WORKOUT "<<workoutCounter++<<" ===\n";

    for(int i=0;i<workout.getCount();i++){
        const ExerciseEntry& entry = workout.getEntry(i);
        out<<entry.exercise.getName()<<" ("<<entry.exercise.getPrimary().name<<"):\n";
        for(int s=0;s<entry.sets;s++){
            float volume = entry.weight[s]*entry.reps[s];
            out<<"  "<<s+1<<". serie: "<<entry.weight[s]<<" kg, "<<entry.reps[s]<<" reps, Volume="<<volume<<"\n";
        }
        out<<"\n";
    }
    out.close();
    cout<<"Workout ulozen do souboru.\n";
}

// ===== Interaktivní vytvoření workoutu =====
void Workout::createInteractive(ExerciseDatabase& db, const Measurements& user){
    while(true){
        string name;
        cout<<"\nZadej nazev cviku (0 pro konec): ";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        getline(cin,name);
        if(name=="0") break;

        Exercise* e = db.findByName(name);
        if(!e){cout<<"Cvik nenalezen!\n"; continue;}

        ExerciseEntry entry; entry.exercise = *e;
        cout<<"Pocet serii: "; cin>>entry.sets;
        if(entry.sets>20) entry.sets=20;

        float addWeight=0.0f;
        bool bodyweightExercise = (name=="Pull Ups" || name=="Triceps Dip");
        if(bodyweightExercise){
            cout<<"Tento cvik se pocita s vlastni vahou ("<<user.weight<<" kg).\n";
            cout<<"Zadej pridavnou vahu (0 pokud zadna): "; cin>>addWeight;
        }

        for(int s=0;s<entry.sets;s++){
            cout<<s+1<<". serie:\n";
            if(!bodyweightExercise){cout<<"Vaha (kg): "; cin>>entry.weight[s];}
            else {entry.weight[s]=user.weight+addWeight; cout<<"Vaha (kg): "<<entry.weight[s]<<"\n";}
            cout<<"Opakovani: "; cin>>entry.reps[s];
        }

        addExercise(entry);
        cout<<"Cvik pridan do workoutu.\n";
    }
}

// ===== Výpis statistik =====
void Workout::printStats() const{
    if(count==0){cout<<"Workout je prazdny.\n"; return;}

    string muscles[50]; float totalWeight[50]={0}; int totalSets[50]={0}; int muscleCount=0;
    float workoutTotalWeight=0; int workoutTotalSets=0;

    for(int i=0;i<count;i++){
        const ExerciseEntry& e=entries[i];
        string muscleName = e.exercise.getPrimary().name;

        int index=-1;
        for(int j=0;j<muscleCount;j++) if(muscles[j]==muscleName){index=j; break;}
        if(index==-1){index=muscleCount; muscles[muscleCount++]=muscleName;}

        totalSets[index]+=e.sets; workoutTotalSets+=e.sets;
        float lifted=0; for(int s=0;s<e.sets;s++) lifted+=e.weight[s]*e.reps[s];
        totalWeight[index]+=lifted; workoutTotalWeight+=lifted;
    }

    cout<<"\n=== STATISTIKY WORKOUTU ===\n";
    for(int i=0;i<muscleCount;i++){
        cout<<muscles[i]<<":\n  Serie: "<<totalSets[i]<<"\n  Zvednuto: "<<totalWeight[i]<<" kg\n\n";
    }
    cout<<"=== CELKEM ===\nSerie celkem: "<<workoutTotalSets<<"\nZvednuto celkem: "<<workoutTotalWeight<<" kg\n\n";
}

// ===== Vymazání workoutu =====
void Workout::clear(){count=0;}

void Workout::deleteWorkoutByNumber(int number, const string& filename){
    ifstream file(filename);
    if(!file.is_open()){cout<<"Soubor s treninky neexistuje.\n"; return;}

    vector<string> lines; string line;
    while(getline(file,line)) lines.push_back(line);
    file.close();

    vector<int> workoutStartIndices;
    for(size_t i=0;i<lines.size();i++) if(lines[i].find("=== WORKOUT")!=string::npos) workoutStartIndices.push_back(i);

    if(number<1 || number>workoutStartIndices.size()){cout<<"Workout s timto cislem neexistuje.\n"; return;}

    int start=workoutStartIndices[number-1];
    int end = (number<workoutStartIndices.size()) ? workoutStartIndices[number] : lines.size();
    lines.erase(lines.begin()+start, lines.begin()+end);

    int workoutCounter=1;
    for(size_t i=0;i<lines.size();i++)
        if(lines[i].find("=== WORKOUT")!=string::npos) lines[i]="=== WORKOUT "+to_string(workoutCounter++)+" ===";

    ofstream out(filename);
    for(const string& l: lines) out<<l<<"\n";
    out.close();
    cout<<"Workout #"<<number<<" byl odstraněn.\n";
}

// ===== Výpis historie =====
void Workout::printHistory(const string& filename){
    ifstream file(filename);
    if(!file.is_open()){cout<<"Historie treninku neexistuje.\n"; return;}

    string line; bool empty=true;
    cout<<"\n=== HISTORIE TRENINKU ===\n\n";
    while(getline(file,line)){cout<<line<<"\n"; empty=false;}
    if(empty) cout<<"Zadne treninky zatim nejsou ulozeny.\n";
    cout<<"\n========================\n";
    file.close();
}


