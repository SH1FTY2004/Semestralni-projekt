# Semestralni-projekt

Krátký popis

Aplikace umožňuje vytvářet a spravovat databázi posilovacích cviků rozdělených podle svalových skupin. Uživatel si může zaznamenávat své tréninky, sledovat celkovou zvednutou váhu, počet sérií, výpočet objemu (volume) a odhadované 1RM (one-rep max) pro každý cvik. Program také ukládá osobní rekordy (achievements) a umožňuje jejich přepočet při odstranění nebo úpravě tréninků.

Klíčové cíle a funkce
1. Databáze cviků

Cviky lze přidávat, odstraňovat a prohlížet podle svalových skupin (prsa, záda, nohy, ruce, ramena).

Každý cvik má primární svalovou skupinu a až 5 sekundárních svalů.

Databáze se ukládá do souboru exercise.txt a načítá při startu programu.

2. Zadávání a správa tréninků

Uživatel může vytvořit trénink složený z několika cviků.

Zadává počet sérií, váhu a počet opakování pro každou sérii.

Aplikace podporuje cviky s vlastní vahou (např. pull-ups) a umožňuje přidat přídavnou váhu.

Tréninky se ukládají do souboru workouts.txt.

Každý trénink automaticky počítá a ukládá statistiky:

Celkový počet sérií

Celkový počet opakování

Celkový objem (váha × opakování)

Největší objem v jedné sérii

3. Výpočet 1RM a osobních rekordů

Aplikace počítá odhadované 1RM (Epleyho vzorec) pro každou sérii.

Sleduje max. zvednutou váhu, max. objem a 1RM pro jednotlivé cviky.

Rekordy se ukládají do souboru achievements.txt.

Funkce rebuildAchievementsFromHistory() umožňuje přepočítat všechny rekordy, např. po smazání tréninku.

4. Historie a správa

Zobrazení historie všech tréninků s podrobnými informacemi o cvicích, sériích, váze a počtu opakování.

Odstranění konkrétního tréninku s automatickým přečíslováním zbytku historie.

Přepočet achievements po smazání tréninku.

5. Nastavení tělesných údajů

Uživatel může zadat a aktualizovat své tělesné údaje: váhu, výšku, věk, obvod hrudníku, pasu, rukou a stehen.

Tyto údaje se využívají pro cviky s vlastní vahou.

Data se ukládají do souboru measurements.txt.
