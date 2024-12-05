# Advent of Code 2024: RPG Challenge
This repository contains solutions for Advent of Code 2024, presented with a unique twist: an RPG-inspired system. 
In this approach, solving puzzles becomes part of a larger challenge involving resource management, constraints, and character progression.
Instead of solving puzzles straightforwardly, you manage a limited energy pool, contend with aging as you rest, and carefully use an artifact with specific rules and restrictions.

You can find the tutorial [here](https://github.com/Sycix-HK/Advent-of-Code-2024-RPG/blob/main/Dungeon/TutorialRoom/Tutorial.cpp)

---

| Mon | Tue | Wed | Thu | Fri | Sat | Sun |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|  |   |   |   |  |    | [Day 1](https://github.com/Sycix-HK/Advent-of-Code-2024-RPG/blob/main/Dungeon/Room1/Room1.cpp) <br> ⭐⭐ <br> ```Age 20``` |
| [Day 2](https://github.com/Sycix-HK/Advent-of-Code-2024-RPG/blob/main/Dungeon/Room2/Room2.cpp) <br> ⭐⭐ <br> ```Age 20``` | [Day 3](https://github.com/Sycix-HK/Advent-of-Code-2024-RPG/blob/main/Dungeon/Room3/Room3.cpp) <br> ⭐⭐ <br> ```Age 21```  | [Day 4](https://github.com/Sycix-HK/Advent-of-Code-2024-RPG/tree/main/Dungeon/Room4) <br> ⭐⭐ <br> ```Age 21```  | Day 5 <br> ⏳⏳  | Day 6 <br> ⏳⏳  | Day 7 <br> ⏳⏳  | Day 8 <br> ⏳⏳  |
| Day 9 <br> ⏳⏳ | Day 10 <br> ⏳⏳  | Day 11 <br> ⏳⏳  | Day 12 <br> ⏳⏳  | Day 13 <br> ⏳⏳  | Day 14 <br> ⏳⏳  | Day 15 <br> ⏳⏳  |
| Day 16 <br> ⏳⏳ | Day 17 <br> ⏳⏳  | Day 18 <br> ⏳⏳  | Day 19 <br> ⏳⏳  | Day 20 <br> ⏳⏳  | Day 21 <br> ⏳⏳  | Day 22 <br> ⏳⏳  |
| Day 23 <br> ⏳⏳ |  Day 24 <br> ⏳⏳  |   Day 25 <br> ⏳⏳ |   |   |

---

![image](https://github.com/user-attachments/assets/0e9feb51-3cec-4640-bac4-3d26310f038a)

---

# Features and Rules

### Energy System
- Every memory allocation deducts from your energy pool.
- Some personal rules:
    - Constexpr and readability-purpose const variables do not have to cost energy, when you could obviously replace them by computing the same line everywhere it's used.
    - Loop indicies have to cost energy wherever they are actually used, iterators simulating a foreach are free.
    - While using a function's return value and passing literals as parameters doesn't necessarily allocate memory on the heap, the system could still be cheated with them, so return values and parameters have to be energy-managed.
 
### Artifact:
  - Creates a custom scope where allocations won't cost energy, but each line of use wears it down, introducing loss of characters to use inside scope next time.
  - You may only use the artifact once per enemy (aoc half day).
  - You may not use it inside loops.
  - You may not return early from the artifact's scope.
  - Every 10 lines used will break characters, constraining the letters you can use within the artifact's scope for consequent uses, until repaired.
  - You may not exceed 25 broken characters, not even if you intend to repair it after.
  - When dealing with a long line with multiple operations or lambda functions inside them (like an std::transform or std::acumulate), the rule is that each ; counts as a line. So an std::transform with a lambda function with a single return line costs 2 lines of wear.
  - Loops counts as one line

### Resting and Aging:
  - Resting between puzzles restores energy but increases your character’s age.
  - You may also repair the artifact between puzzles, which won't restore energy, but will clear all broken characters from the artifact to give a fresh start to it. This action will age you the same way.
  - Your goal is to complete the challenges as young as possible.

---

# Combat Log

* You carefully push the door open to [room 1](https://github.com/Sycix-HK/Advent-of-Code-2024-RPG/blob/main/Dungeon/Room1/Room1.cpp), entering a chamber filled with dusty tomes and ancient scrolls.
```
- Age: 20 years
- Energy: 500 / 500
- Artifact Wear: 0 lines
- Clues damaged in Artifact:
```
 * You decipher an ancient text in 300.906 milliseconds, expending 128 energy.
 * You uncover a critical clue, unraveling 3714264 layers of historical mystery.
```
- Age: 20 years
- Energy: 372 / 500
- Artifact Wear: 0 lines
- Clues damaged in Artifact:
```
 * You decipher an ancient text in 294.413 milliseconds, expending 32 energy.
 * You uncover a critical clue, unraveling 18805872 layers of historical mystery.
```
- Age: 20 years
- Energy: 340 / 500
- Artifact Wear: 0 lines
- Clues damaged in Artifact:
```
---
 * You carefully push the door open to [room 2](https://github.com/Sycix-HK/Advent-of-Code-2024-RPG/blob/main/Dungeon/Room2/Room2.cpp), entering a chamber filled with dusty tomes and ancient scrolls.
```
- Age: 20 years
- Energy: 340 / 500
- Artifact Wear: 0 lines
- Clues damaged in Artifact:
```
 * You decipher an ancient text in 1.1869 milliseconds, expending 40 energy.
 * You uncover a critical clue, unraveling 463 layers of historical mystery.
```
- Age: 20 years
- Energy: 300 / 500
- Artifact Wear: 0 lines
- Clues damaged in Artifact:
```
 * You decipher an ancient text in 4.5416 milliseconds, expending 248 energy.
 * You uncover a critical clue, unraveling 514 layers of historical mystery.
```
- Age: 20 years
- Energy: 52 / 500
- Artifact Wear: 0 lines
- Clues damaged in Artifact:
```
 * You take a moment to recover, drawing on the strength of the room's historical resonance, growing wiser but older.
```
- Age: 21 years
- Energy: 750 / 750
- Artifact Wear: 0 lines
- Clues damaged in Artifact:
```
---
 * You carefully push the door open to [room 3](https://github.com/Sycix-HK/Advent-of-Code-2024-RPG/blob/main/Dungeon/Room3/Room3.cpp), entering a chamber filled with dusty tomes and ancient scrolls.
```
- Age: 20 years
- Energy: 52 / 500
- Artifact Wear: 0 lines
- Clues damaged in Artifact:
```
 * You activate the artifact, shielding 1344 energy as it endures 3 lines of strain.
 * You decipher an ancient text in 2.0225 milliseconds, expending 32 energy.
 * You uncover a critical clue, unraveling 171183089 layers of historical mystery.
```
- Age: 20 years
- Energy: 20 / 500
- Artifact Wear: 3 lines
- Clues damaged in Artifact:
```
 * You take a moment to recover, drawing on the strength of the room's historical resonance, growing wiser but older.
```
- Age: 21 years
- Energy: 750 / 750
- Artifact Wear: 3 lines
- Clues damaged in Artifact:
```
 * You activate the artifact, shielding 1344 energy as it endures 3 lines of strain.
 * You decipher an ancient text in 2.6219 milliseconds, expending 32 energy.
 * You uncover a critical clue, unraveling 63866497 layers of historical mystery.
```
- Age: 21 years
- Energy: 718 / 750
- Artifact Wear: 6 lines
- Clues damaged in Artifact:
```
---
 * You carefully push the door open to [room 4](https://github.com/Sycix-HK/Advent-of-Code-2024-RPG/tree/main/Dungeon/Room4), entering a chamber filled with dusty tomes and ancient scrolls.
```
- Age: 21 years
- Energy: 718 / 750
- Artifact Wear: 6 lines
- Clues damaged in Artifact:
```
 * You decipher an ancient text in 0.5972 milliseconds, expending 48 energy.
 * You uncover a critical clue, unraveling 2344 layers of historical mystery.
```
- Age: 21 years
- Energy: 670 / 750
- Artifact Wear: 6 lines
- Clues damaged in Artifact:
```
 * You decipher an ancient text in 0.167 milliseconds, expending 32 energy.
 * You uncover a critical clue, unraveling 1815 layers of historical mystery.
```
- Age: 21 years
- Energy: 638 / 750
- Artifact Wear: 6 lines
- Clues damaged in Artifact:
```
---
