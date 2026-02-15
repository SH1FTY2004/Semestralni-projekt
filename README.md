# 🏋️ Workout Tracker – Konzolová C++ aplikace

## 📌 Přehled projektu

Workout Tracker je konzolová aplikace napsaná v jazyce C++, která slouží k evidenci silových tréninků, cviků a tělesných údajů uživatele. Program umožňuje vytvářet tréninky, ukládat jejich historii do souboru, vyhodnocovat nejlepší výkony (achievements) a spravovat databázi cviků podle svalových skupin.

Aplikace je navržena bez použití dynamických kontejnerů (např. `vector`) pro hlavní datové struktury — používá pevná pole a práci se soubory. Je tedy vhodná jako semestrální / zápočtový projekt pro procvičení:

* práce se třídami
* práce se soubory
* parsování textových dat
* strukturovaný návrh programu
* menu-driven CLI aplikace
* základní statistické výpočty

---

## ⚙️ Funkce aplikace

### ✅ Správa cviků

* načtení cviků ze souboru
* rozdělení podle primárního svalu
* přidání nového cviku interaktivně
* odstranění cviku
* vyhledání historie konkrétního cviku
* podpora sekundárních svalů

---

### 🏋️ Tréninky

* vytvoření workoutu krok za krokem
* přidávání cviků do tréninku
* zadání sérií, vah a opakování
* podpora cviků s vlastní vahou těla (např. shyby, dipy)
* automatický výpočet:

  * objemu série (váha × opakování)
  * celkového objemu tréninku
* uložení workoutu do souboru
* výpis historie tréninků
* mazání workoutu podle čísla

---

### 🏆 Nejlepší výkony (Achievements)

Program z historie tréninků automaticky přepočítává statistiky pro každý cvik:

* maximální zvednutá váha
* maximální objem jedné série
* odhad 1RM (Epley formule)

Vzorec:

```
1RM = váha × (1 + opakování / 30)
```

Achievements se ukládají do samostatného souboru a lze je kdykoliv znovu přegenerovat z historie.

---

### 📏 Tělesné údaje uživatele

Program umožňuje ukládat a spravovat:

* váhu
* výšku
* věk
* obvod hrudníku
* obvod pasu
* obvod paží
* obvod stehen

Tyto údaje se používají například u cviků s vlastní vahou.

---

## 📂 Struktura souborů

```
exercise.h / exercise.cpp
→ definice cviku

exercise_database.h / .cpp
→ databáze cviků

workout.h / .cpp
→ workout a jeho logika

measurements.h / .cpp
→ tělesné údaje

utils.h / .cpp
→ achievements + pomocné funkce

main.cpp
→ hlavní menu aplikace
```

---

## 💾 Používané datové soubory

### exercise.txt

Databáze cviků a svalových skupin.

---

### workouts.txt

Historie všech uložených tréninků:

```
=== WORKOUT 3 ===
Bench Press:
  1. serie: 80 kg, 5 reps, Volume=400
```

---

### achievements.txt

Automaticky generované nejlepší výkony:

```
=== Bench Press ===
MaxWeight=100
MaxVolume=500
1RM=116.6
```

---

### measurements.txt

Tělesné údaje uživatele ve formátu klíč=hodnota.

---

## 🧠 Architektura programu

Program je rozdělen do samostatných modulů:

* **Exercise** — reprezentuje cvik
* **ExerciseDatabase** — správa všech cviků
* **Workout** — jeden trénink
* **ExerciseEntry** — cvik uvnitř workoutu
* **Measurements** — tělesná data
* **Achievement** — statistiky výkonu

Používá se:

* OOP návrh
* zapouzdření
* práce s referencemi
* práce s konstantními metodami
* oddělení rozhraní (.h) a implementace (.cpp)

---

## ▶️ Ovládání programu

Hlavní menu:

```
[1] Cviky
[2] Treninky
[3] Nejlepsi vykony
[4] Nastaveni telesnych udaju
[0] Konec
```

Podmenu obsahují další interaktivní volby.

---

## 🧮 Výpočty

Program počítá:

* objem série
* objem cviku
* objem podle svalových skupin
* celkový objem workoutu
* 1RM odhad
* maxima napříč historií

---

## 🚫 Omezení

* pevné velikosti polí (max počty):

  * 200 cviků
  * 20 cviků ve workoutu
  * 20 sérií na cvik
* textový formát souborů → závislost na správném zápisu
* bez GUI — pouze konzole
* bez databáze — pouze textové soubory

---

## 🎯 Vhodné pro

* zápočtový / semestrální projekt
* procvičení C++
* práci se soubory
* parsování textu
* menu aplikace
* OOP návrh

---

## 🔧 Možná rozšíření

* grafické rozhraní
* grafy progresu
* export do CSV
* filtrování podle svalů
* historie podle data
* trend výkonu
* validace vstupů
* dynamické kontejnery
* testy

---


